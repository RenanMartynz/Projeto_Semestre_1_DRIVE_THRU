/* BIBLIOTECAS */
#include "Drive-Thru-Lib.h"

/* PROTÓPIPOS DE FUNÇÕES */
void consulta_menu (void);

/*CONSTRUÇÃO DAS FUNÇÕES*/
void consulta_menu (void)
{	FILE *Arq;

	CARDAPIO reg;

	char	 opc;

    /* Abre o arquivo para leitura "r" */

	Arq = fopen ("PRODUTOS.DAT", "r");

	if (Arq == NULL)

	{	printf ("\nERRO AO LER PRODUTOS.DAT");

		printf ("\nEndereco lido: %p", Arq);

		getch();

		exit(0);

	}

	/* Enquanto n�o for fim de arquivo (EOF)...*/

	system ("cls");

	printf ("\nCod\tDescricao\tCusto");

	printf ("\n---------------------");

	while ( !feof(Arq) )

	{	/*... leio do arquivo */

		fread ( &reg, sizeof(reg), 1, Arq );

		/* Testa se foi lido EOF */

		if (!feof(Arq))

		{	/* Depois, mostra na tela o conte�do lido */	

			printf ("\n%i\t%s\t R$%.2f", 

			reg.codprod, reg.descrprod, reg.custoprod);

		}

	}

	/* Fecha o arquivo */

	fclose(Arq);

	printf("\nDeseja imprimir o relat�rio? [1=Sim]");

	fflush(stdin); opc=getche();

	if ( opc=='1')

		imprimeRelat();

	getch();

}

/* CORPO DO PROGRAMA */
int main()
{  
  consulta_menu();
  return 0;
}
