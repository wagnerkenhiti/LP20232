#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "tempo.h"

typedef struct CLIENTE
{
    char CPF[15]; 
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
 * Verifica existencia do cliente ou se tem algum cliente cadastrado
 * @param cpf Informa o CPF do cliente que deseja alterar
 * @return linha no qual encontrou o CPF; -1 se o cpf nao foi encontrado ou se nao tiver clientes cadastrados (nao existir o arquivo)
*/
int verificaClienteDAT(char cpf[]);

/**
 * Edita dados no DAT do cliente a partir de uma busca com o CPF
 * @param linha Informa a linha no qual sera sobrescrita
 * @param att Insere os novos dados do cliente
*/
void editaClienteDAT(int linha, CLIENTE att);

/**
 * Mostra os clientes no arquivo DAT
*/
void mostrarClientesDAT();



/**
 * Lista clientes entre 18 a 25 anos
*/
int listaClientes();

#endif