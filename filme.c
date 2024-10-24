#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"

// Função para salvar a lista de filmes no arquivo
void salvarFilmesNoArquivo(Filme* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Filme* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "ID: %d\n", atual->id);
        fprintf(arquivo, "Nome: %s\n", atual->nome);
        fprintf(arquivo, "Genero: %s\n", atual->genero);
        fprintf(arquivo, "Ano: %d\n", atual->ano);
        fprintf(arquivo, "Classificacao: %d\n", atual->classificacao);
        fprintf(arquivo, "-----------------------------------\n");
        atual = atual->proximo;
    }

    fclose(arquivo);
}

// Função para carregar os filmes do arquivo para a lista encadeada
void carregarFilmesDoArquivo(Filme** lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Criando um novo arquivo.\n");
        return;
    }

    Filme* novoFilme;
    while (1) {
        novoFilme = (Filme*)malloc(sizeof(Filme));
        if (fscanf(arquivo, "ID: %d\n", &novoFilme->id) != 1) {
            free(novoFilme);
            break;
        }
        fscanf(arquivo, "Nome: %[^\n]\n", novoFilme->nome);
        fscanf(arquivo, "Genero: %[^\n]\n", novoFilme->genero);
        fscanf(arquivo, "Ano: %d\n", &novoFilme->ano);
        fscanf(arquivo, "Classificacao: %d\n", &novoFilme->classificacao);
        fscanf(arquivo, "-----------------------------------\n");
        novoFilme->proximo = NULL;
        inserirFilmeNaLista(lista, novoFilme);
    }

    fclose(arquivo);
}

// Função para inserir o filme na lista encadeada
void inserirFilmeNaLista(Filme** lista, Filme* novoFilme) {
    if (*lista == NULL) {
        *lista = novoFilme;
    } else {
        Filme* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoFilme;
    }
}

// Função para adicionar um novo filme
void adicionarFilme(Filme** lista) {
    Filme* novoFilme = (Filme*)malloc(sizeof(Filme));
    if (novoFilme == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    printf("Digite o título do filme: ");
    fgets(novoFilme->nome, sizeof(novoFilme->nome), stdin);
    novoFilme->nome[strcspn(novoFilme->nome, "\n")] = '\0';

    printf("Digite o gênero do filme: ");
    fgets(novoFilme->genero, sizeof(novoFilme->genero), stdin);
    novoFilme->genero[strcspn(novoFilme->genero, "\n")] = '\0';

    printf("Digite o ano do filme: ");
    scanf("%d", &novoFilme->ano);
    getchar();  // Limpar o buffer

    printf("Digite a classificação indicativa do filme: ");
    scanf("%d", &novoFilme->classificacao);
    getchar();  // Limpar o buffer

    novoFilme->proximo = NULL;

    // Atribuir um ID ao novo filme
    if (*lista == NULL) {
        novoFilme->id = 1;
        *lista = novoFilme;
    } else {
        Filme* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        novoFilme->id = atual->id + 1;
        atual->proximo = novoFilme;
    }

    printf("Filme cadastrado com sucesso! ID do filme: %d\n", novoFilme->id);
}

// Função para exibir os filmes cadastrados
void exibirFilmes(Filme* lista) {
    Filme* atual = lista;
    if (atual == NULL) {
        printf("\nNenhum filme armazenado.\n");
        return;
    }
    printf("\n-----------------------------\n");
    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Título: %s\n", atual->nome);
        printf("Gênero: %s\n", atual->genero);
        printf("Ano: %d \n", atual->ano);
        printf("Classificação indicativa: %d\n", atual->classificacao);
        printf("-----------------------------\n");
        atual = atual->proximo;
    }
}

// Função para excluir um filme da lista
void excluirFilme(Filme** lista, int id) {
    if (*lista == NULL) {
        printf("Nenhum filme para excluir.\n");
        return;
    }

    Filme* atual = *lista;
    Filme* anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Filme com ID %d não encontrado.\n", id);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Filme com ID %d excluído com sucesso!\n", id);
}

// Função para editar um filme
void editarFilme(Filme* lista, int id) {
    Filme* atual = lista;
    while (atual != NULL && atual->id != id) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Filme com ID %d não encontrado.\n", id);
        return;
    }

    printf("Editando filme com ID %d:\n", id);

    printf("Novo título (atual: %s): ", atual->nome);
    fgets(atual->nome, sizeof(atual->nome), stdin);
    atual->nome[strcspn(atual->nome, "\n")] = '\0';

    printf("Novo gênero (atual: %s): ", atual->genero);
    fgets(atual->genero, sizeof(atual->genero), stdin);
    atual->genero[strcspn(atual->genero, "\n")] = '\0';

    printf("Nova ano (atual: %d minutos): ", atual->ano);
    scanf("%d", &atual->ano);
    getchar();  // Limpar o buffer

    printf("Nova classificação indicativa (atual: %d): ", atual->classificacao);
    scanf("%d", &atual->classificacao);
    getchar();  // Limpar o buffer

    printf("Filme com ID %d editado com sucesso!\n", id);
}