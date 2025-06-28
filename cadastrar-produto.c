/*BIBLIOTECAS*/
#include "Drive-Thru-Lib.h"

/* PROTÓPIPOS DE FUNÇÕES */
void cadastrar_produto(void);
void gravaArq (void);

/* CONSTRUÇÃO DAS FUNÇÕES */
void cadastrar_produto(void){	
	do
	{	/* Captura os dados que serão gravados */
		system ("cls");
		printf ("\nCodigo do produto   : "); 
		fflush(stdin); scanf ("%i", &produto.codprod);
		printf ("\nDescricao do produto: "); 
		fflush(stdin); gets(produto.descrprod);
		printf ("\nCusto do produto    : "); 
		fflush(stdin); scanf ("%f", &produto.custoprod);
		/* Grava os dados no arquivo */
		gravaArq(produto);
		/* Deseja cadastrar outro produto? */
		printf ("\nDeseja cadastrar outro produto? [0=NAO]:");
		op = getche();
	}while ( op!='0' );
}

void gravaArq (void)
{
	int codigo_atual=0;
	FILE *Arq;
	/* Abre o arquivo */
	Arq = fopen ("PRODUTOS.DAT", "rb+");
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
	do{ 
		fread ( &produto, sizeof(produto), 1, Arq );
			if(produto.Codprod){
				fwrite ( &produto, sizeof(produto), 1, Arq );
			}
		
		
	  }while(!EOF(Arq));
	if (codigo_atual==0){
		fwrite ( &produto, sizeof(produto), 1, Arq );
	}
	
	/* Fecha o arquivo */
	fclose(Arq);
}

/*CORPO DO PROGRAMA*/
int main(){
cadastrar_produto();
return 0;
}
