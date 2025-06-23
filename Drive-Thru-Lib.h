// BIBLIOTECAS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <conio.h> 
#include <string.h>

// VARI�VEIS GLOBAIS
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
