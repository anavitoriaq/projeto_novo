#include <stdio.h>
#include <stdlib.h>
#include "filme.h"

int main() {
    Filme* listaFilmes = NULL;
    const char * nomeArquivo = "filmes.txt";
    int opcao, id;

    // Carregar os filmes do arquivo no início do programa
    carregarFilmesDoArquivo(&listaFilmes, nomeArquivo);

    do {
        printf("\nGerenciamento de Filmes\n");
        printf("1. Adicionar Filme\n");
        printf("2. Exibir Filmes\n");
        printf("3. Excluir Filme\n");
        printf("4. Editar Filme\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer

        switch (opcao) {
            case 1:
                adicionarFilme(&listaFilmes);
                salvarFilmesNoArquivo(listaFilmes, nomeArquivo);
                break;
            case 2:
                exibirFilmes(listaFilmes);
                break;
            case 3:
                printf("Digite o ID do filme que deseja excluir: ");
                scanf("%d", &id);
                getchar();  // Limpar o buffer
                excluirFilme(&listaFilmes, id);
                salvarFilmesNoArquivo(listaFilmes, nomeArquivo);
                break;
            case 4:
                printf("Digite o ID do filme que deseja editar: ");
                scanf("%d", &id);
                getchar();  // Limpar o buffer
                editarFilme(listaFilmes, id);
                salvarFilmesNoArquivo(listaFilmes, nomeArquivo);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}