// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTÓTIPOS
void solicitar_acao(void);
void gerenciar_acao(void);

// FUNÇÕES
void solicitar_acao(void) 
{
	// Imprime o cabeçário do menu no terminal
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
	printf("\n\t\t0 = sair");
	printf("\n==================================================");
	printf("\nEscolha:");
	// Recebe a escolha da ação desejada
	op = getche();
	} while (op < '0' || op > '4');
}

void gerenciar_acao(void)
{
	// Leva o usuário para o programa que realizará a ação desejada
	switch(op)
		{
		case '1':	system ("atendimento");
			break;
		case '2': system ("consultar-menu");
			break;
		case '3': system ("cadastrar-produto");
			break;
		case '4': system ("remover-produto");
			break;
		}
}

// CORPO DO PROGRAMA
int main () 
{
	// Configurar formatação para a localidade padrão do sistema operacional
	setlocale(LC_ALL,"");
	do
	{
	solicitar_acao();
	gerenciar_acao();
	}	// Faz o looping enquanto o usuário não digitar 0, finalizando o programa quando sair.	
	while (op!='0');
	printf("\nPrograma finalizado.");
	getch();
	return 0;
}

