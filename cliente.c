#include "cliente.h"
#include "apresentacao.h"
#include "tempo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * Adiciona pontos a um determinado cliente
 * @param c Ponteiro para o cliente que será adicionado
 * @param pontos Pontos a serem adicionados ao cliente c * 
*/
void AdicionarPontosCliente( CLIENTE *c, int pontos )
{
    c->pontos += pontos;
}

/**
 * Função que adiciona um novo cliente através do teclado
 * @param c Ponteiro para um registro do tipo CLIENTE
*/
void adicionarCliente(CLIENTE *c)
{
    separador();
    printf("Adicionar cliente\n");
    printf("CPF: ");
    scanf(" %[^\n]s", c->CPF);
    printf("Nome: ");
    scanf(" %[^\n]", c->nome);
    printf("Dia da data de nascimento: ");
    scanf(" %d", &c->dataNascimento.dia);
    printf("Mês da data de nascimento: ");
    scanf(" %d", &c->dataNascimento.mes);
    printf("Ano da data de nascimento: ");
    scanf(" %d", &c->dataNascimento.ano);
    printf("Idade: ");
    scanf(" %d", &c->idade);
    printf("Endereço: ");
    scanf(" %[^\n]", c->endereco);
    printf("Cidade: ");
    scanf(" %[^\n]", c->cidade);
    printf("Estado: ");
    scanf(" %[^\n]", c->estado);
    c->pontos = 0;
}

/**
 * Grava dados de um cliente, caso o arquivo não exista, cria ele
 * @param c Cliente salvo no registro
*/
int gravarClienteCSV(CLIENTE c)
{
    char nomeArquivo[] = "Cliente.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r+w");

    //Criar arquivo caso não exista
    if (csv == NULL)
    {
        printf("Criando arquivo %s\n", nomeArquivo);
        csv = fopen(nomeArquivo, "a");
        fprintf(csv, "CPF;nome;data de nascimento;idade;endereço;cidade;estado\n");
        fflush(csv);
    }

    //Gravar novos dados
    if (csv != NULL)
    {
        fseek(csv, 0, SEEK_END);
        fprintf(csv, "%s;%s;%d/%d/%d;%d;%s;%s;%s\n",
            c.CPF, c.nome, c.dataNascimento.dia, c.dataNascimento.mes,
            c.dataNascimento.ano, c.idade, c.endereco, c.cidade, c.estado);
        fflush(csv);
        fclose(csv);
    }

    return 0;
}

/**
 * Grava dados de um cliente em binário, caso o arquivo
 * não exista, cria ele
 * @param c Cliente salvo no registro 
*/
int gravarClienteDAT(CLIENTE c)
{
    char nomeArquivo[] = "Cliente.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "a+b");

    //Caso o arquivo não exita, cria ele
    if (dat == NULL)
    {
        printf("Criando arquivo %s\n", nomeArquivo);
        dat = fopen(nomeArquivo, "ab");
    }

    //Adicionar dados
    fwrite(&c, sizeof(CLIENTE), 1, dat);
    fflush(dat);
    fclose(dat);

    return 0;
}