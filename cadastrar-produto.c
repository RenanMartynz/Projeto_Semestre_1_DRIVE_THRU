/*BIBLIOTECAS*/
#include "Drive-Thru-Lib.h"

/* PROTOPIPOS DE FUNCOES */
void cadastrar_produto(void);
void gravaArq (void);

/* CONSTRUCAO DAS FUNCOES */
void cadastrar_produto(void){	
	int count = 0;
	do
	{	
		
		/* Captura os dados que serão gravados */
		system ("cls");
		printf ("\nDescricao do produto: "); 
		fflush(stdin); gets(produto.Nomeprod);
		printf ("\nCusto do produto    : "); 
		fflush(stdin); scanf ("%f", &produto.Custoprod);
		/* Grava os dados no arquivo */
		gravaArq();
		/* Deseja cadastrar outro produto? */
		count++;
		if (count >= 100) 
		{ 
			printf("\nLimite de 100 produtos atingido.\n"); 
		        break;
	        }


		printf ("\nDeseja cadastrar outro produto? [0=NAO]:");
		op = getche();
		
	}while ( op!='0');
}

void gravaArq (void)
{
	CARDAPIO c;
	int codigo_atual=0;
	/* Abre o arquivo */
	Arq = fopen ("PRODUTOS.DAT", "rb+");
        /*VERIFICA SE O ARQUIVO EXISTE*/
	if (Arq == NULL)
	{	printf ("\nERRO AO ABRIR O PRODUTOS.DAT");
		printf ("\nEndereco lido: %p", Arq);
		getch();
		exit(0);
	}
        /*MOSTRA O ENDEREÇO DE MEMORIA DO ARQUIVO*/
	printf ("\nEndereco de PRODUTOS.DAT: %p", Arq);
	/* Grava no arquivo */
	do{ 
		fread ( &c, sizeof(c), 1, Arq );
			if(c.Codprod == 0){
				fseek(Arq, codigo_atual*sizeof(produto),SEEK_SET);
				produto.Codprod = codigo_atual + 1;
				fwrite ( &produto, sizeof(produto), 1, Arq );
				fclose(Arq);
				exit(0);
			}
			codigo_atual ++;
	  }while(!feof(Arq));
	produto.Codprod = codigo_atual;
		fwrite ( &produto, sizeof(produto), 1, Arq );
	/* Fecha o arquivo */
	fclose(Arq);
}

/*CORPO DO PROGRAMA*/
int main(){
cadastrar_produto();
return 0;
}
