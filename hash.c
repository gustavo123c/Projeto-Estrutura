#include <stdio.h>     
#include <stdlib.h>    
#include <string.h>    
#include "hash.h"      


int converterString(const char *s) {
    int valor = 0;           
    int i;                

    // percorre cada caractere da string
    for (i = 0; s[i] != '\0'; i++) {
       
        valor = valor * 31 + (int)s[i];
    }


    if (valor < 0) valor = -valor;

    return valor;           


int funcaoHash(int valor, int tamanho) {
    int resultado = valor % tamanho; 
    if (resultado < 0) resultado += tamanho; 
    return resultado;
}

struct TabelaHash* criarTabela(int tamanho) {
   
    struct TabelaHash *tabela = (struct TabelaHash*) malloc(sizeof(struct TabelaHash));
    if (tabela == NULL) return NULL; 


    tabela->tamanho = tamanho;
    tabela->quantidade = 0;

  
    tabela->itens = (struct Registro*) malloc(tamanho * sizeof(struct Registro));


    if (tabela->itens == NULL) {
        free(tabela);
        return NULL;
    }

  
    int i;
    for (i = 0; i < tamanho; i++) {
        tabela->itens[i].usuario = NULL; 
        tabela->itens[i].senha_hash = 0; 
        tabela->itens[i].estado = 0;   
    }

    return tabela;
}

int inserir(struct TabelaHash *tabela, const char *usuario, const char *senha) {
   
    if (tabela == NULL || usuario == NULL || senha == NULL) return -1;

  
    if (buscar(tabela, usuario) != -1) return 0;

   
    int chave = converterString(usuario);
   
    int senhaHash = converterString(senha);

    
    int pos = funcaoHash(chave, tabela->tamanho);

    int i, primeiraRemovida = -1; 

    for (i = 0; i < tabela->tamanho; i++) {
  
        int indice = (pos + i) % tabela->tamanho;

        
        if (tabela->itens[indice].estado == 1) continue;

        if (tabela->itens[indice].estado == 2 && primeiraRemovida == -1)
            primeiraRemovida = indice;

   
        if (tabela->itens[indice].estado == 0) {
         
            if (primeiraRemovida != -1) indice = primeiraRemovida;

     
            tabela->itens[indice].usuario = (char*) malloc(strlen(usuario) + 1);
            strcpy(tabela->itens[indice].usuario, usuario);

            tabela->itens[indice].senha_hash = senhaHash;
            tabela->itens[indice].estado = 1;

            tabela->quantidade++;

            return 1;
        }
    }

    return -1; 
}

int buscar(struct TabelaHash *tabela, const char *usuario) {
    if (tabela == NULL || usuario == NULL) return -1;


    int chave = converterString(usuario);
    int pos = funcaoHash(chave, tabela->tamanho);

    int i;
  
    for (i = 0; i < tabela->tamanho; i++) {
        int indice = (pos + i) % tabela->tamanho;

        if (tabela->itens[indice].estado == 0) return -1;

       
        if (tabela->itens[indice].estado == 1 &&
            strcmp(tabela->itens[indice].usuario, usuario) == 0)
            return indice; // retorna o indice encontrado
    }


    return -1;
}


int remover(struct TabelaHash *tabela, const char *usuario) {

    int pos = buscar(tabela, usuario);
    if (pos == -1) return 0; 

    
    free(tabela->itens[pos].usuario);


    tabela->itens[pos].usuario = NULL;
    tabela->itens[pos].senha_hash = 0;
    tabela->itens[pos].estado = 2; 


    tabela->quantidade--;

    return 1; 
}


int login(struct TabelaHash *tabela, const char *usuario, const char *senha) {
    /
    int pos = buscar(tabela, usuario);
    if (pos == -1) return 0;

  
    int senhaHash = converterString(senha);

    
    if (senhaHash == tabela->itens[pos].senha_hash)
        return 1; 
    else
        return 0; 


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


void liberar(struct TabelaHash *tabela) {
    int i;

    // libera cada usuario armazenado
    for (i = 0; i < tabela->tamanho; i++) {
        if (tabela->itens[i].estado == 1)
            free(tabela->itens[i].usuario);
    }

    free(tabela->itens);

 
    free(tabela);
}
