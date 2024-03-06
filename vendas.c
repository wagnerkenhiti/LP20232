#include "vendas.h"
#include "cliente.h"
#include "produtos.h"
#include "tempo.h"
#include "apresentacao.h"

#include <stdio.h>
#include <string.h>
void IniciarCompra(char cpf[])
{
    // Iniciando uma nova compra (Não consegui colocar o CPF, em v.CPF)

    // Iniciando ItensCompra (não cosnegui iniciar)

    // Busca cliente pelo CPF (Não consegui colocar o CPF, em v.CPF)

    // Verifica se o cliente está cadastrado, caso de verdadeiro, irá cadasta-lo

    VENDA v;
    v.identificacaoVenda = ProximoIdVenda();
    strcpy(v.CPF, cpf);
    v.dataCompra = hoje();
    v.valorTotal = 0;
    v.quantidadeProdutos = 0;

    int opcao;
    do
    {
        opcao = MenuCompra();
        int id;

        // Leitura do código do produto
        printf("Código do produto: ");
        scanf(" %d", &id);

        // Exibir tela com as informações: nome, preço, qtd em estoque

        // Verifica se o produto está em estoque e adiciona a compra
        int quantidadeDisponivel, quantidade;
        // Fazer uma função para ler a quantidade de prodoutos disponivel
        float precoUnitario;
        float *precoUnitarioP = &precoUnitario;
        quantidadeDisponivel = RetornaQuantidade(id, precoUnitarioP);
        if (quantidadeDisponivel == -1)
        {
            printf("ID do produto nao reconhecido\n");
            return;
        }
        else if (quantidadeDisponivel == 0)
            printf("Produto em falta.\n");
        else
        {
            printf("Quantidade: ");
            scanf(" %d", &quantidade);
            while (quantidade > quantidadeDisponivel)
            {
                printf("Quantidade acima do disponivel.\n");
                printf("Para adicionar a compra, digitar um número disponivel de produto,caso, não queira adicionar ao carrinho digitar 0");
                scanf(" %d", &quantidade);
            }

            v.quantidadeProdutos = v.quantidadeProdutos + quantidade;
            v.valorTotal += precoUnitario * quantidade;
            gravarVendaDAT(v);
            gravarVendaCSV(v);
        }

        // Baixar do estoque
    } while (opcao != 2);

    // Verifica se o cliente comprou algo, caso positivo, grava dados em Vendas.csv
    if (v.quantidadeProdutos != 0)
    {
    }
}

/**
 * Grava dados de uma venda em texto, caso o arquivo não exista, cria ele
 * @param v Venda salvo no registro
 */
int gravarVendaCSV(VENDA v)
{
    char nomeArquivo[] = "Vendas.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r+w");

    // Criar arquivo caso não exista
    if (csv == NULL)
    {
        printf("Criando arquivo %s\n", nomeArquivo);
        csv = fopen(nomeArquivo, "a");
        fprintf(csv, "Id;CPF;Data da compra;Valor total;Itens");
        fflush(csv);
    }

    // Gravar novos dados
    if (csv != NULL)
    {
        fseek(csv, 0, SEEK_END);
        fprintf(csv, "%d;%s;%d/%d/%d;%.2f;%d;0\n", v.identificacaoVenda, v.CPF,
                v.dataCompra.dia, v.dataCompra.mes, v.dataCompra.ano, v.valorTotal, v.quantidadeProdutos);
        fflush(csv);
        fclose(csv);
    }

    return 0;
}

/**
 * Grava dados de uma venda em binário, caso o arquivo
 * não exista, cria ele
 * @param v Venda salvo no registro
 */
int gravarVendaDAT(VENDA v)
{
    char nomeArquivo[] = "Vendas.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "a+b");

    // Caso o arquivo não exista, sria ele
    if (dat == NULL)
    {
        printf("Criando arquivo %s\n", nomeArquivo);
        dat = fopen(nomeArquivo, "ab");
    }

    // Adiciona dados
    if (dat != NULL)
    {
        fwrite(&v, sizeof(VENDA), 1, dat);
        fflush(dat);
        fclose(dat);
    }

    return 0;
}

int RetornaQuantidade(int id, float *precoUnit)
{
    FILE *f = fopen("Produtos.dat", "rb");
    int tamProd = quantidadeProdutosDAT();
    PRODUTO comp;
    for (int i = 0; i < tamProd; i++)
    {
        fseek(f, sizeof(PRODUTO) * i, SEEK_SET);
        fread(&comp, sizeof(PRODUTO), 1, f);
        if (comp.id == id)
        {
            *precoUnit = comp.preco;
            return comp.estoque;
        }
    }
    return -1;
}

/**
 * Retorna o id a ser utilizado para a próxima venda
 * @return Retorna próximo ID, quando há erro, retoena -1
 */
unsigned int ProximoIdVenda()
{
    char nomeArquivo[] = "idVenda.dat";
    FILE *f = fopen(nomeArquivo, "r+w");
    unsigned id = 1;
    unsigned int v;
    int size;

    if (f != NULL)
    {
        size = fread(&v, sizeof(unsigned int), 1, f);
        if (size > 0)
        {
            v++;
            id = v;
        }
        fseek(f, 0, SEEK_SET);
        fwrite(&v, sizeof(unsigned int), 1, f);
        fflush(f);
        fclose(f);
    }
    else
    {
        f = fopen(nomeArquivo, "wb");
        fwrite(&id, sizeof(unsigned int), 1, f);
        fclose(f);
    }

    return id;
}