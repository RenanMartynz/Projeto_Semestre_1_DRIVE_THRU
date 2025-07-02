// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTOTIPOS
void inicializa_relatorio(void);
void processa_dados(void);

// FUNCOES
void inicializa_relatorio(void)
{
	system("cls");
	// Abre e/ou cria arquivos
	Arq = fopen("PRODUTOS.DAT", "rb");
	if (Arq == NULL)
	{
		printf("\nArquivo PRODUTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(1);
	}
	Relat = fopen("MENUPRODUTOS.TXT", "w");
	if (Relat == NULL)
	{
		printf("\nArquivo MENUPRODUTOS.TXT nao foi criado com sucesso");
		getch();
		exit(1);
	}
	// Monta cabecario do relatorio
	fprintf(Relat, "==================================================");
	fprintf(Relat, "\n\t\tMenu de Produtos");
	fprintf(Relat, "\n==================================================");
	fprintf(Relat, "\n\tCodigo\tNome\t\tCusto");
	fprintf(Relat, "\n==================================================");
}

void processa_dados(void) 
{
	// Looping registrando todos os produtos no relatorio
	while(!feof(Arq))
	{
	fread(&produto, sizeof(produto), 1, Arq);
	if(!feof(Arq) && produto.Codprod!=0)
	fprintf(Relat, "\n\t%i\t%s\t\tR$%.2f", produto.Codprod, produto.Nomeprod, produto.Custoprod);
	}
	// Termina a tabela apcoes processado o ultimo produto
	fprintf(Relat, "\n==================================================");
	// Fecha arquivos
	fclose(Arq);
	fclose(Relat);
}

// CORPO DO PROGRAMA 
int main()
{
	inicializa_relatorio();
	processa_dados();
	// Exibe relatorio
	system("notepad MENUPRODUTOS.TXT");
	return 0;
}
