// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// CORPO DO PROGRAMA
int main () 
{
	setlocale(LC_ALL,"");
	char op;
	do{
	do
	{
	system("cls");
	system("color 70");
	printf("\n==================================================\n\t\tPAINEL DE CONTROLE\n==================================================\n\t\t0 = sair\n\t\t1 = atender cliente\n\t\t2 = administrar fila\n\t\t3 = consultar menu de produtos\n\t\t4 = cadastrar produto\n\t\t5 = remover produto\n==================================================\nEscolha:");
	op = getche();
	} while (op != '0' && op != '1' && op != '2' && op != '3' && op != '4' && op != '5');
	switch (op)
	{
		case 1:	system ("atendimento.c");
			break;
		case 2: system ("fila.c");
			break;
		case 3: consultar_menu();
			break:
		case 4:
				cadastrar_produto();
			break;
		case 5:
				remover_produto();
			break;
	}
}	while (op!='0');
	printf("\nPrograma finalizado");
	getch();
	return 0;
}

