#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Ler texto sem o \n final
void lerTexto(char *str, int tamanho) {
    fgets(str, tamanho, stdin);
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

int main() {
    int tamanho;
    printf("Informe o tamanho da tabela hash: ");
    scanf("%d", &tamanho);
    getchar(); // limpa o \n deixado pelo scanf

    struct TabelaHash *tabela = criarTabela(tamanho);
    if (tabela == NULL) {
        printf("Erro ao criar tabela.\n");
        return 1;
    }

    char opcao[10];
    char usuario[50];
    char senha[50];

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Cadastrar usuario\n");
        printf("2 - Login\n");
        printf("3 - Remover usuario\n");
        printf("4 - Mostrar tabela\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        lerTexto(opcao, 10);

        if (strcmp(opcao, "1") == 0) {
            printf("Usuario: ");
            lerTexto(usuario, 50);
            printf("Senha: ");
            lerTexto(senha, 50);

            int r = inserir(tabela, usuario, senha);
            if (r == 1) printf("Usuario cadastrado.\n");
            else if (r == 0) printf("Usuario ja existe.\n");
            else printf("Erro ao cadastrar.\n");

        } else if (strcmp(opcao, "2") == 0) {
            printf("Usuario: ");
            lerTexto(usuario, 50);
            printf("Senha: ");
            lerTexto(senha, 50);

            if (login(tabela, usuario, senha))
                printf("Login bem-sucedido!\n");
            else
                printf("Falha no login.\n");

        } else if (strcmp(opcao, "3") == 0) {
            printf("Usuario para remover: ");
            lerTexto(usuario, 50);
            if (remover(tabela, usuario))
                printf("Usuario removido.\n");
            else
                printf("Usuario nao encontrado.\n");

        } else if (strcmp(opcao, "4") == 0) {
            imprimir(tabela);

        } else if (strcmp(opcao, "5") == 0) {
            printf("Saindo...\n");
            break;

        } else {
            printf("Opcao invalida.\n");
        }
    }

    liberar(tabela);
    return 0;
}
