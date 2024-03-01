#include "vendas.h"
#include "tempo.h"
#include "apresentacao.h"

#include <stdio.h>

/**
 * Começa uma nova compra
 * @param v pnteiro para um registro do tipo VENDA
*/
void IniciarCompra(VENDA *v)
{
    
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
        fflush(v);
        fclose(f);
    }
}