/*BIBLIOTECAS*/
#include <stdio.h>
#include <string.h>

/* TIPOS PRÉ-DEFINIDOS PELO PROGRAMADOR */
typedef  struct 
{
	int		codprod;
	char	descrprod[20+1];
	float	custoprod;
}CARDAPIO;

/* PROTÓPIPOS DE FUNÇÕES */
void cadastrar_produto(void);

/* CONSTRUÇÃO DAS FUNÇÕES */
void cadastrar_produto(void){
  CARDAPIO   c;	
	char      op;
	do
	{	/* Captura os dados que serão gravados */
		system ("cls");
		printf ("\nCodigo do produto   : "); 
		fflush(stdin); scanf ("%i", &c.codprod);
		printf ("\nDescricao do produto: "); 
		fflush(stdin); gets(c.descrprod);
		printf ("\nCusto do produto    : "); 
		fflush(stdin); scanf ("%f", &c.custoprod);
		/* Grava os dados no arquivo */
		gravaArq(c);
		/* Deseja cadastrar outro produto? */
		printf ("\nDeseja cadastrar outro produto? [0=NAO]:");
		op = getche();
	}while ( op!='0' );
}

/*CORPO DO PROGRAMA*/
int main(){
solicitar_dados
return 0;
}
