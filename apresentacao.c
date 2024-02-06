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
    // system("cls"); // <- opcao caso Windows
    separador();
    printf("1. Venda\n2. Clientes\n3. Produtos\n9. Sair\n");
    separador();
    separador();
    printf("\nOpção -> ");
    
    scanf(" %d", &opcao );
    return opcao;
}
