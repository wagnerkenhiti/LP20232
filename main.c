#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "apresentacao.h"
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
    int opcao;
    //char msg[50];
    DATA d1, d2;

    printf("Data 1\n");
    printf("\tDia ->");
    scanf(" %d", &d1.dia);
    printf("\tMês ->");
    scanf(" %d", &d1.mes);
    printf("\tAno ->");
    scanf(" %d", &d1.ano);

    printf("Data 2\n");
    printf("\tDia ->");
    scanf(" %d", &d2.dia);
    printf("\tMês ->");
    scanf(" %d", &d2.mes);
    printf("\tAno ->");
    scanf(" %d", &d2.ano);

    int resp = DataCmp(d1,d2);
    switch (resp)    
    {
    case 0: printf("Datas iguais\n");            
        break;
    
    case -1: printf("Data 1 menos recente que Data 2\n");            
        break;
    
    case 1: printf("Data 1 mais recente que Data 2\n");            
        break;
    default:
        break;
    }
    getchar();
        
    lerProduto(&produto);
    produto.id = obterProximoIdProduto();
    exibirProduto(produto);
    //gravarProdutoCSV(produto);
    getchar();
    do
    {
        opcao = MenuPrincipal();
        switch (opcao)
        {
        case 3:
            lista = (PRODUTO *)malloc(sizeof(PRODUTO) * 10);
            int qtdeProdutos = lerProdutosCSV(lista);
            printf("Quantidade de registros: %d\n", qtdeProdutos);
            for (int i = 0; i < qtdeProdutos; i++)
            {
                separador();
                printf("Produto %d\n", i + 1);
                separador();
                exibirProduto(lista[i]);
                gravarProdutoDAT(lista[i]);
                separador();
            }
            free(lista);
            lista = (PRODUTO *)malloc(sizeof(PRODUTO) * 10);
            int qtdeBin;
            qtdeBin = lerProdutosDAT(lista);
            printf("Quantidade de registros (binário): %d\n", qtdeBin);     
            getchar();  
            getchar();     
            break;
        default:
            break;
        }
    } while (opcao != 9);
}
