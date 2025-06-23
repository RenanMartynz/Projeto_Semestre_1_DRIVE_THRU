// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTÓTIPOS
void inicializa_relatorio(void);
void processa_dados(void);

// FUNÇÔES
void inicializa_relatorio(void)
{
	system("cls");
	// Abre e/ou cria arquivos
	Arq = fopen("PRODUTOS.DAT", "rb");
	Relat = fopen("MENUPRODUTOS.TXT", "w");
	// Monta cabeçário do relatório
	fprintf(Relat, "\n==================================================");
	fprintf(Relat, "\n\t\tMenu de Produtos");
	fprintf(Relat, "\n==================================================");
	fprintf(Relat, "\n\tCódigo\tNome\tCusto");
	fprintf(Relat, "\n==================================================");
}

void processa_dados(void) 
{
	// Validação do arquivo
	if(Arq != NULL)
	{
	// Loopíng registrando todos os produtos no relatório
	while(!feof(Arq))
	{
	fread(&produto, sizeof(produto), 1, Arq);
	if(!feof(Arq))
	fprintf(Relat, "\n\t%i\t%s\tR$%.2f", produto.Codprod, produto.Nomeprod, produto.Custoprod);
	}
	}
	// Termina a tabela após processado o último produto
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
	// Exibe relatório
	system("notepad MENUPRODUTOS.TXT");
	return 0;
}
