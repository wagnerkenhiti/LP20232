#include "cliente.h"
/**
 * Adiciona pontos a um determinado cliente
 * @param c Ponteiro para o cliente que será adicionado
 * @param pontos Pontos a serem adicionados ao cliente c * 
*/
void AdicionarPontosCliente( CLIENTE *c, int pontos )
{
    c->pontos += pontos;
}