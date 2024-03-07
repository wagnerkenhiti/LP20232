#ifndef __VENDAS_H__
#define __VENDAS_H__

#include "tempo.h"

typedef struct VENDA
{
    int identificacaoVenda;
    char CPF[15];
    DATA dataCompra;
    float valorTotal;
    int quantidadeProdutos;
}VENDA;

typedef struct item
{
    int identificacaoProduto;
    int quantidade;
    float precoUnitario;
    float precoTotal;
}item;

typedef struct ItensCompra
{
    int identificacaoVenda;
    char CPF[15];
    item *listaCompra;
}IntensCompra;

/**
 * Começa uma nova compra
 * @param cpf CPF no qual a compra sera contabilizada
*/
void IniciarCompra(char cpf[]);

/**  
 * FUNCAO AINDA NAO TESTADA
 * @param id ID do produto que tera sua disponibilidade consultada
 * @param precoUnit preco unitario do produto.
 * @return Retorna a quantidade de itens disponiveis ou -1 se nao existir produto com tal ID
*/
int RetornaQuantidade(int id,float *precoUnit);


void exibirVendas(VENDA p);


/**
 * Leitura de dados do .dat para registros 
 * @param lista Ponteiro para um vetor de registros 
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de produtos cadastrados
*/
int lerVendasDAT(VENDA *lista);


void debitaEstoque(int id,int quantidade);


/**
 * Grava dados de uma venda em texto, caso o arquivo não exista, cria ele
 * @param v Venda salvo no registro
*/
int gravarVendaCSV(VENDA v);

/**
 * Grava dados de uma venda em binário, caso o arquivo
 * não exista, cria ele
 * @param v Venda salvo no registro 
*/
int gravarVendaDAT(VENDA v);

/**
 * Retorna o id a ser utilizado para a próxima venda
 * @return Retorna próximo ID, quando há erro, retoena -1
*/
unsigned int ProximoIdVenda();

#endif