#ifndef __VENDAS_H__
#define __VENDAS_H__

#include "tempo.h"

typedef struct VENDA
{
    int identificacaoVenda;
    char CPF[14];
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
    char CPF[14];
    item *listaCompra;
}IntensCompra;

/**
 * Começa uma nova compra
 * @param v pnteiro para um registro do tipo VENDA
*/
void IniciarCompra(VENDA *v);

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