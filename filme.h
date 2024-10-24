#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct filme {
    int id;
    char nome[100];
    char genero[50];
    int ano;
    int classificacao;
    struct filme *proximo;  // Ponteiro para o próximo filme
} Filme;

void salvarFilmesNoArquivo(Filme* lista, const char* nomeArquivo);

void carregarFilmesDoArquivo(Filme** lista, const char* nomeArquivo);

void inserirFilmeNaLista(Filme** lista, Filme* novoFilme);

void adicionarFilme(Filme** lista);

void exibirFilmes(Filme* lista);

void excluirFilme(Filme** lista, int id);

void editarFilme(Filme* lista, int id);