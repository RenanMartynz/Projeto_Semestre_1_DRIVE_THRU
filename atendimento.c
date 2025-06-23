// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTÓTIPOS
void atendimento (void);
void adicionar_prod (void);
void remover_prod (void);
void finalizar_ped (void);
void administrar_fila (void);

// FUNÇÕES
void atendimento (void)
{
	int tamanho_arquivo, cliente_atual, i=2;
	float valortotalped;
	setlocale(LC_ALL, "");
	system("cls");
	system("color FC");
	printf("\n==================================================");
	printf("\n\t\tATENDIMENTO");
	printf("\n==================================================");
	Arq = fopen("PAGAMENTOS.DAT", "rb");
	fseek (Arq, 0,  SEEK_END);
	tamanho_arquivo = ftell(Arq)/sizeof(cliente);
	fseek(Arq, (tamanho_arquivo-1)*sizeof(cliente), SEEK_SET);
	fread(&cliente, sizeof(cliente), 1, Arq);
	if(strcmp(cliente.Formapgto,"0")==0)
	{
		cliente_atual= cliente.Codpgto;
	}
	else
	{
		cliente_atual= cliente.Codpgto+1;
	}
	printf("\n\t\tPedido nro = %03d", cliente_atual);
	printf("\nCódigo\tProduto\tCusto unitário R$\tQuantidade pedida\tValor do item pedido R$\n");
	valortotalped = cliente.Valorpgto;
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
	printf("\n\t0 = voltar para menu inicial");
	printf("\n==================================================");
	printf("\nEscolha:");
	do
	{
		scanf("%c", opc);
	}
	while (opc < '0' || opc >'4');
	switch(opc) 
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
				exit(0);
			break;
		}
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
