#include "cinema.h"

// Ponteiros para os cabeçalhos das listas
Filme *cabecalhoFilmes = NULL;
Usuario *cabecalhoUsuarios = NULL;
Usuario usuarioAtual;

bool verificarEmail(const char *email) {
    if (strchr(email, '@') == NULL || strlen(email) >= 80) {
        return false;
    }
    Usuario *atual = cabecalhoUsuarios;
    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0) {
            return false;
        }
        atual = atual->proximo;
    }
    return true;
}

void cadastrarUsuario(Usuario *usuario) {
    char email[80];
    printf("Digite seu nome de usuario: ");
    fgets(usuario->nome, sizeof(usuario->nome), stdin);
    strtok(usuario->nome, "\n");

    printf("Digite sua senha: ");
    fgets(usuario->senha, sizeof(usuario->senha), stdin);
    strtok(usuario->senha, "\n");

    while (true) {
        printf("Digite seu e-mail: ");
        fgets(email, sizeof(email), stdin);
        strtok(email, "\n");

        if (verificarEmail(email)) {
            strcpy(usuario->email, email);
            break;
        } else {
            printf("E-mail inválido ou já cadastrado. Tente novamente.\n");
        }
    }

    printf("Digite sua idade: ");
    scanf("%d", &usuario->idade);
    getchar();  // Consome o newline após o scanf

    // Adiciona o novo usuário à lista encadeada
    usuario->proximo = cabecalhoUsuarios;
    cabecalhoUsuarios = usuario;

    printf("Cadastro realizado com sucesso!\n");
}

void salvarUsuarios() {
    FILE *arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Usuario *atual = cabecalhoUsuarios;
    while (atual != NULL) {
        fwrite(atual, sizeof(Usuario), 1, arquivo);
        atual = atual->proximo;
    }

    fclose(arquivo);
}

void carregarUsuarios() {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Usuario *usuario = malloc(sizeof(Usuario));
    while (fread(usuario, sizeof(Usuario), 1, arquivo)) {
        usuario->proximo = cabecalhoUsuarios;
        cabecalhoUsuarios = usuario;
        usuario = malloc(sizeof(Usuario));  // Aloca novo espaço para o próximo
    }

    free(usuario);  // Libera o último espaço alocado que não foi usado
    fclose(arquivo);
}

void cadastrarFilme() {
    Filme *filme = malloc(sizeof(Filme));
    if (filme == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    printf("Digite o nome do filme: ");
    fgets(filme->nome, sizeof(filme->nome), stdin);
    strtok(filme->nome, "\n");

    printf("Digite o genero do filme: ");
    fgets(filme->genero, sizeof(filme->genero), stdin);
    strtok(filme->genero, "\n");

    printf("Digite o ano de lancamento: ");
    scanf("%d", &filme->ano);
    getchar();

    printf("Digite a faixa etaria do filme: ");
    scanf("%d", &filme->faixaEtaria);
    getchar();

    // Adiciona o novo filme à lista encadeada
    filme->proximo = cabecalhoFilmes;
    cabecalhoFilmes = filme;

    printf("Filme '%s' cadastrado com sucesso!\n", filme->nome);
}

void salvarFilmes() {
    FILE *arquivo = fopen("filmes.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Filme *atual = cabecalhoFilmes;
    while (atual != NULL) {
        fwrite(atual, sizeof(Filme), 1, arquivo);
        atual = atual->proximo;
    }

    fclose(arquivo);
}

void carregarFilmes() {
    FILE *arquivo = fopen("filmes.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Filme *filme = malloc(sizeof(Filme));
    while (fread(filme, sizeof(Filme), 1, arquivo)) {
        filme->proximo = cabecalhoFilmes;
        cabecalhoFilmes = filme;
        filme = malloc(sizeof(Filme));  // Aloca novo espaço para o próximo
    }

    free(filme);  // Libera o último espaço alocado que não foi usado
    fclose(arquivo);
}

void listarFilmes() {
    Filme *atual = cabecalhoFilmes;
    if (atual == NULL) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    while (atual != NULL) {
        printf("Nome: %s, Genero: %s, Ano: %d, Faixa etaria: %d\n",
               atual->nome, atual->genero, atual->ano, atual->faixaEtaria);
        atual = atual->proximo;
    }
}

void editarFilme() {
    listarFilmes();
    char nome[100];
    printf("Digite o nome do filme que deseja editar: ");
    fgets(nome, sizeof(nome), stdin);
    strtok(nome, "\n");

    Filme *atual = cabecalhoFilmes;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Digite o novo nome do filme (ou pressione Enter para manter '%s'): ", atual->nome);
            char novoNome[100];
            fgets(novoNome, sizeof(novoNome), stdin);
            strtok(novoNome, "\n");
            if (strlen(novoNome) > 0) {
                strcpy(atual->nome, novoNome);
            }

            printf("Digite o novo genero do filme (ou pressione Enter para manter '%s'): ", atual->genero);
            char novoGenero[50];
            fgets(novoGenero, sizeof(novoGenero), stdin);
            strtok(novoGenero, "\n");
            if (strlen(novoGenero) > 0) {
                strcpy(atual->genero, novoGenero);
            }

            printf("Digite o novo ano de lancamento (ou pressione Enter para manter %d): ", atual->ano);
            char novoAnoStr[10];
            fgets(novoAnoStr, sizeof(novoAnoStr), stdin);
            if (strlen(novoAnoStr) > 1) {
                int novoAno = atoi(novoAnoStr);
                atual->ano = novoAno;
            }

            printf("Digite a nova faixa etaria (ou pressione Enter para manter %d): ", atual->faixaEtaria);
            char novaFaixaEtariaStr[10];
            fgets(novaFaixaEtariaStr, sizeof(novaFaixaEtariaStr), stdin);
            if (strlen(novaFaixaEtariaStr) > 1) {
                int novaFaixaEtaria = atoi(novaFaixaEtariaStr);
                atual->faixaEtaria = novaFaixaEtaria;
            }

            printf("Filme atualizado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Filme não encontrado.\n");
}

void excluirFilme() {
    listarFilmes();
    char nome[100];
    printf("Digite o nome do filme que deseja excluir: ");
    fgets(nome, sizeof(nome), stdin);
    strtok(nome, "\n");

    Filme **atual = &cabecalhoFilmes;
    while (*atual != NULL) {
        if (strcmp((*atual)->nome, nome) == 0) {
            Filme *filmeParaExcluir = *atual;
            *atual = filmeParaExcluir->proximo;
            free(filmeParaExcluir);
            printf("Filme excluído com sucesso!\n");
            return;
        }
        atual = &(*atual)->proximo;
    }
    printf("Filme não encontrado.\n");
}

void exibirDetalhesFilme() {
    listarFilmes();
    char nome[100];
    printf("Digite o nome do filme para ver os detalhes: ");
    fgets(nome, sizeof(nome), stdin);
    strtok(nome, "\n");

    Filme *atual = cabecalhoFilmes;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Detalhes do filme:\n");
            printf("Nome: %s\n", atual->nome);
            printf("Genero: %s\n", atual->genero);
            printf("Ano: %d\n", atual->ano);
            printf("Faixa etaria: %d\n", atual->faixaEtaria);
            return;
        }
        atual = atual->proximo;
    }
    printf("Filme não encontrado.\n");
}

bool login() {
    char nome[50];
    char senha[50];
    printf("Nome de usuario: ");
    fgets(nome, sizeof(nome), stdin);
    strtok(nome, "\n");

    printf("Senha: ");
    fgets(senha, sizeof(senha), stdin);
    strtok(senha, "\n");

    Usuario *atual = cabecalhoUsuarios;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0 && strcmp(atual->senha, senha) == 0) {
            usuarioAtual = *atual;
            return true;
        }
        atual = atual->proximo;
    }
    printf("Login falhou. Tente novamente.\n");
    return false;
}

void mensagemBoasVindas(const Usuario *usuario) {
    printf("Bem-vindo, %s!\n", usuario->nome);
}

void menu() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Filme\n");
        printf("2. Listar Filmes\n");
        printf("3. Editar Filme\n");
        printf("4. Excluir Filme\n");
        printf("5. Exibir Detalhes do Filme\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Consome o newline após o scanf

        switch (opcao) {
            case 1:
                cadastrarFilme();
                break;
            case 2:
                listarFilmes();
                break;
            case 3:
                editarFilme();
                break;
            case 4:
                excluirFilme();
                break;
            case 5:
                exibirDetalhesFilme();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);
}