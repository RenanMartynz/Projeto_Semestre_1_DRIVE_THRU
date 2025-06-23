// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROT�TIPOS
void inicializa_relatorio(void);
void processa_dados(void);

// FUN��ES
void inicializa_relatorio(void)
{
	system("cls");
	// Abre e/ou cria arquivos
	Arq = fopen("PRODUTOS.DAT", "rb");
	Relat = fopen("MENUPRODUTOS.TXT", "w");
	// Monta cabe��rio do relat�rio
	fprintf(Relat, "\n==================================================");
	fprintf(Relat, "\n\t\tMenu de Produtos");
	fprintf(Relat, "\n==================================================");
	fprintf(Relat, "\n\tC�digo\tNome\tCusto");
	fprintf(Relat, "\n==================================================");
}

void processa_dados(void) 
{
	// Valida��o do arquivo
	if(Arq != NULL)
	{
	// Looping registrando todos os produtos no relat�rio
	while(!feof(Arq))
	{
	fread(&produto, sizeof(produto), 1, Arq);
	if(!feof(Arq))
	fprintf(Relat, "\n\t%i\t%s\tR$%.2f", produto.Codprod, produto.Nomeprod, produto.Custoprod);
	}
	}
	// Termina a tabela ap�s processado o �ltimo produto
	fprintf(Relat, "\n==================================================");
	// Fecha arquivos
	fclose(Arq);
	fclose(Relat);
}

// CORPO DO PROGRAMA 
int main()
{
	setlocale(LC_ALL, "");
	inicializa_relatorio();
	processa_dados();
	// Exibe relat�rio
	system("notepad MENUPRODUTOS.TXT");
	return 0;
}