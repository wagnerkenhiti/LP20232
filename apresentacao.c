#include <stdio.h>
#include <stdlib.h>
#include "apresentacao.h"

const int TAM_SEPARADOR = 40;

void separador()
{
    for (int i = 0 ; i< TAM_SEPARADOR; i++ )
        printf("#");
    printf("\n");
}


int MenuPrincipal()
{
    int opcao;
    system("clear"); // <- opcao caso Linux 
    //system("cls"); // <- opcao caso Windows
    separador();
    printf("1. Venda\n2. Clientes\n3. Produtos\n9. Sair\n");
    separador();
    separador();
    printf("\nOpção -> ");
    
    scanf(" %d", &opcao );
    return opcao;
}

int MenuVenda()
{
    int opcao;
    system("clear"); // <- opcao caso Linux 
    //system("cls"); // <- opcao caso Windows
    separador();
    printf("1. Nova Venda\n2. Listar Venda de Clientes\n9. Sair");
    separador();
    separador();
    printf("\nOpção -> ");
    scanf(" %d", &opcao);
    return opcao;
}

int MenuClientes()
{
    int opcao;
    system("clear"); // <- opcao caso Linux 
    //system("cls"); // <- opcao caso Windows
    separador();
    printf("1. Cadastrar novo cliente\n2. Atualizar pontuação\n3. Atualizar clientes\n");
    printf("4. Listar Clientes entre 18 e 25\n5. Listar Clientes acima de 1000 pontos\n9. Sair");
    separador();
    separador();
    printf("\nOpção -> ");
    scanf(" %d", &opcao);
    return opcao;
}

int MenuProdutos()
{
    int opcao;
    system("clear"); // <- opcao caso Linux 
    //system("cls"); // <- opcao caso Windows
    separador();
    separador();
    printf("1. Cadastrar novo produto\n2. Atualizar informações do produto\n3. Estoque de setor\n4. Produtos com estoque baixo\n9. Sair");
    separador();
    separador();
    printf("\nOpção -> ");
    scanf(" %d", &opcao);
    return opcao;
}