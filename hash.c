#include <stdio.h>     
#include <stdlib.h>    
#include <string.h>    
#include "hash.h"      


int converterString(const char *s) {
    int valor = 0;           // valor que guardara o resultado final
    int i;                   // contador do for

    // percorre cada caractere da string
    for (i = 0; s[i] != '\0'; i++) {
        // multiplica o valor atual por 31 e soma o codigo ASCII do caractere
        valor = valor * 31 + (int)s[i];
    }

    // se o resultado for negativo, transforma em positivo
    if (valor < 0) valor = -valor;

    return valor;            // retorna o numero gerado
}


int funcaoHash(int valor, int tamanho) {
    int resultado = valor % tamanho; 
    if (resultado < 0) resultado += tamanho; 
    return resultado;
}

struct TabelaHash* criarTabela(int tamanho) {
    // aloca espaco para a estrutura principal da tabela
    struct TabelaHash *tabela = (struct TabelaHash*) malloc(sizeof(struct TabelaHash));
    if (tabela == NULL) return NULL; // se nao conseguiu alocar, retorna erro

    // define tamanho e inicializa quantidade de elementos
    tabela->tamanho = tamanho;
    tabela->quantidade = 0;

    // aloca espaco para os registros (posicoes da tabela)
    tabela->itens = (struct Registro*) malloc(tamanho * sizeof(struct Registro));

    // se nao conseguiu alocar o vetor, libera a tabela e retorna erro
    if (tabela->itens == NULL) {
        free(tabela);
        return NULL;
    }

    // inicializa todas as posicoes como vazias
    int i;
    for (i = 0; i < tamanho; i++) {
        tabela->itens[i].usuario = NULL; // nenhuma string armazenada ainda
        tabela->itens[i].senha_hash = 0; // sem senha
        tabela->itens[i].estado = 0;     // 0 = vazio
    }

    return tabela; // retorna a nova tabela criada
}

int inserir(struct TabelaHash *tabela, const char *usuario, const char *senha) {
    // verifica se a tabela ou os dados sao invalidos
    if (tabela == NULL || usuario == NULL || senha == NULL) return -1;

    // verifica se o usuario ja existe
    if (buscar(tabela, usuario) != -1) return 0; // 0 indica "ja existe"

    // gera o numero (chave) a partir do nome do usuario
    int chave = converterString(usuario);
    // gera um numero (hash) para a senha
    int senhaHash = converterString(senha);

    // calcula a posicao inicial usando a funcao de hash
    int pos = funcaoHash(chave, tabela->tamanho);

    int i, primeiraRemovida = -1; // guarda posicao de item removido, se existir

    // percorre as posicoes da tabela (enderecamento linear)
    for (i = 0; i < tabela->tamanho; i++) {
        // calcula o indice (posicao atual)
        int indice = (pos + i) % tabela->tamanho;

        // se a posicao esta ocupada, continua procurando
        if (tabela->itens[indice].estado == 1) continue;

        // se foi removida e ainda nao marcamos uma, guardamos esta posicao
        if (tabela->itens[indice].estado == 2 && primeiraRemovida == -1)
            primeiraRemovida = indice;

        // se encontramos uma posicao vazia
        if (tabela->itens[indice].estado == 0) {
            // se havia uma posicao removida antes, usaremos ela
            if (primeiraRemovida != -1) indice = primeiraRemovida;

            // aloca espaco e copia o nome do usuario
            tabela->itens[indice].usuario = (char*) malloc(strlen(usuario) + 1);
            strcpy(tabela->itens[indice].usuario, usuario);

            // guarda o hash da senha e marca como ocupado
            tabela->itens[indice].senha_hash = senhaHash;
            tabela->itens[indice].estado = 1;

            // aumenta a quantidade total de usuarios
            tabela->quantidade++;

            return 1; // insercao bem-sucedida
        }
    }

    return -1; // tabela cheia (nao encontrou posicao livre)
}

int buscar(struct TabelaHash *tabela, const char *usuario) {
    if (tabela == NULL || usuario == NULL) return -1;

    // gera a chave do usuario e calcula a posicao inicial
    int chave = converterString(usuario);
    int pos = funcaoHash(chave, tabela->tamanho);

    int i;
    // percorre as posicoes da tabela (enderecamento linear)
    for (i = 0; i < tabela->tamanho; i++) {
        int indice = (pos + i) % tabela->tamanho;

        // se encontrar uma posicao vazia, para — o usuario nao existe
        if (tabela->itens[indice].estado == 0) return -1;

        // se a posicao estiver ocupada e o nome for igual, achou o usuario
        if (tabela->itens[indice].estado == 1 &&
            strcmp(tabela->itens[indice].usuario, usuario) == 0)
            return indice; // retorna o indice encontrado
    }

    // percorreu tudo e nao encontrou
    return -1;
}


int remover(struct TabelaHash *tabela, const char *usuario) {
    // procura o usuario na tabela
    int pos = buscar(tabela, usuario);
    if (pos == -1) return 0; // nao encontrado

    // libera a memoria usada pelo nome do usuario
    free(tabela->itens[pos].usuario);

    // limpa os dados e marca como removido
    tabela->itens[pos].usuario = NULL;
    tabela->itens[pos].senha_hash = 0;
    tabela->itens[pos].estado = 2; // 2 = removido

    // diminui o contador de usuarios
    tabela->quantidade--;

    return 1; // sucesso
}

// -------------------------------
// Funcao: login
// Verifica se o usuario existe e se a senha esta correta
// -------------------------------
int login(struct TabelaHash *tabela, const char *usuario, const char *senha) {
    // procura o usuario
    int pos = buscar(tabela, usuario);
    if (pos == -1) return 0; // usuario nao existe

    // gera o hash da senha digitada
    int senhaHash = converterString(senha);

    // compara com o hash armazenado
    if (senhaHash == tabela->itens[pos].senha_hash)
        return 1; // senha correta
    else
        return 0; // senha incorreta
}

// -------------------------------
// Funcao: imprimir
// Mostra todas as posicoes da tabela (vazias, ocupadas e removidas)
// -------------------------------
void imprimir(struct TabelaHash *tabela) {
    int i;
    printf("\n--- TABELA HASH ---\n");

    // percorre todas as posicoes da tabela
    for (i = 0; i < tabela->tamanho; i++) {
        printf("[%02d] ", i);

        if (tabela->itens[i].estado == 0)
            printf("Vazio\n");
        else if (tabela->itens[i].estado == 1)
            printf("Usuario: %s | Hash senha: %d\n",
                   tabela->itens[i].usuario, tabela->itens[i].senha_hash);
        else
            printf("Removido\n");
    }
}

// -------------------------------
// Funcao: liberar
// Libera toda a memoria usada pela tabela hash
// -------------------------------
void liberar(struct TabelaHash *tabela) {
    int i;

    // libera cada usuario armazenado
    for (i = 0; i < tabela->tamanho; i++) {
        if (tabela->itens[i].estado == 1)
            free(tabela->itens[i].usuario);
    }

    // libera o vetor de itens
    free(tabela->itens);

    // libera a estrutura principal
    free(tabela);
}
