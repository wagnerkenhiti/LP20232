#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "apresentacao.h"
#include "vendas.h"
#include "cliente.h"
#include "tempo.h"

/*************************************************************************************/

/*************************************************************************************/
/**
 * Main para teste das funções
 */
int main(int argc, char const *argv[])
{
    PRODUTO produto;
    CLIENTE cliente;
    int opcao;

    do
    {
        opcao = MenuPrincipal();
        switch (opcao)
        {

        case 1:
            int opcao1;
            do
            {
                opcao1 = MenuVenda();
                switch (opcao1)
                {
                case 1:
                    char cpfVenda[15];
                    printf("Digite o CPF do cliente que deseja cadastrar a compra: ");
                    scanf(" %s", cpfVenda);

                    if (verificaClienteDAT(cpfVenda) == -1)
                    {
                        printf("Cadastrando cliente!\n");
                        CLIENTE clienteVenda;
                        adicionarCliente(&clienteVenda);
                        exibirCliente(clienteVenda);
                        int h = 0;
                        printf("Dados do cliente acima. Para confirmar cadastro, digite 1. Caso contrario, os dados serao invalidados e nao serao salvos: ");
                        scanf(" %d", &h);
                        if (h == 1)
                        {
                            printf("Cliente cadastrado!\n");
                            gravarClienteCSV(clienteVenda);
                            gravarClienteDAT(clienteVenda);
                        }
                    }
                    IniciarCompra(cpfVenda);


                    break;

                case 2:
                    break;
                default:
                    break;
                }
            } while (opcao1 != 9);

            break;

        case 2:

            int opcao2;
            do
            {
                opcao2 = MenuClientes();
                switch (opcao2)
                {
                case 1:
                    adicionarCliente(&cliente);
                    exibirCliente(cliente);
                    int a = 0;
                    printf("Dados do cliente acima. Para confirmar cadastro, digite 1. Caso contrario, os dados serao invalidados e nao serao salvos: ");
                    scanf(" %d", &a);
                    if (a == 1)
                    {
                        printf("Cliente cadastrado!\n");
                        gravarClienteCSV(cliente);
                        gravarClienteDAT(cliente);
                    }
                    getchar();
                    break;

                case 2:
                    printf("Pontuacao atualizada!\n");
                    break;
                case 3:
                    char cpfTemp[30];
                    printf("***EDICAO DE CLIENTE***\n");
                    printf("Digite o CPF do cliente que deseja alterar: ");
                    scanf(" %s", cpfTemp);
                    int linhaEd = verificaClienteDAT(cpfTemp);
                    if (linhaEd < 0)
                        break;
                    adicionarCliente(&cliente);
                    editaClienteDAT(linhaEd, cliente);

                    break;
                case 4:
                    mostrarClientesDAT();
                    break;
                case 5:
                    break;
                case 6:
                    break;

                default:
                    break;
                }
            } while (opcao2 != 9);

            break;

        case 3:

            int opcao3;
            do
            {
                opcao3 = MenuProdutos();
                switch (opcao3)
                {
                case 1:
                    printf("Cadastrando um produto: \n");
                    lerProduto(&produto);
                    exibirProduto(produto);
                    int b = 0;
                    printf("Dados do produto acima. Para confirmar cadastro, digite 1. Caso contrario, os dados serao invalidados e nao serao salvos: ");
                    scanf(" %d", &b);
                    if (b == 1)
                    {
                        printf("Produto cadastrado!\n");
                        produto.id = obterProximoIdProduto();
                        gravarProdutoCSV(produto);
                        gravarProdutoDAT(produto);
                    }

                    getchar();

                    break;

                case 2:

                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    break;
                }
            } while (opcao3 != 9);

            break;
        default:
            break;
        }
    } while (opcao != 9);

    printf("\nSaindo do programa!\n");
    return 0;
}
