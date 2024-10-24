#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


// Definição da struct de Pedido
typedef struct Usuario{
    int id;
    char nome[50];
    char senha[50];
    char email[80];
    int idade;
    struct Usuario * proximo;
} Usuario;

// Função para capturar e validar a entrada
int obterOpcaoMenu();

// Função para obter a data atual dd/mm/yyyy
void obterData(char *data); 

// Função para verificar se a string contém apenas letras
int apenasLetras(const char *str);

// Função para verificar se a string contém apenas números
int apenasNumeros(const char *str);

// Função para obter uma entrada apenas com caracteres
void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt);

// Função para obter o tipo de solicitante
void obterTipoSolicitante(Usuario *pedido);

// Função para obter a quantidade de páginas
void obterQuantidadePaginas(int *quantidade);

// Função para obter o novo status do pedido
void Status(char *status);

// Função para salvar pedidos no arquivo
void salvarPedidoNoArquivo(Usuario* lista, const char* nomeArquivo);

// Carrega os pedidos existentes do arquivo
void carregarPedidosDoArquivo(Usuario** lista, const char* nomeArquivo);

// Função para inserir um pedido na lista encadeada
void inserirUsuarioNaLista(Usuario** lista, Usuario* novoPedido);

// Função para adicionar um pedido
void adicionarPedido(Usuario** lista);

// Função para listar os pedidos
void exibirUsuarios(Usuario *lista);

// Função para excluir um pedido e atualizar os números
void excluirPedido(Usuario** lista);

// Função para editar um pedido 
void editarPedido(Usuario *lista);

// Função para buscar pedido por número ou nome
void buscarPedido(Usuario * lista);

// Função para consultar pedidos por status
void consultarPedidoPorStatus(Usuario * lista);

// Função para consultar total de copias realizadas e o valor arrecado 
void consultarTotalCopiasValor(Usuario *lista);