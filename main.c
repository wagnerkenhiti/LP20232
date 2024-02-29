#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "apresentacao.h"
#include "cliente.h"
#include "tempo.h"

/*************************************************************************************/

/*************************************************************************************/
/**
 * Main para teste das funções
 */
int main(int argc, char const *argv[])
{
    /* code */
    PRODUTO *lista;
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
                    }
                    getchar();
                    break;

                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
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

                    lerProduto(&produto);
                    produto.id = obterProximoIdProduto();
                    exibirProduto(produto);
                    gravarProdutoCSV(produto);
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
