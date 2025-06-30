// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h> 
#include <conio.h> 
#include <string.h>

// CONSTANTES
#define TAMANHOFILA 4
// VARIAVEIS GLOBAIS
FILE *Arq, *Relat;
char op;

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
typedef struct {
    char NumeroCartao[16+1];
    int Codpgto;
}DADOSCARTAO;
DADOSCARTAO cartao;
