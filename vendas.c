#include "vendas.h"
#include "cliente.h"
#include "produtos.h"
#include "tempo.h"
#include "apresentacao.h"

#include <stdio.h>

/**
 * Começa uma nova compra
 * @param v pnteiro para um registro do tipo VENDA
*/
void IniciarCompra(VENDA *v)
{
    // Iniciando uma nova compra (Não consegui colocar o CPF, em v.CPF)
    v->identificacaoVenda = ProximoIdVenda();
    v->dataCompra = hoje();
    v->valorTotal = 0.0;
    v->quantidadeProdutos = 0;

    // Iniciando ItensCompra (não cosnegui iniciar)

    // Busca cliente pelo CPF (Não consegui colocar o CPF, em v.CPF)
    char CPF[15];
    printf("Iniciando uma nova compra.\n");
    printf("Digitar o CPF do cliente: ");
    scanf(" %[^\n]s", CPF);

    // Verifica se o cliente está cadastrado, caso de verdadeiro, irá cadasta-lo
    if (verificaClienteDAT(CPF) == -1)
    {
        printf("Cliente não cadastrado.\n");
        CLIENTE cliente;
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
    }

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
        //Fazer uma função para ler a quantidade de prodoutos disponivel
        quantidadeDisponivel = 0;
        if (quantidadeDisponivel == 0)
            printf("Produto em falta.\n");
        else
        {
            printf("Quantidade: ");
            scanf(" %d", quantidade);
            while (quantidade > quantidadeDisponivel)
            {
                printf("Quantidade acima do disponivel.\n");
                printf("Para adicionar a compra, digitar um número disponivel de produto,caso, não queira adicionar ao carrinho digitar -1");
                scanf(" %d", &quantidade);
            }
        }

        // Adicionar item a compra
        item *i;
        if (quantidadeDisponivel != 0 || quantidade != -1)
        {
            i->identificacaoProduto = id;
            i->quantidade = quantidade;
            // Adicionar uma função ou fazer uma modo de achar o preco unitario
            i->precoUnitario = 0;
            i->precoTotal = i->precoUnitario * i->quantidade;
            
            // Adiciona ao registro de VENDA
            v->quantidadeProdutos = v->quantidadeProdutos + i->quantidade;
            v->valorTotal = v->valorTotal + i->precoTotal;
        }

        //Baixar do estoque
    } while (opcao != 2);

    // Verifica se o cliente comprou algo, caso positivo, grava dados em Vendas.csv
    if (v->quantidadeProdutos != 0)
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
        fseek(f,0,SEEK_SET);
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