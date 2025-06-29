// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// VARIAVEIS GLOBAIS DO PROGRAMA
int cliente_atual, i=1, fila[TAMANHOFILA], inicio_fila=0, final_fila=0;
long  tamanho_arquivo, inicio_pedido, final_pedido; 

// PROTOTIPOS
void administrar_fila (void);
void finalizar_ped (void);
void remover_prod (void);
void adicionar_prod (void);
void atendimento (void);
void ler_ultimo_reg (void);
void configurar_pedido(void);

// FUNCOES
void administrar_fila (void)
{
	Arq = fopen("PAGAMENTOS.DAT", "rb");
	while(!feof(Arq))
	{
	fread(&cliente, sizeof(cliente), 1, Arq);
	if(!feof(Arq))
	{
	printf("\n%i\t%s\t\tR$%.2f\t\t%i\t\t\tR$%.2f\t%s\t%i", 
	cliente.Codprod, cliente.Nomeprod, cliente.Custoprod, cliente.Quantprod, cliente.Valortotalprod, cliente.Formapgto, cliente.Codpgto);
	printf("\nTotal da compra:\tR$%.2f", cliente.Valorpgto);
	}
	}
	if(strcmp(cliente.Formapgto,"0")==0)printf("\nnao pago");
	else printf("\nfoi pago");
	getch();
	

}

void finalizar_ped (void)
{
	
}

void remover_prod (void)
{
	
}

void adicionar_prod (void)
{
	// Processo de acrescimo de produto no pedido
	int codped, quantped;
	char op2;
	system("cls");
	Arq = fopen("PRODUTOS.DAT", "rb");
	if (Arq == NULL)
	{
		printf("Arquivo PRODUTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(0);
	}
	printf("==================================================");
	printf("\n\t\tMenu de Produtos");
	printf("\n==================================================");
	printf("\n\tCodigo\tNome\t\tCusto");
	printf("\n==================================================");
	// Apresenta menu de todos os itens disponiveis do cardapio
	while(!feof(Arq))
	{
	fread(&produto, sizeof(produto), 1, Arq);
	if(!feof(Arq) && produto.Codprod!=0)
	printf("\n\t%i\t%s\t\tR$%.2f", produto.Codprod, produto.Nomeprod, produto.Custoprod);
	}
	printf("\n==================================================");
	// Realiza o atendimento ao cliente
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
	// Identifica se o produto escolhido foi removido e cancela o acao
	if(produto.Codprod==0)
	{
		printf("\nProduto indisponivel");
		getch();
		fclose(Arq);
		return;
	}
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
	if (Arq == NULL)
	{
		printf("Arquivo PAGAMENTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(0);
	}
	// Verifica
	if(final_pedido!=inicio_pedido)
	{
	fseek (Arq, (final_pedido-1)*sizeof(cliente), SEEK_SET);
	fread (&cliente, sizeof(cliente), 1, Arq);
	cliente.Valorpgto=cliente.Valorpgto+produto.Custoprod*quantped;
	}
	else
	{
	cliente.Valorpgto=produto.Custoprod*quantped;
	}
	fseek (Arq, final_pedido*sizeof(cliente), SEEK_SET);
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

void ler_ultimo_reg (void)
{
	fseek (Arq, 0,  SEEK_END);
	tamanho_arquivo = ftell(Arq)/sizeof(cliente);
	// Se arquivo for vazio, tamanho_arquivo sera 0 e nao sera necessario fazer leitura
	if(tamanho_arquivo>0)
	{
	fseek(Arq, (tamanho_arquivo-1)*sizeof(cliente), SEEK_SET);
	fread(&cliente, sizeof(cliente), 1, Arq);
	}
}

void atendimento (void)
{
	Arq = fopen("PAGAMENTOS.DAT", "rb");
	if (Arq == NULL)
	{
		printf("Arquivo PRODUTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(0);
	}
	system("cls");
	system("color FC");
	printf("\n==================================================");
	printf("\n\t\tATENDIMENTO");
	printf("\n==================================================");
	printf("\n\t\tPedido nro = %03d", cliente_atual);
	printf("\nCodigo\tProduto\tCusto unitario R$\tQuantidade pedida\tValor do item pedido R$\n");
	fseek(Arq, inicio_pedido*sizeof(cliente), SEEK_SET);
	cliente.Valorpgto = 0;
	for (i=0;final_pedido-inicio_pedido!=i;i++)
	{
		fread(&cliente, sizeof(cliente), 1, Arq);
		printf("\n%i\t%s\t\tR$%.2f\t\t%i\t\t\tR$%.2f", 
		cliente.Codprod, cliente.Nomeprod, cliente.Custoprod, cliente.Quantprod, cliente.Valortotalprod);
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
	// Gerencia a acao do usuario
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
		}

}

void configurar_pedido(void)
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
	// Configura inicio, final e codigo do pedido
	if(strcmp(cliente.Formapgto,"0")==0 && tamanho_arquivo>0)
	{
		// Se o pedido anterior nao foi concluido e o arquivo ja tem registros
		do
		{
		// Procura sequencialmente ate achar o final do ultimo pedido concluido
			i++;
			inicio_pedido= tamanho_arquivo-i+1;
			final_pedido= inicio_pedido;
			fseek(Arq, (tamanho_arquivo-i)*sizeof(cliente), SEEK_SET);
			fread(&cliente, sizeof(cliente), 1, Arq);
			cliente_atual= cliente.Codpgto;
		// Um pedido concluido tem forma de pagamento diferente de 0
		}
		while (strcmp(cliente.Formapgto,"0")==0 && tamanho_arquivo-i>=0);
		if(tamanho_arquivo-i<1)
		{
			cliente_atual=1;
		}
	}
	// Se o pedido anterior foi concluido
	else if (strcmp(cliente.Formapgto,"0")!=0)
	{
		cliente_atual= cliente.Codpgto+1;
		inicio_pedido= tamanho_arquivo;
		final_pedido = inicio_pedido;
	}
	// Se o arquivo nao tem nenhum registro
	else
	{
		cliente_atual= 1;
		inicio_pedido=0;
		final_pedido=0;
	}
	fclose(Arq);
}

// CORPO DO PROGRAMA
int main () 
{
	configurar_pedido();
	// Loop registrando todos os novos produtos no mesmo pedido
	do	
	{
		atendimento();
	}
	while (op != '0' && final_fila == inicio_fila);
	return 0;
}
