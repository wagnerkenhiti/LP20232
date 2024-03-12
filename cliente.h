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
 * Adiciona pontos a um determinado cliente
 * @param c Ponteiro para o cliente que será adicionado
 * @param pontos Pontos a serem adicionados ao cliente c *
 */
void AdicionarPontosCliente(CLIENTE *c, int pontos);

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
 * Leitura de dados do .dat para registros 
 * @param lista Ponteiro para um vetor de registros 
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de produtos cadastrados
*/
int lerClientesDAT(CLIENTE *lista);

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

#endif