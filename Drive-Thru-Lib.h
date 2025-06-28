// BIBLIOTECAS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h> 
#include <conio.h> 
#include <string.h>
#include <ctype.h>
// CONSTANTES
#define TAMANHONOMEPROD 100

// VARIÁVEIS
char op;

// ESTRUTURAS DE DADOS
// Produtos
typedef struct 
{
	int Codprod;
	char Nomeprod[TAMANHONOMEPROD + 1];
	float Custoprod;	
} CARDAPIO;
