#define HASH_H

struct Registro {
    char *usuario;
    unsigned long senha_hash;
    int estado; 
};

struct TabelaHash {
    struct Registro *itens;
    int tamanho;
    int quantidade;
};

struct TabelaHash* criarTabela(int tamanho);

int inserir(struct TabelaHash *tabela, const char *usuario, const char *senha);

int buscar(struct TabelaHash *tabela, const char *usuario);

int remover(struct TabelaHash *tabela, const char *usuario);

void imprimir(struct TabelaHash *tabela);

void liberar(struct TabelaHash *tabela);

int login(struct TabelaHash *tabela, const char *usuario, const char *senha);
