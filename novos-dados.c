// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTOTIPOS
void verificar_arquivo(void);

// FUNCOES
void processar_arquivo(void)
{
	if (Arq==NULL)
	{
		printf("\nNao foi possivel criar arquivo");
		getch();
		exit(1);
	}
	fclose(Arq);
}

// CORPO DO PROGRAMA
int main ()
{
	Arq = fopen ("PAGAMENTOS.DAT", "wb");
	processar_arquivo();
	Arq = fopen ("CARTOES.DAT", "wb");
	processar_arquivo();
	Arq = fopen ("INDICE-CLIENTE.DAT", "wb");
	processar_arquivo();
	Arq = fopen ("FILA.DAT", "wb");
	posicao.Codpgto=1;
	posicao.Poscod=1;
	fwrite(&posicao, sizeof(posicao), 1, Arq);
	processar_arquivo();
	Arq = fopen ("PRODUTOS.DAT", "wb");
	processar_arquivo();
	printf("\nArquivos de dados reiniciados/criados.");
	getch();
	return 0;
}
