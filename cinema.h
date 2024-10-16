#ifndef CINEMA_H
#define CINEMA_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct filme {
    char nome[100];
    char genero[50];
    int ano;
    int faixaEtaria;
    struct filme *proximo;  // Ponteiro para o próximo filme
} Filme;

typedef struct usuario {
    char nome[50];
    char senha[50];
    char email[80];
    int idade;
    struct usuario *proximo;  // Ponteiro para o próximo usuário
} Usuario;

// Ponteiros para os cabeçalhos das listas
extern Filme *cabecalhoFilmes;
extern Usuario *cabecalhoUsuarios;
extern Usuario usuarioAtual;

// Funções para manipulação das listas encadeadas
bool verificarEmail(const char *email);
void cadastrarUsuario(Usuario *usuario);
void salvarUsuarios();
void carregarUsuarios();
void cadastrarFilme();
void salvarFilmes();
void carregarFilmes();
void listarFilmes();
void editarFilme();
void excluirFilme();
void exibirDetalhesFilme();
bool login();
void mensagemBoasVindas(const Usuario *usuario);
void menu();

#endif // CINEMA_H
