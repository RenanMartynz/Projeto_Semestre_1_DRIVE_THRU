// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// VARIAVEIS GLOBAIS DO PROGRAMA
int prod;

// PROTOTIPOS
void entrada_do_usuario(void);
int confirma(void);
void remove_prod(int flag);

// FUNCOES
void entrada_do_usuario(void)
{
	do 
	// Pergunta ao cliente o codigo desejado
	{
	system("cls");
	system("color 4F");
	printf("Digite o codigo do produto a ser removido do cardapio [0=Sair da acao]: ");
	fflush(stdin);
	}
	// Valida escolha para receber inteiro
	while (scanf("%i", &prod)!=1 || prod <0);
}

int confirma()
{
	// Executa apenas se o cliente nao escolheu 0
	if(prod!=0)
	{
		Arq = fopen ("PRODUTOS.DAT", "rb+");
		// Valida se arquivo foi aberto corretamente
		if(Arq == NULL)
		{
			printf("\nArquivo PRODUTOS.DAT nao foi acessado com sucesso");
			getch();
		}
		else
		{
		fseek(Arq, (prod-1)*sizeof(produto), SEEK_SET);
		// Valida se o registro do produto pode ser removido
		if(fread(&produto, sizeof(produto), 1, Arq)!=1 || produto.Codprod==0)
		{
			printf("\nProduto nao encontrado");
			getch();
		}
		else
		// Pede confirmacao
		{
			printf("\nTem certeza que deseja remover %s [0=Nao]? ", produto.Nomeprod);
			fflush(stdin);
			scanf("%c", &op);
			if (op!='0')
			{
				// Realiza a remocao
				return 0;
			}
		}
	}
	}
	// Pula a remocao por falha no processo
	return 1;
}

void remove_prod (int flag)
{
	// Remove apenas se permitido
	if(flag==0)
	{
		fseek(Arq, (prod-1)*sizeof(produto), SEEK_SET);
		printf("\nProduto %s removido com sucesso", produto.Nomeprod);
		produto.Codprod = 0;
		fwrite(&produto.Codprod, sizeof(produto.Codprod), 1, Arq);
		getch();
	}
	fclose (Arq);
}

// CORPO DO PROGRAMA
int main ()
{
	entrada_do_usuario();
	remove_prod(confirma());
	return 0;
}
