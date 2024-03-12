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
                        else
                        {
                            printf("Cadastro do cliente cancelado!\n");
                            break;
                        }
                    }
                    IniciarCompra(cpfVenda);

                    break;

                case 2:
                    VENDA todasVendas[200];
                    int u = lerVendasDAT(todasVendas);
                    if (u > 0)
                        for (int i = 0; i < u; i++)
                        {
                            exibirVendas(todasVendas[i]);
                        }

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
                    CLIENTE todosClientes[200];
                    VENDA todasVendas[200];
                    int u = lerVendasAttDAT(todasVendas);
                    int n = lerClientesDAT(todosClientes);
                    for (int i = 0; i < u; i++)
                    {
                        lerClientesDAT(todosClientes);
                        for (int j = 0; j < n; j++)
                        {   
                            if (!strcmp(todasVendas[i].CPF, todosClientes[j].CPF))
                            {
                                cliente = todosClientes[j];
                                AdicionarPontosCliente(&cliente, (int)todasVendas[i].valorTotal);
                                int linhaEd = verificaClienteDAT(cliente.CPF);
                                editaClienteDAT(linhaEd, cliente);
                                break;
                            }
                        }
                    }
                    system("rm VendasAttPontos.dat");
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
                    n = lerClientesDAT(todosClientes);
                    for (int i = 0; i < n; i++)
                    {
                        if (todosClientes[i].idade <= 25 && todosClientes[i].idade >= 18)
                        {
                            exibirCliente(todosClientes[i]);
                        }
                    }
                    break;
                case 6:
                    n = lerClientesDAT(todosClientes);
                    for (int i = 0; i < n; i++)
                    {
                        if (todosClientes[i].pontos > 1000)
                        {
                            exibirCliente(todosClientes[i]);
                        }
                    }
                    break;
                case 7:
                    char cpfNome[50];
                    printf("Digite o CPF ou o nome do cliente que deseja procurar: ");
                    scanf(" %[^\n]s", cpfNome);
                    n = lerClientesDAT(todosClientes);
                    int i = 0;
                    for (; i < n; i++)
                    {
                        if (!strcmp(todosClientes[i].nome, cpfNome))
                        {
                            strcpy(cpfNome, todosClientes[i].CPF);
                            i = n;
                        }
                    }
                    u = lerVendasDAT(todasVendas);
                    for (int i = 0; i < u; i++)
                    {
                        if (!strcmp(todasVendas[i].CPF, cpfNome))
                        {
                            char data[50];
                            DataToString(todasVendas[i].dataCompra, data, false);
                            printf("Data que o produto foi comprado: %s\n", data);
                            printf("Valor total da compra: ");
                            printf("%.2f\n", todasVendas[i].valorTotal);
                            printf("Quantidade total de produtos: ");
                            printf("%d\n", todasVendas[i].quantidadeProdutos);
                            separador();
                        }
                    }

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

                    printf("***EDICAO DE PRODUTO***\n");
                    int id;
                    printf("Digite o ID do produto que deseja alterar: ");
                    scanf(" %d", &id);
                    int linhaEd = verificaProdutoDAT(id);
                    if (linhaEd < 0)
                        break;
                    produto.id = id;
                    lerProduto(&produto);
                    editaProdutoDAT(linhaEd, produto);
                    break;

                case 3:

                    PRODUTO todosProdutos[200];
                    int k = lerProdutosDAT(todosProdutos);
                    char setor[50];
                    printf("Digite o setor que deseja consultar quantos itens ha no estoque: ");
                    scanf(" %s", setor);
                    int soma = 0;
                    for (int i = 0; i < k; i++)
                    {
                        if (strcmp(todosProdutos[i].setor, setor) == 0)
                        {
                            soma += todosProdutos[i].estoque;
                            exibirProduto(todosProdutos[i]);
                        }
                    }
                    if (!soma)
                        printf("Nao ha nenhum produto no setor digitado ou setor digitado incorretamente");
                    printf("A soma dos estoques do setor digitado e %d\n", soma);
                    break;

                case 4:
                    k = lerProdutosDAT(todosProdutos);
                    for (int i = 0; i < k; i++)
                    {
                        if (todosProdutos[i].estoque <= 5)
                            exibirProduto(todosProdutos[i]);
                    }

                    break;
                case 5:
                    k = lerProdutosDAT(todosProdutos);
                    for (int i = 0; i < k; i++)
                    {
                        exibirProduto(todosProdutos[i]);
                    }
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
