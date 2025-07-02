// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// CORPO DO PROGRAMA
int main ()
{
	int codped, tamanho_arquivo;
	FILE *Arqpos;
	Arq = fopen ("PAGAMENTOS.DAT", "rb");
	if (Arq==NULL)
	{
		printf("\nArquivo PAGAMENTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(1);
	}
	Relat = fopen ("COMANDA.TXT", "w");
	if (Relat==NULL)
	{
		printf("\nArquivo COMANDA.TXT nao foi acessado com sucesso");
		getch();
		exit(1);
	}
	Arqpos = fopen ("INDICE-CLIENTE.DAT", "rb");
	if (Arqpos==NULL)
	{
		printf("\nArquivo INDICE-CLIENTE.DAT nao foi acessado com sucesso");
		getch();
		exit(1);
	}
	fseek(Arq, 0,SEEK_END);
	tamanho_arquivo= ftell(Arq)/sizeof(cliente);
	fseek(Arq, (tamanho_arquivo-1)*sizeof(cliente), SEEK_SET);
	fread(&cliente, sizeof(cliente), 1, Arq);
	do
	{
	system("cls");
	printf("\nDigite o codigo do cliente [0=Voltar]: ");
	fflush(stdin);
	}
	while(scanf("%i", &codped)!=1 || codped < 0 || codped>cliente.Codpgto);
	if (codped==0)
	{
		fclose(Arqpos);
		fclose(Relat);
		fclose(Arq);
		return;
	}
	fseek(Arqpos, (codped-1)*sizeof(posicao), SEEK_SET);
	fread(&posicao, sizeof(posicao), 1, Arqpos);
	fseek(Arq, posicao.Poscod*sizeof(cliente), SEEK_SET);
	fread(&cliente, sizeof(cliente), 1, Arq);
    fprintf(Relat, "\n==================================================");
	fprintf(Relat, "\n\t\tPedido nro = %03d", cliente.Codpgto);
	fprintf(Relat, "\n==================================================");
	fprintf(Relat, "\nCodigo\tProduto\tCusto unitario R$\tQuantidade pedida\tValor do item pedido R$\n");
	fprintf(Relat, "\n%i\t%s\t\tR$%.2f\t\t%i\t\t\tR$%.2f", 
	cliente.Codprod, cliente.Nomeprod, cliente.Custoprod, cliente.Quantprod, cliente.Valortotalprod);
	do
	{
		fread(&cliente, sizeof(cliente), 1, Arq);
		if (cliente.Codprod!=0)
		{
		fprintf(Relat, "\n%i\t%s\t\tR$%.2f\t\t%i\t\t\tR$%.2f", 
		cliente.Codprod, cliente.Nomeprod, cliente.Custoprod, cliente.Quantprod, cliente.Valortotalprod);
		}
	}
	while (strcmp(cliente.Formapgto,"0")==0);
	fprintf(Relat, "\nTotal da compra:\tR$%.2f", cliente.Valorpgto);
	fprintf(Relat, "\nPago em:\t%s", cliente.Formapgto);
	fprintf(Relat, "\n==================================================");
	fclose(Arqpos);
	fclose(Relat);
	fclose(Arq); // Fecha o arquivo PAGAMENTOS.DAT
	system("notepad COMANDA.TXT");
	return 0;
}
