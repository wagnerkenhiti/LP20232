#include "produtos.h"
#include "apresentacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char separadorCSV = ';';
// char SETOR[6][] = {"Higiene", "Limpeza", "Bebidas", "Frios", "Padaria", "Açougue"};

/**
 * Rotina que lê os dados de um produto através do teclado
 * @param p Ponteiro para um registro do tipo PRODUTO,
 * onde os dados lidos serão armazenados
 */
void lerProduto(PRODUTO *p)
{
    separador();
    printf("Lendo um produto \n");
    printf("Setor do produto :  ");
    scanf(" %[^\n]s", p->setor);
    printf("Nome do produto: ");
    scanf(" %[^\n]s", p->nome);
    printf("Preço do produto: ");
    scanf(" %f", &p->preco);
    printf("Data de validade do produto\n");
    printf("\tDia ->");
    scanf(" %d", &p->dataValidade.dia);
    printf("\tMês ->");
    scanf(" %d", &p->dataValidade.mes);
    printf("\tAno ->");
    scanf(" %d", &p->dataValidade.ano);
    printf("Estoque do produto: ");
    scanf(" %i", &p->estoque);
}

/**
 * Exibe os campos contidos em um registro do tipo PRODUTO
 * @param p Registro que será exibido
 */
void exibirProduto(PRODUTO p)
{
    char data[50];
    separador();
    printf("Exibindo um produto \n");
    printf("Idenficador do produto: ");
    printf(" %u\n", p.id);
    printf("Setor do produto :  ");
    printf(" %s\n", p.setor);
    printf("Nome do produto: ");
    printf(" %s\n", p.nome);
    printf("Preço do produto: ");
    printf(" %.2f\n", p.preco);
    DataToString(p.dataValidade, data, false);
    printf("Data de validade do produto: %s\n", data);
    printf("Estoque do produto: ");
    printf(" %i\n", p.estoque);
    separador();
}

/**
 * Gravando os dados de um produto no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param p Produto que será salvo no registro
 */
int gravarProdutoCSV(PRODUTO p)
{
    char nomeArquivo[] = "Produtos.csv";
    FILE *csv;
    csv = fopen(nomeArquivo, "r+w");

    if (csv == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivo);
        csv = fopen(nomeArquivo, "a");
        fprintf(csv, "id;setor;nome;preço;data de validade;estoque\n");
        fflush(csv);
    }
    else
        fseek(csv, 0, SEEK_END);
    // arquivo ja existe, insere apenas o dado no final do arquivo
    fprintf(csv, "%d;%s;%s;%.2f;%d/%d/%d;%d\n",
            p.id, p.setor, p.nome, p.preco,
            p.dataValidade.dia, p.dataValidade.mes, p.dataValidade.ano,
            p.estoque);
    fflush(csv);
    fclose(csv);
    // salvando o cabeçalho do arquivo
    return 0;
}

int quantidadeProdutosCSV()
{
    char nomeArquivo[] = "Produtos.csv";
    FILE *csv;
    char linha[1000];
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        int contadorLinha = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            contadorLinha++;
        }
        fclose(csv);
        return contadorLinha;
    }
    else
    {
        // arquivo não existe
        return 0;
    }
}

/**
 * Leitura de dados do CSV para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de produtos cadastrados
 */
int lerProdutosCSV(PRODUTO *lista)
{
    char nomeArquivo[] = "Produtos.csv";
    FILE *csv;
    char linha[1000];
    char *campos;
    const char s[2] = ";";
    int contadorLinha = 0;
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // fim dos registros, reabrindo para ler os dados
        fseek(csv, 0, SEEK_SET);
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        // alocando memoria para os registros lidos

        int i = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            // separando os dados de uma linha
            campos = strtok(linha, s);
            int campoAtual = 0;
            while (campos != NULL)
            {
                printf(" %s\n", campos);
                switch (campoAtual)
                {
                case 0:
                    lista[i].id = atoi(campos);
                    break;
                case 1:
                    strcpy(lista[i].setor, campos);
                    break;
                case 2:
                    strcpy(lista[i].nome, campos);
                    break;
                case 3:
                    lista[i].preco = atof(campos);
                    break;
                case 4:
                    StringToData(campos, &lista[i].dataValidade);
                    break;
                case 5:
                    lista[i].estoque = atoi(campos);
                    break;
                default:
                    break;
                }
                campos = strtok(NULL, s);

                campoAtual++;
            }

            i++;
            // dados do setor;
        }
        contadorLinha = i;
        return contadorLinha;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivo);
        return -1;
    }
}

/**
 * Grava um registro de PRODUTO em um arquivo binário
 * @param p Produto que será salvo no arquivo
 */
int gravarProdutoDAT(PRODUTO p)
{
    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "a+b");
    if (dat == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivo);
        dat = fopen(nomeArquivo, "ab");
    }
    fwrite(&p, sizeof(PRODUTO), 1, dat);
    fflush(dat);
    fclose(dat);
    return 0;
}

int quantidadeProdutosDAT()
{
    int qtde = 0;
    PRODUTO dummy;
    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat != NULL)
    {
        while (fread(&dummy, sizeof(PRODUTO), 1, dat) > 0)
            qtde++;

        return qtde;
    }
    else
    {
        return 0;
    }
}

/**
 * Leitura de dados do arquivo binário para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de produtos cadastrados
 */
int lerProdutosDAT(PRODUTO *lista)
{
    int qtde = 0;
    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat != NULL)
    {
        while (fread(&lista[qtde], sizeof(PRODUTO), 1, dat) > 0)
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







int verificaProdutoDAT(int ID)
{

    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb");
    if (dat == NULL)
    {
        printf("Nenhum produto cadastrado\n");
        return -1;
    }
    bool encontrou = true;
    PRODUTO velho;
    int encontraLinha = 0;
    do
    {
        fread(&velho, sizeof(PRODUTO), 1, dat);
        if (velho.id== ID)
            encontrou = false;
        encontraLinha++;
    } while (!feof(dat) && encontrou);

    
    if (encontrou)
    {
        printf("Produto nao encontrado.\n");
        return -1;
    }
    return encontraLinha;
}

void editaProdutoDAT(int linha, PRODUTO att)
{
    char nomeArquivo[] = "Produtos.dat";
    FILE *dat;
    dat = fopen(nomeArquivo, "rb+");
    fseek(dat,sizeof(PRODUTO)*(linha-1), SEEK_SET);
    fwrite(&att, sizeof(PRODUTO), 1, dat);
    fflush(dat);
    fclose(dat);
    printf("Produto alterado com sucesso!\n");

}



/**
 * Rotina que devolve o id a ser utilizado no próximo cadastro
 * @param formato Define se é para o tipo de arquivo csv ou para o tipo dat
 * @return Retorna o próximo ID a ser utilizado. Se o formato não for definido para 
 * um dos dois válidos ("CSV" ou "DAT"), a função retorna -1.
*/
unsigned int obterProximoIdProduto()
{
    char nomeArquivo[] = "idProduto.dat";
    FILE *f = fopen(nomeArquivo, "r+wb");
    unsigned  id=1;
    unsigned int v;
    int size;
    if (f != NULL)
    {
        size = fread(&v,sizeof(unsigned int),1, f);
        if (size > 0)
        {
            v++;
            id = v;
        }
        fseek(f,0,SEEK_SET);
        fwrite(&v, sizeof(unsigned int), 1, f);    
        fflush(f);
        fclose(f);
    }
    else
    {
        f = fopen(nomeArquivo,"wb");
        fwrite(&id, sizeof(unsigned int), 1, f);
        fclose(f);
    }
    return id;
}

/**
 * @param id Indica qual produto vai ser alterado
 * @param prod Indica qual novo produto substituira o antigo
 * @return Retorna 1 para caso a modificacao foi realizada e 0 quando nao. 
*/
int editaProduto(unsigned int id, PRODUTO prod){







    return 0;
}