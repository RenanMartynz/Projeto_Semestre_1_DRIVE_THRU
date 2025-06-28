// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTOTIPOS
void solicitar_acao(void);
void gerenciar_acao(void);

// FUNCOES
void solicitar_acao(void) 
{
	// Imprime o cabecario do menu no terminal
	do
	{
	system("cls");
	system("color 70");
	printf("\n==================================================");
	printf("\n\t\tPAINEL DE CONTROLE");
	printf("\n==================================================");
	printf("\n\t\t1 = atendimento");
	printf("\n\t\t2 = consultar menu de produtos");
	printf("\n\t\t3 = cadastrar produto");
	printf("\n\t\t4 = remover produto");
	printf("\n\t\t5 = consultar comanda");
	printf("\n\t\t0 = sair");
	printf("\n==================================================");
	printf("\nEscolha:");
	// Recebe a escolha da acao desejada
	op = getche();
	} while (op < '0' || op > '5');
}

void gerenciar_acao(void)
{
	// Leva o usuario para o programa que realizara a acao desejada
	switch(op)
		{
		case '1': system ("atendimento");
			break;
		case '2': system ("consultar-menu");
			break;
		case '3': system ("cadastrar-produto");
			break;
		case '4': system ("remover-produto");
			break;
		case '5': system ("consultar-comanda");
			break;
		}
}

// CORPO DO PROGRAMA
int main () 
{
	do
	{
	solicitar_acao();
	gerenciar_acao();
	}	// Faz o looping enquanto o usuario nao digitar 0, finalizando o programa quando sair.	
	while (op!='0');
	printf("\nPrograma finalizado.");
	getch();
	return 0;
}

