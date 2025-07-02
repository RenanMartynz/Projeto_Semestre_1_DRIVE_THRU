// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// VARIAVEIS GLOBAIS DO PROGRAMA
int inicio_fila, final_fila, i, j;

// PROTOTIPOS
void gerenciar_fila(void);
void entrada_do_usuario(void);

// FUNCOES
void gerenciar_fila(void)
{
	FILE *Indice = fopen ("INDICE-CLIENTE.DAT", "rb");
	Arq = fopen ("FILA.DAT", "rb+");
	Relat = fopen ("PAGAMENTOS.DAT", "rb");
	if (Indice==NULL)
	{
		printf("\nArquivo INDICE-CLIENTE.DAT nao foi acessado com sucesso");
		getch();
		exit(1);
	}
	if (Arq==NULL)
	{
		printf("\nArquivo FILA.DAT nao foi acessado com sucesso");
		getch();
		exit(1);
	}
	if (Relat==NULL)
	{
		printf("\nArquivo PAGAMENTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(1);
	}
	fread(&posicao, sizeof(posicao), 1, Arq);
	if(posicao.Poscod==0)
	{
		fseek(Arq, 0, SEEK_SET);
		posicao.Poscod=posicao.Codpgto;
		if(posicao.Codpgto!=TAMANHOFILA)
		{
			posicao.Codpgto++;
		}
		else
		{
			posicao.Codpgto=1;
		}
		fwrite(&posicao, sizeof(posicao), 1, Arq);
	}
fseek(Arq, inicio_fila*sizeof(posicao), SEEK_SET);
fread(&posicao, sizeof(posicao), 1, Arq);
fseek(Indice, posicao.Poscod*sizeof(posicao), SEEK_SET);
fread(&posicao, sizeof(posicao), 1, Indice);
fseek(Relat, posicao.Poscod*sizeof(cliente), SEEK_SET);
do
{
fread(&cliente, sizeof(cliente), 1, Relat);
}
while (strcmp(cliente.Formapgto, "0"));
	   if (strcmp(cliente.Formapgto, "dinheiro") == 0) 
	{
    // coloca cor verde se for dinheiro 
        printf("\n\nPEDIDO PAGO COM \x1b[32mDINHEIRO\x1b[0m\n");
  	} else if (strcmp(cliente.Formapgto, "pix") == 0) 
	  {
   	// coloca cor azul se for pix 
		printf("\n\nPEDIDO PAGO COM \x1b[34mPIX\x1b[0m\n");
  	  } else if (strcmp(cliente.Formapgto, "credito") == 0) {
  	       // coloca cor lilas se for credito 
  	      printf("\n\nPEDIDO PAGO COM CARTAO DE \x1b[35mCREDITO\x1b[0m\n");
  	  } else if (strcmp(cliente.Formapgto, "debito") == 0) {
  	      // coloca cor lilas se for debito
  	      printf("\n\nPEDIDO PAGO COM CARTAO DE \x1b[35mDEBITO\x1b[0m\n");
 	   } else {
 	       printf("\n\nPEDIDO PAGO\n");
  	  }
getch();
  	  fclose(Indice);
  	  fclose(Arq);
  	  fclose(Relat);
}
void entrada_do_usuario(void)
{
	Arq = fopen ("FILA.DAT", "rb");
	if (Arq== NULL)
	{
		printf("\nArquivo FILA.DAT nao foi acessado com sucesso");
		getch();
		exit(1);
	}
	fread(&posicao, sizeof(posicao), 1, Arq);
	inicio_fila= posicao.Codpgto;
	final_fila = posicao.Poscod;
	printf("\nPedidos na fila: ");
	if(final_fila!=0)
	{
	for(i=inicio_fila, j=1;j!=5;i++, j++)
	{
		fseek(Arq, i*sizeof(posicao), SEEK_SET);
		fread(&posicao, sizeof(posicao), 1, Arq);
		printf("[%i] ", posicao.Codpgto);
		if (i+1>TAMANHOFILA)
		{
			i = 0;
		}
	}
	}
	else
	{
		for(i=inicio_fila;i!=final_fila;i++)
	{
		fseek(Arq, i*sizeof(posicao), SEEK_SET);
		fread(&posicao, sizeof(posicao), 1, Arq);
		printf("[%i] ", posicao.Codpgto);
		if (i+1>TAMANHOFILA)
		{
			i = 0;
		}
	}
	}
	fclose(Arq);
	printf("\nDeseja atender o primeiro cliente [0=Nao]?");
fflush(stdin);
	scanf("%c", op);
	getch();
}

// CORPO DO PROGRAMA
int main ()
{
	do
	{
	entrada_do_usuario();
	if (op!='0')
	{
		gerenciar_fila();
	}
	}
	while (op!='0');
	return 0;
}
