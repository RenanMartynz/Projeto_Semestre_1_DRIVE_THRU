// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h> 
#include <conio.h> 
#include <string.h>

// CONSTANTES
#define TAMANHOFILA 4

// VARIAVEIS GLOBAIS
FILE *Arq, *Relat;
char op, op2;

// ESTRUTURAS DE DADOS
// Produtos
typedef struct 
{
	int Codprod;
	char Nomeprod[100+1];
	float Custoprod;	
} CARDAPIO;
CARDAPIO produto;
// Pedido
typedef struct 
{
	int Codpgto, Codprod;
	char Nomeprod[100+1];
	float Custoprod;
	int Quantprod;
	float Valortotalprod, Valorpgto;
	char Formapgto[8+1];	
} PEDIDO;
PEDIDO cliente;
// Posicao do pedido no arquivo
typedef struct
{
	int Codpgto, Poscod;
} ENDERECO;
ENDERECO posicao;
// Cartao
typedef struct {
    char NumeroCartao[16+1];
    int Codpgto;
}DADOSCARTAO;
DADOSCARTAO cartao;
