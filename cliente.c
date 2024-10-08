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
void AdicionarPontosCliente(CLIENTE *c, int pontos)
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
    getchar();
    printf("Nome: ");
    scanf(" %[^\n]s", c->nome);
    printf("Dia da data de nascimento: ");
    scanf(" %d", &c->dataNascimento.dia);
    printf("Mês da data de nascimento: ");
    scanf(" %d", &c->dataNascimento.mes);
    printf("Ano da data de nascimento: ");
    scanf(" %d", &c->dataNascimento.ano);
    printf("Idade: ");
    scanf(" %d", &c->idade);
    printf("Endereço: ");
    scanf(" %[^\n]s", c->endereco);
    printf("Cidade: ");
    scanf(" %[^\n]s", c->cidade);
    printf("Estado: ");
    scanf(" %[^\n]s", c->estado);
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

    // Criar arquivo caso não exista
    if (csv == NULL)
    {
        printf("Criando arquivo %s\n", nomeArquivo);
        csv = fopen(nomeArquivo, "a");
        fprintf(csv, "CPF;nome;data de nascimento;idade;endereço;cidade;estado;pontuacao\n");
        fflush(csv);
    }

    // Gravar novos dados
    if (csv != NULL)
    {
        fseek(csv, 0, SEEK_END);
        fprintf(csv, "%s;%s;%d/%d/%d;%d;%s;%s;%s;0\n",
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

    // Caso o arquivo não exita, cria ele
    if (dat == NULL)
    {
        printf("Criando arquivo %s\n", nomeArquivo);
        dat = fopen(nomeArquivo, "ab");
    }

    // Adicionar dados
    fwrite(&c, sizeof(CLIENTE), 1, dat);
    fflush(dat);
    fclose(dat);

    return 0;
}

/**
 * Exibe os campos contidos em um registro do tipo PRODUTO
 * @param c Registro que será exibido
 */
void exibirCliente(CLIENTE c)
{
    char data[50];
    separador();
    printf("Exibindo um cliente \n");
    printf("CPF do cliente: ");
    printf(" %s\n", c.CPF);
    printf("Nome do cliente :  ");
    printf(" %s\n", c.nome);
    DataToString(c.dataNascimento, data, false);
    printf("Data do nascimento do cliente: %s\n", data);
    printf("Idade do cliente: ");
    printf(" %d\n", c.idade);
    printf("Enderedo do cliente: ");
    printf(" %s\n", c.endereco);
    printf("Cidade do cliente: ");
    printf(" %s\n", c.cidade);
    printf("Estado do cliente: ");
    printf(" %s\n", c.estado);
    printf("Pontos do cliente: ");
    printf(" %d\n", c.pontos);
    separador();
}

int verificaClienteDAT(char cpf[])
{

    char nomeArquivo[] = "Cliente.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat == NULL)
    {
        printf("Nenhum cliente cadastrado\n");
        return -1;
    }
    bool encontrou = true;
    CLIENTE velho;
    int encontraLinha = 0;
    do
    {
        fread(&velho, sizeof(velho), 1, dat);
        if (strcmp(velho.CPF, cpf) == 0)
            encontrou = false;
        encontraLinha++;
    } while (!feof(dat) && encontrou);
    if (encontrou)
    {
        printf("Cliente nao encontrado.\n");
        return -1;
    }
    return encontraLinha;
}

void editaClienteDAT(int linha, CLIENTE att)
{
    char nomeArquivo[] = "Cliente.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb+");
    fseek(dat, sizeof(CLIENTE) * (linha - 1), SEEK_SET); // sizeof(CLIENTE)*(linha-1)
    fwrite(&att, sizeof(CLIENTE), 1, dat);
    fflush(dat);
    fclose(dat);
    printf("Cliente alterado com sucesso!\n");
}



int lerClientesDAT(CLIENTE *lista)
{
    int qtde = 0;
    char nomeArquivo[] = "Cliente.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat != NULL)
    {
        while (fread(&lista[qtde], sizeof(CLIENTE), 1, dat) > 0)
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
}








void mostrarClientesDAT()
{

    char nomeArquivo[] = "Cliente.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    CLIENTE listar;
    fseek(dat, sizeof(CLIENTE), SEEK_END);
    int i = ftell(dat) / sizeof(CLIENTE);
    fseek(dat, 0, SEEK_SET);
    printf("%d", i);
    for (int j = 1; j < i; j++)
    {
        fread(&listar, sizeof(CLIENTE), 1, dat);
        exibirCliente(listar);
    }
}
