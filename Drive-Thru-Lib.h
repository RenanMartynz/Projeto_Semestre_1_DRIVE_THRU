// BIBLIOTECAS
#include <stdio.h>
#include <locale.h>

// CONSTANTES
#define TAMANHONOMEPROD 100

// VARI�VEIS
char op;

// ESTRUTURAS DE DADOS
// Produtos
typedef struct 
{
	int Codprod;
	char Nomeprod[TAMANHONOMEPROD + 1];
	float Custoprod;	
} CARDAPIO;
