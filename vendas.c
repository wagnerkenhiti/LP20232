#include "vendas.h"
#include "cliente.h"
#include "produtos.h"
#include "tempo.h"
#include "apresentacao.h"

#include <stdio.h>
#include <string.h>
void IniciarCompra(char cpf[])
{
    VENDA v;
    v.identificacaoVenda = ProximoIdVenda();
    strcpy(v.CPF, cpf);
    v.dataCompra = hoje();
    v.valorTotal = 0;
    v.quantidadeProdutos = 0;

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
        if (quantidade <= 0)
            return;
        v.quantidadeProdutos = v.quantidadeProdutos + quantidade;
        v.valorTotal += precoUnitario * quantidade;
        gravarVendaDAT(v);
        gravarVendaCSV(v);
        debitaEstoque(id, quantidade);
    }
}

void exibirVendas(VENDA p)
{
    char data[50];
    separador();
    printf("Exibindo uma venda \n");
    printf("Idenficador da venda: ");
    printf("%d\n", p.identificacaoVenda);
    printf("CPF do cliente que realizou a compra:  ");
    printf("%s\n", p.CPF);
    DataToString(p.dataCompra, data, false);
    printf("Data que o produto foi comprado: %s\n", data);
    printf("Valor total da compra: ");
    printf("%.2f\n", p.valorTotal);
    printf("Quantidade total de produtos: ");
    printf("%d\n", p.quantidadeProdutos);
    separador();
}

void debitaEstoque(int id, int quantidade)
{
    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb+");

    PRODUTO todosProdutos1[200];
    int k1 = lerProdutosDAT(todosProdutos1);
    PRODUTO temp;

    for (int j = 0; j < k1; j++)
    {
        fread(&temp, sizeof(PRODUTO), 1, dat);
        if (temp.id == id)
        {
            fseek(dat, sizeof(PRODUTO) * j, SEEK_SET);
            temp.estoque -= quantidade;
            fwrite(&temp, sizeof(PRODUTO), 1, dat);
            fflush(dat);
        }
    }
}

int lerVendasDAT(VENDA *lista)
{
    int qtde = 0;
    char nomeArquivo[] = "Vendas.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat != NULL)
    {
        while (fread(&lista[qtde], sizeof(VENDA), 1, dat) > 0)
        {
            // exibirProduto(lista[qtde]);
            qtde++;
        }
        return qtde;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        return -1;
    }
    fclose(dat);
}

int lerVendasAttDAT(VENDA *lista)
{
    int qtde = 0;
    char nomeArquivo[] = "VendasAttPontos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat != NULL)
    {
        while (fread(&lista[qtde], sizeof(VENDA), 1, dat) > 0)
        {
            // exibirProduto(lista[qtde]);
            qtde++;
        }
        return qtde;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        return -1;
    }
    fclose(dat);
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
        fprintf(csv, "Id;CPF;Data da compra;Valor total;Quantidade produtos\n");
        fflush(csv);
    }

    // Gravar novos dados
    if (csv != NULL)
    {
        fseek(csv, 0, SEEK_END);
        fprintf(csv, "%d;%s;%d/%d/%d;%.2f;%d\n", v.identificacaoVenda, v.CPF,
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
    FILE *datAttPontos = fopen("VendasAttPontos.dat", "a+b");
    dat = fopen(nomeArquivo, "a+b");

    // Caso o arquivo não exista, sria ele
    if (dat == NULL)
    {
        printf("Criando arquivo %s\n", nomeArquivo);
        dat = fopen(nomeArquivo, "ab");
        datAttPontos = fopen("VendasAttPontos.dat", "ab");
    }

    // Adiciona dados
    if (dat != NULL)
    {

        fwrite(&v, sizeof(VENDA), 1, dat);
        fwrite(&v, sizeof(VENDA), 1, datAttPontos);
        fflush(datAttPontos);
        fflush(dat);
        fclose(datAttPontos);
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