/*BIBLIOTECAS*/
#include "Drive-Thru-Lib.h"

/* PROTÓPIPOS DE FUNÇÕES */
void cadastrar_produto(void);
void gravaArq (CARDAPIO reg);

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

void gravaArq (CARDAPIO reg)
{	FILE *Arq;
	/* Abre o arquivo */
	Arq = fopen ("PRODUTOS.DAT", "a");
        /*VERIFICA SE O ARQUIVO EXISTE*/
	if (Arq == NULL)
	{	printf ("\nERRO AO ABRIR O PRODUTOS.DAT");
		printf ("\nEndereco lido: %p", Arq);
		getch();
		exit(0);
	}
        /*MOSTRA O ENDEREÇO DE MEMÓRIA DO ARQUIVO*/
	printf ("\nEndereco de PRODUTOS.DAT: %p", Arq);
	/* Grava no arquivo */
	fwrite ( &reg, sizeof(reg), 1, Arq );
	/* Fecha o arquivo */
	fclose(Arq);
}

/*CORPO DO PROGRAMA*/
int main(){
cadastrar_produto();
return 0;
}
