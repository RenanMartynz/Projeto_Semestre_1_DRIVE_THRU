// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// VARIAVEIS GLOBAIS DO PROGRAMA
int cliente_atual, i=2, fila[TAMANHOFILA], inicio_fila=0, final_fila=0;
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
	float valortotalped;
	Arq = fopen("PAGAMENTOS.DAT", "rb+");
	ler_ultimo_reg();
	if(strcmp(cliente.Formapgto,"0")==0)
	{
		cliente_atual= cliente.Codpgto;
	do
	{
		fseek(Arq, (tamanho_arquivo-i)*sizeof(cliente), SEEK_SET);
		fread(&cliente, sizeof(cliente), 1, Arq);
		i++;
	}
	while (cliente.Codpgto==cliente_atual);
	}
	else
	{
		cliente_atual= cliente.Codpgto+1;
	}
	do {
	ler_ultimo_reg();
	system("cls");
	system("color FC");
	printf("\n==================================================");
	printf("\n\t\tATENDIMENTO");
	printf("\n==================================================");
	printf("\n\t\tPedido nro = %03d", cliente_atual);
	printf("\nCodigo\tProduto\tCusto unitario R$\tQuantidade pedida\tValor do item pedido R$\n");
	valortotalped = cliente.Valorpgto;
	i=2;
	do
	{
		printf("\n%i\t%s\t\tR$%.2f\t\t%i\t\t\tR$%.2f\t%s", cliente.Codprod, cliente.Nomeprod, cliente.Custoprod, cliente.Quantprod, cliente.Valortotalprod, cliente.Formapgto);
		fseek(Arq, (tamanho_arquivo-i)*sizeof(cliente), SEEK_SET);
		fread(&cliente, sizeof(cliente), 1, Arq);
		i++;
	}
	while (cliente.Codpgto==cliente_atual);
	printf("\nTotal da compra:\tR$%.2f", valortotalped);
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
		scanf("%c", op);
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
	while (op != '0' && final_fila == 0);
}

void ler_ultimo_reg (void)
{
	fseek (Arq, 0,  SEEK_END);
	tamanho_arquivo = ftell(Arq)/sizeof(cliente);
	fseek(Arq, (tamanho_arquivo-1)*sizeof(cliente), SEEK_SET);
	fread(&cliente, sizeof(cliente), 1, Arq);
}

void adicionar_prod (void)
{
	
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
