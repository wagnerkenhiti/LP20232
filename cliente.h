#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "tempo.h"

typedef struct CLIENTE
{
    char CPF[14];
    char nome[51];
    DATA dataNascimento;
    int idade;
    char endereco[101];
    char cidade[101];
    char estado[3];
    unsigned int pontos;
} CLIENTE;

/**
 * Função que adiciona um novo cliente através do teclado
 * @param c Ponteiro para um registro do tipo CLIENTE
*/
void adicionarCliente(CLIENTE *c);

/**
 * Grava dados de um cliente em texto, caso o arquivo não exista, cria ele
 * @param c Cliente salvo no registro
*/
int gravarClienteCSV(CLIENTE c);

/**
 * Grava dados de um cliente em binário, caso o arquivo
 * não exista, cria ele
 * @param c Cliente salvo no registro 
*/
int gravarClienteDAT(CLIENTE c);

/**
 * Exibe os campos contidos em um registro do tipo CLIENTE
 * @param c Registro que será exibido
*/
void exibirCliente(CLIENTE c);


/**
 * Edita dados no CSV do cliente a partir de uma busca com o CPF
*/
int editaClienteCSV();

/**
 * Edita dados no DAT do cliente a partir de uma busca com o CPF
*/
int editaClienteDAT();

/**
 * Lista clientes entre 18 a 25 anos
*/
int listaClientes();

/**
 * Procura cliente a partir do CPF
*/
bool procuraCliente();

#endif