#include "cinema.h"

int main(){
    Usuario * listaUsuario = NULL;
    const char* nomeArquivo = "pedidos.txt";

    carregarPedidosDoArquivo(&listaUsuario, nomeArquivo);

    int quantidadePaginas, opcao, numeroPedido = 1;
    char nome[50], tipoSolicitante[20], status[15];

    do{
        printf("\n----- | Menu de Pedidos | -----\n\n");
        printf("1. Adicionar pedido\n");
        printf("2. Listar pedidos\n");
        printf("3. Excluir pedido\n");
        printf("4. Editar pedido\n");
        printf("5. Buscar pedido por número ou nome\n");
        printf("6. Consultar pedidos por status\n");
        printf("7. Consultar total de cópias e valor arrecadado\n");
        printf("8. Sair\n\n");

        opcao = obterOpcaoMenu();

        switch(opcao){
            case 1:
                adicionarPedido(&listaUsuario);
                salvarPedidoNoArquivo(listaUsuario, nomeArquivo);
                break;
            case 2:
                exibirPedidos(listaUsuario);
                break;
            case 3:
                excluirPedido(&listaUsuario);
                salvarPedidoNoArquivo(listaUsuario, nomeArquivo);
                break;
            case 4: 
                editarPedido(listaUsuario);
                salvarPedidoNoArquivo(listaUsuario, nomeArquivo);
                break;
            case 5:
                buscarPedido(listaUsuario);
                break;
            case 6: 
                consultarPedidoPorStatus(listaUsuario);
                break;
            case 7:
                consultarTotalCopiasValor(listaUsuario);
                break;
            case 8:
                salvarPedidoNoArquivo(listaUsuario, nomeArquivo);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }while(opcao != 8);
    return 0;
}