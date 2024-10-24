#include "cinema.h"

int obterOpcaoMenu(){
    char entrada[50]; 
    int opcao = -1;

    while (1)
    {
        printf("Digite uma opção do menu: ");
        fgets(entrada, 50, stdin);             
        entrada[strcspn(entrada, "\n")] = '\0'; 

        if (apenasNumeros(entrada))
        {
            opcao = atoi(entrada); 
            break;
        }
        else
        {
            printf("Entrada inválida! Por favor, insira um número.\n");
        }
    }

    return opcao;
}

void obterData(char *data){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int apenasLetras(const char *str){
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]) && str[i] != ' ')
        {
            return 0; 
        }
    }
    return 1;
}

int apenasNumeros(const char *str){
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; 
        }
    }
    return 1; 
}

void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt) {
    char entradaTemp[tamanho];

    while (1) {
        printf("%s", prompt);
        fgets(entradaTemp, tamanho, stdin);
        entradaTemp[strcspn(entradaTemp, "\n")] = 0; 

        if (strlen(entradaTemp) > 0 && apenasLetras(entradaTemp)) {
            strcpy(buffer, entradaTemp);
            break;
        } else {
            printf("Entrada inválida! Por favor, insira apenas letras.\n");
        }
    }
}

void obterTipoSolicitante(Usuario *pedido) {
    int opcao;
    while (1) {
        printf("Tipo de solicitante:\n 1. Aluno\n 2. Professor\n 3. Funcionário\n Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        if (opcao == 1) {
            strcpy(pedido->tipoSolicitante, "Aluno");
            break;
        } else if (opcao == 2) {
            strcpy(pedido->tipoSolicitante, "Professor");
            break;
        } else if (opcao == 3) {
            strcpy(pedido->tipoSolicitante, "Funcionário");
            break;
        } else {
            printf("Opção inválida! Por favor, escolha 1, 2 ou 3.\n");
        }
    }
}

void obterQuantidadePaginas(int *quantidade) {
    char entrada[10];

    while (1) {
        printf("Quantidade de páginas: ");
        fgets(entrada, sizeof(entrada), stdin);

        entrada[strcspn(entrada, "\n")] = 0; 

        if (apenasNumeros(entrada)) {
            *quantidade = atoi(entrada);
            break; 
        } else {
            printf("Entrada inválida! Por favor, insira apenas números.\n");
        }
    }
}

void Status(char *status) {
    int escolha = 0;
    char entrada[3]; 

    while (1) {
        printf("Escolha o status:\n");
        printf(" 1. Pendente\n");
        printf(" 2. Concluído\n");
        printf(" 3. Cancelado\n");
        printf(" Digite a opção (1-3): ");
        fgets(entrada, sizeof(entrada), stdin); 

        if (entrada[0] == '\n') { 
            return;
        }

        escolha = atoi(entrada);

        switch (escolha) {
            case 1:
                strcpy(status, "Pendente");
                return;
            case 2:
                strcpy(status, "Concluído");
                return;
            case 3:
                strcpy(status, "Cancelado");
                return;
            default:
                printf("\nEscolha inválida! Tente novamente.\n");
                break;
        }
    }
}

void salvarUsuarioNoArquivo(Usuario* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Usuario* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "ID: %d\n", atual->id);
        fprintf(arquivo, "Nome: %s\n", atual->nome);
        fprintf(arquivo, "Email: %s\n", atual->email);
        fprintf(arquivo, "Senha: %s\n", atual->senha);
        fprintf(arquivo, "Idade: %d\n", atual->idade);
        fprintf(arquivo, "-----------------------------------\n");
        atual = atual->proximo;
    }

    fclose(arquivo); 
}

void carregarUsuariosDoArquivo(Usuario** lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Criando um novo arquivo.\n");
        return; 
    }

    Usuario* novoUsuario;
    while (1) {
        novoUsuario = (Usuario*) malloc(sizeof(Usuario));
        if (fscanf(arquivo, "ID: %d\n", &novoUsuario->id) != 1) {
            free(novoUsuario);
            break; 
        }
        fscanf(arquivo, "Nome: %[^\n]\n", novoUsuario->nome);
        fscanf(arquivo, "Email: %[^\n]\n", novoUsuario->email);
        fscanf(arquivo, "Senha: %[^\n]\n", &novoUsuario->senha);
        fscanf(arquivo, "Idade: %d\n", &novoUsuario->idade);
        fscanf(arquivo, "-----------------------------------\n"); 
        novoUsuario->proximo = NULL;
        inserirUsuarioNaLista(lista, novoUsuario);
    }
    fclose(arquivo);
}


void inserirUsuarioNaLista(Usuario** lista, Usuario* novoUsuario) {
    if (*lista == NULL) {
        *lista = novoUsuario; 
    } else {
        Usuario* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;  
        }
        atual->proximo = novoUsuario;  
    }
}

void cadastrarUsuario(Usuario ** lista){
    Usuario * novoUsuario = (Usuario*)malloc(sizeof(Usuario));
    if (novoUsuario == NULL){
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    printf("Digite seu nome de usuario: ");
    fgets(novoUsuario->nome, sizeof(novoUsuario->nome), stdin);
    novoUsuario->nome[strcspn(novoUsuario->nome, "\n")] = '\0';

    printf("Digite seu nome de usuario: ");
    fgets(novoUsuario->nome, sizeof(novoUsuario->nome), stdin);
    novoUsuario->nome[strcspn(novoUsuario->nome, "\n")] = '\0';

 printf("Digite o e-mail do usuário: ");
    fgets(novoUsuario->email, sizeof(novoUsuario->email), stdin);
    novoUsuario->email[strcspn(novoUsuario->email, "\n")] = '\0';

    printf("Digite a senha do usuário: ");
    fgets(novoUsuario->senha, sizeof(novoUsuario->senha), stdin);
    novoUsuario->senha[strcspn(novoUsuario->senha, "\n")] = '\0';

    printf("Digite a idade do usuário: ");
    scanf("%d", &novoUsuario->idade);
    getchar(); // Limpar o buffer

    novoUsuario->proximo = NULL;

    // Atribuir um ID ao novo usuário
    if (*lista == NULL) {
        novoUsuario->id = 1;
        *lista = novoUsuario;
    } else {
        Usuario* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        novoUsuario->id = atual->id + 1;
        atual->proximo = novoUsuario;
    }

    printf("Usuário criado com sucesso! ID do usuário: %d\n", novoUsuario->id);
}

void exibirUsuarios(Usuario *lista) {
    Usuario *atual = lista;
    if (atual == NULL) {
        printf("\nNenhum pedido armazenado.\n");
        return;
    }

    printf("\n-----------------------------\n");

    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Nome: %s\n", atual->nome);
        printf("Email: %s\n", atual->email);
        printf("Idade: %d\n", atual->idade);
        printf("-----------------------------\n");
        atual = atual->proximo;
    }
}

void excluirPedido(Usuario** lista) {
    char entrada[15];
    int numeroExcluir;

    if(*lista == NULL){
        printf("Nenhum pedido para excluir!\n");
        return;
    }

    Usuario* atual = *lista;
    Usuario* anterior = NULL;
    
    printf("\nDigite o número do pedido que deseja excluir: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = 0; 

    if (apenasNumeros(entrada)) {
        numeroExcluir = atoi(entrada); 
    } else {
        printf("Entrada inválida! Digite apenas números.\n");
        return;  
    }

    while (atual != NULL && atual->numero != numeroExcluir) {
        anterior = atual; 
        atual = atual->proximo; 
    }

    if (atual == NULL) {
        printf("Usuario com número %d não encontrado.\n", numeroExcluir);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->proximo; 
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual); 

    Usuario *aux = *lista;
    int novoNumero = 1;

    while(aux != NULL){
        aux->numero = novoNumero;
        novoNumero ++;
        aux = aux->proximo;
    }
    printf("Usuario com número %d excluído com sucesso.\n", numeroExcluir);
}

void editarPedido(Usuario *lista) {
    char entrada[15];
    int numeroPedido;

    if (lista == NULL) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }

    printf("\nDigite o número do pedido que deseja editar: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';    
    if (apenasNumeros(entrada)) {
        numeroPedido = atoi(entrada); 
    } else {
        printf("Entrada inválida! Digite apenas números.\n");
        return; 
    }

    Usuario *atual = lista;

    while (atual != NULL && atual->numero != numeroPedido) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Usuario com o número %d não encontrado.\n", numeroPedido);
        return;
    }

    int opcao;
    do {
        printf("\nEditando pedido #%d:\n", numeroPedido);
        printf(" 1. Editar quantidade de páginas (atual: %d)\n", atual->quantidadePaginas);
        printf(" 2. Editar Status do Usuario (Atual: %s)\n", atual->status);
        printf(" 3. Sair da Edição\n"); 
        printf(" Escolha uma opção: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = 0; 

        if (apenasNumeros(entrada)) {
            opcao = atoi(entrada); 
        } else {
            printf("Entrada inválida! Digite apenas números.\n");
            continue; 
        }

        switch (opcao) {
            case 1:
                obterQuantidadePaginas(&atual->quantidadePaginas);
                break;
            case 2:
                Status(atual->status); 
                break;
            case 3:
                printf("Saindo da edição.\n");
                break;
            default:
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
                break;
        }
    } while (opcao != 3);

    printf("Edição concluída com sucesso!\n");
}


void buscarPedido(Usuario * lista){
    if(lista == NULL){
        printf("Nenhum pedido encontrado!\n");
        return;
    }

    char entrada[15];
    int numeroPedido, encontrado = 0;
    Usuario *atual = lista;

    printf("\nDigite o número ou nome do solicitante: ");
    scanf(" %[^\n]", entrada);
    getchar();

    if (apenasNumeros(entrada)) {
        numeroPedido = atoi(entrada);
        while(atual != NULL){
            if(atual->numero == numeroPedido){
                printf("\nPedido #%d\n", atual->numero);
                printf("Solicitante: %s\n", atual->nomeSolicitante);
                printf("Tipo de solicitante: %s\n", atual->tipoSolicitante);
                printf("Quantidade de páginas: %d\n", atual->quantidadePaginas);
                printf("Data do pedido: %s\n", atual->dataPedido);
                printf("Valor total: R$ %.2f\n", atual->valorTotal);
                printf("Status: %s\n", atual->status);
                encontrado = 1;
                break;
            }
            atual = atual->proximo;
        }
    } else {
        while(atual != NULL){
            char nomeSolicitanteLower[50], entradaLower[50];

            strcpy(nomeSolicitanteLower, atual->nomeSolicitante);
            strcpy(entradaLower, entrada);

            for(int j = 0; nomeSolicitanteLower[j]; j++){
                nomeSolicitanteLower[j] = tolower(nomeSolicitanteLower[j]);
            }
            for(int j = 0; entradaLower[j]; j++){
                entradaLower[j] = tolower(entradaLower[j]);
            }
            
            if (strstr(nomeSolicitanteLower, entradaLower) != NULL) {
                            printf("\nPedido #%d\n", atual->numero);
                            printf("Solicitante: %s\n", atual->nomeSolicitante);
                            printf("Tipo de solicitante: %s\n", atual->tipoSolicitante);
                            printf("Quantidade de páginas: %d\n", atual->quantidadePaginas);
                            printf("Data do pedido: %s\n", atual->dataPedido);
                            printf("Valor total: R$ %.2f\n", atual->valorTotal);
                            printf("Status: %s\n", atual->status);
                            encontrado = 1;
            }
            atual = atual->proximo;
        }
    }
    if(!encontrado){
        printf("Nenhum pedido encontrado!\n");
    }
}

void consultarPedidoPorStatus(Usuario * lista){
    if(lista == NULL){
        printf("Nenhum pedido registrado!\n");
        return;
    }

    char status[15];
    int encontrado = 0;
    Usuario * atual = lista;

    Status(status);

    printf("\n---- | Pedidos com status %s | ----\n", status);

    while(atual != NULL){
        if (strcasecmp(atual->status, status) == 0){
            printf("\nPedido #%d\n", atual->numero);
            printf("Solicitante: %s\n", atual->nomeSolicitante);
            printf("Tipo de solicitante: %s\n", atual->tipoSolicitante);
            printf("Quantidade de páginas: %d\n", atual->quantidadePaginas);
            printf("Data do pedido: %s\n", atual->dataPedido);
            printf("Valor total: R$ %.2f\n", atual->valorTotal);
            printf("Status: %s\n", atual->status);
            encontrado = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrado){
        printf("Nenhum pedido com status %s encontrado.\n", status);
    }
}

void consultarTotalCopiasValor(Usuario *lista){
    if(lista == NULL){
        printf("Nenhum pedido registrado!\n");
        return;
    }

    int totalCopias = 0;
    float totalValor = 0;
    Usuario * atual = lista;

    while(atual != NULL){
        totalCopias += atual->quantidadePaginas;
        totalValor += atual->valorTotal;
        atual = atual->proximo;
    }
    printf("\nTotal de cópias: %d\n", totalCopias);
    printf("Valor arrecadado: R$ %.2f\n", totalValor);
}