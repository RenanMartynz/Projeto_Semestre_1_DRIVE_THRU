// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTÓTIPOS
void solicitar_acao(void);
void gerenciar_acao(void);

// FUNÇÕES
void solicitar_acao(void) 
{
	do
	{
	system("cls");
	system("color 70");
	printf("\n==================================================");
	printf("\n\t\tPAINEL DE CONTROLE");
	printf("\n==================================================");
	printf("\n\t\t0 = sair");
	printf("\n\t\t1 = atender cliente");
	printf("\n\t\t2 = administrar fila");
	printf("\n\t\t3 = consultar menu de produtos");
	printf("\n\t\t4 = cadastrar produto");
	printf("\n\t\t5 = remover produto");
	printf("\n==================================================");
	printf("\nEscolha:");
	op = getche();
	} while (op < '0' || op > '5');
}

void gerenciar_acao(void)
{
	switch(op)
		{
		case 1:	system ("atendimento.c");
			break;
		case 2: system ("fila.c");
			break;
		case 3: system ("consultar-menu.c");
			break;
		case 4: system ("cadastrar-produto.c");
			break;
		case 5: system ("remover-produto.c");
			break;
		}
}

// CORPO DO PROGRAMA
int main () 
{
	setlocale(LC_ALL,"");
	do
	{
	solicitar_acao();
	gerenciar_acao();
	}	while (op!='0');
	printf("\nPrograma finalizado.");
	getch();
	return 0;
}

