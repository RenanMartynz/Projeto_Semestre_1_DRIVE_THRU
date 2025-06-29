// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// VARIAVEIS GLOBAIS DO PROGRAMA
int cliente_atual, i=1, fila[TAMANHOFILA], inicio_fila=0, final_fila=0;
long  tamanho_arquivo, inicio_pedido, final_pedido; 

// PROTOTIPOS
void atendimento (void);
void ler_ultimo_reg (void);
void adicionar_prod (void);
void remover_prod (void);
void finalizar_ped (void);
void administrar_fila (void);

// FUNCOES
void atendimento (void)
{
	Arq = fopen("PAGAMENTOS.DAT", "rb");
	// Verifica se o arquivo foi aberto corretamente
	if (Arq == NULL)
	{
		printf("Arquivo PAGAMENTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(0);
	}
	ler_ultimo_reg();
	// Verifica 
	if(cliente.Formapgto=="0" && tamanho_arquivo>0)
	{
		do
		{
		i++;
		if(tamanho_arquivo>0)
		{
		inicio_pedido= tamanho_arquivo-i+1;
		final_pedido= inicio_pedido;
		}
		fseek(Arq, (tamanho_arquivo-i)*sizeof(cliente), SEEK_SET);
		fread(&cliente, sizeof(cliente), 1, Arq);
		cliente_atual= cliente.Codpgto;
		}
		while (cliente.Formapgto=="0" && tamanho_arquivo-i>=0);
	}
	else if (cliente.Formapgto!="0")
	{
		cliente_atual= cliente.Codpgto+1;
		inicio_pedido= tamanho_arquivo;
		final_pedido = inicio_pedido;
	}
	else
	{
		cliente_atual= 1;
		inicio_pedido=0;
		final_pedido=0;
	}
	do {
	system("cls");
	system("color FC");
	printf("\n==================================================");
	printf("\n\t\tATENDIMENTO");
	printf("\n==================================================");
	printf("\n\t\tPedido nro = %03d", cliente_atual);
	printf("\nCodigo\tProduto\tCusto unitario R$\tQuantidade pedida\tValor do item pedido R$\n");
	fseek(Arq, inicio_pedido*sizeof(cliente), SEEK_SET);
	cliente.Valorpgto = 0;
	for (i=0;final_pedido-inicio_pedido==i;i++)
	{
		fread(&cliente, sizeof(cliente), 1, Arq);
		printf("\n%i\t%s\t\tR$%.2f\t\t%i\t\t\tR$%.2f\t%s", 
		cliente.Codprod, cliente.Nomeprod, cliente.Custoprod, cliente.Quantprod, cliente.Valortotalprod, cliente.Formapgto);
	}
	printf("\nTotal da compra:\tR$%.2f", cliente.Valorpgto);
	printf("\n==================================================");
	printf("\n\t1 = registrar produto no pedido");
	printf("\n\t2 = remover produto do pedido");
	printf("\n\t3 = finalizar pedido");
	printf("\n\t4 = administrar fila");
	printf("\n\t0 = voltar para menu inicial (apenas se fila a estiver vazia)");
	printf("\n==================================================");
	printf("\nEscolha:");
	fclose(Arq);
	do
	{
		fflush(stdin);
		scanf("%c", &op);
	}
	while (op < '0' || op >'4');
	switch(op) 
		{
			case '1':
				adicionar_prod();
			break;
			case '2':
				remover_prod();
			break;
			case '3':
				finalizar_ped();
			break;
			case '4':
				administrar_fila();
			break;
			default:
				if (final_fila == 0)
				exit(0);
			break;
		}
	}
	while (op != '0' && final_fila == inicio_fila);
}

void ler_ultimo_reg (void)
{
	fseek (Arq, 0,  SEEK_END);
	tamanho_arquivo = ftell(Arq)/sizeof(cliente);
	if(tamanho_arquivo>0)
	{
	fseek(Arq, (tamanho_arquivo-1)*sizeof(cliente), SEEK_SET);
	fread(&cliente, sizeof(cliente), 1, Arq);
	}
}

void adicionar_prod (void)
{
	int codped, quantped;
	char op2;
	system("cls");
	// Abre e/ou cria arquivos
	Arq = fopen("PRODUTOS.DAT", "rb");
	if (Arq == NULL)
	{
		printf("Arquivo PRODUTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(0);
	}
	// Monta cabecario do relatorio
	printf("==================================================");
	printf("\n\t\tMenu de Produtos");
	printf("\n==================================================");
	printf("\n\tCodigo\tNome\t\tCusto");
	printf("\n==================================================");
	while(!feof(Arq))
	{
	fread(&produto, sizeof(produto), 1, Arq);
	if(!feof(Arq) && produto.Codprod!=0)
	printf("\n\t%i\t%s\t\tR$%.2f", produto.Codprod, produto.Nomeprod, produto.Custoprod);
	}
	printf("\n==================================================");
	do
	{
	printf("\nCodigo do produto [0=Voltar]: ");
	fflush(stdin);
	}
	while(scanf("%i", &codped)!=1 && codped > 0);
	if (codped == 0)
	{
		fclose(Arq);
		return;
	}
	fseek (Arq, (codped-1)*sizeof(produto), SEEK_SET);
	fread (&produto, sizeof(produto), 1, Arq);
	do
	{
	printf("\nQuantidade de %s desejada [0=Voltar]: ", produto.Nomeprod);
	fflush(stdin);
	}
	while(scanf("%i", &quantped)!=1 && quantped > 0);
	if (quantped == 0)
	{
		fclose(Arq);
		return;
	}
	printf("\n%i*%s = R$%.2f", quantped, produto.Nomeprod, produto.Custoprod*quantped);
	printf("\nConfirmar [0=Nao]? ");
	fflush(stdin);
	scanf("%c", &op2);
	if (op2 == '0')
	{
		fclose(Arq);
		return;
	}
	fclose(Arq);
	Arq = fopen ("PAGAMENTOS.DAT", "rb+");
	if(final_pedido!=inicio_pedido)
	{
	fseek (Arq, (final_pedido-1)*sizeof(cliente), SEEK_SET);
	fread (&cliente, sizeof(cliente), 1, Arq);
	cliente.Valorpgto=cliente.Valorpgto+produto.Custoprod*quantped;
	}
	else
	{
	fseek (Arq, final_pedido*sizeof(cliente), SEEK_SET);
	cliente.Valorpgto=produto.Custoprod*quantped;
	}
	cliente.Codpgto=cliente_atual;
	cliente.Codprod=codped;
	cliente.Custoprod=produto.Custoprod;
	strcpy(cliente.Formapgto, "0");
	strcpy(cliente.Nomeprod, produto.Nomeprod);
	cliente.Quantprod=quantped;
	cliente.Valortotalprod=quantped*produto.Custoprod;
	fwrite (&cliente, sizeof(cliente), 1, Arq);
	final_pedido++;
	fclose(Arq);
}

void remover_prod (void)
{
	
}

void finalizar_ped (void)
{
	
}

void administrar_fila (void)
{
	
}

// CORPO DO PROGRAMA
int main () 
{
	atendimento();
	return 0;
}
