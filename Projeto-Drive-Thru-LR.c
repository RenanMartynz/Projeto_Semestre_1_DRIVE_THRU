// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTÓTIPOS
void administracao(void);

// FUNÇÕES
void administracao(void) 
{
	do
	{
	system("cls");
	system("color 70");
	printf("\n==================================================\n\t\tPAINEL DE CONTROLE\n==================================================\n\t\t0 = sair\n\t\t1 = atender cliente\n\t\t2 = administrar fila\n\t\t3 = consultar menu de produtos\n\t\t4 = cadastrar produto\n\t\t5 = remover produto\n==================================================\nEscolha:");
	op = getche();
	} while (op < '0' && op > '5');
	switch (op)
	{
		case 1:	system ("atendimento.c");
			break;
		case 2: system ("fila.c");
			break;
		case 3: system ("consultar-menu.c");
			break;
		case 4:
				system ("cadastrar-produto.c");
			break;
		case 5:
				system ("remover-produto.c");
			break;
		}
}

// CORPO DO PROGRAMA
int main () 
{
	setlocale(LC_ALL,"");
	do
	{
	administracao();
	}	while (op!='0');
	printf("\nPrograma finalizado");
	getch();
	return 0;
}

