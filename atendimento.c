// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// CONSTANTES
#define TAMANHONENTRADA 9

// VARIAVEIS GLOBAIS DO PROGRAMA
int cliente_atual, i=1, fila[TAMANHOFILA], codped;
long  tamanho_arquivo, inicio_pedido, final_pedido; 
char op2;

// PROTOTIPOS
void mascarar_cartao(char *);
void finalizar_ped (void);
void remover_prod (void);
void adicionar_prod (void);
void atendimento (void);
void ler_ultimo_reg (void);
void configurar_pedido(void);
void verificar_fila(int *);

// FUNCOES
// Substitui os digitos de posicao 5 a 12 por asteriscos (*)
void mascarar_cartao(char *numero) { 
	//rebece o ponteiro para o caractere da string, permitindo modificar diretamente o conteudo do numero do cartao original    
	for (i = 4; i < 12; i++) {
        numero[i] = '*';
    }
}

void finalizar_ped (void)
{
    char numero_cartao[30];     // Variavel temporaria para ler o numero do cartao
    int numero_valido = 0;      // Flag para validar o numero do cartao
    int opcao_pgto = 0;			// para pegar a opcao de pagamento do usuario
    numero_valido = 1;			// para verificar se o cartao so contem digitos numericos
    int i;
   printf("\nTem certeza que deseja finalizar o pedido [0=Nao]? ");
   scanf("%i", &op2);
   if(op2=='0')
   {
     return;
   }
    // Abre o arquivo de pagamentos para leitura e escrita binaria
    Arq = fopen("PAGAMENTOS.DAT", "rb+");
    if (Arq == NULL) {
        printf("Erro ao abrir PAGAMENTOS.DAT\n");
        getch();
        exit(0); // Sai do programa em caso de erro
    }

    // Menu de opcoes para o usuario escolher a forma de pagamento
    printf("\nSelecione a forma de pagamento:\n");
    printf(" 1 - dinheiro\n 2 - pix\n 3 - credito\n 4 - debito\n");

    
    do {
        printf("Opcao (1-4): ");
        scanf("%d", &opcao_pgto);
        fflush(stdin); // Limpa o buffer do teclado
    } while (opcao_pgto < 1 || opcao_pgto > 4); // Garante que a entrada esta entre 1 e 4

    // Atribui a string da forma de pagamento conforme a opcao escolhida
    switch (opcao_pgto) {
        case 1:
            strcpy(cliente.Formapgto, "dinheiro");
            break;
        case 2:
            strcpy(cliente.Formapgto, "pix");
            break;
        case 3:
            strcpy(cliente.Formapgto, "credito");
            break;
        case 4:
            strcpy(cliente.Formapgto, "debito");
            break;
    }

    // Se for cartao (credito ou debito), realiza a validacao e registro
     if (opcao_pgto == 3 || opcao_pgto == 4) {
        do {
            numero_valido = 1;
            printf("Digite o numero do cartao (16 digitos): ");
            fgets(numero_cartao, sizeof(numero_cartao), stdin);
            numero_cartao[strcspn(numero_cartao, "\n")] = '\0';

            if (strlen(numero_cartao) != 16) {
                printf("Cartao invalido. Deve conter exatamente 16 digitos.\n");
                numero_valido = 0;
                continue;
            }

            for (i = 0; i < 16; i++) {
                if (!isdigit(numero_cartao[i])) {
                    printf("Cartao invalido. Digite apenas numeros.\n");
                    numero_valido = 0;
                    break;
                }
            }
        } while (!numero_valido);

        // Aplica a mascara nos digitos do meio
        mascarar_cartao(numero_cartao);

        // Abre o arquivo CARTOES.DAT para acrescentar dados
        FILE *cartoes = fopen("CARTOES.DAT", "ab");
        if (cartoes == NULL) {
            printf("Erro ao abrir CARTOES.DAT\n");
            fclose(Arq);
            exit(1);
        }

        // Preenche a estrutura do cartao com os dados
        strcpy(cartao.NumeroCartao, numero_cartao); //joga as informacoes da variavel temporaria para a original
        cartao.Codpgto = cliente.Codpgto; // Garante que o pedido associado e valido

        // Grava o cartao mascarado no arquivo
        fwrite(&cartao, sizeof(DADOSCARTAO), 1, cartoes);
        fclose(cartoes);
        printf("Cartao registrado com sucesso.\n");
    }
    // Posiciona no ultimo registro do pedido
    fseek(Arq, (final_pedido - 1) * sizeof(PEDIDO), SEEK_SET);
    fread(&cliente, sizeof(PEDIDO), 1, Arq); // Le esse registro para editar
    // Atualiza o campo Formapgto no ultimo registro do pedido
    fseek(Arq, (final_pedido - 1) * sizeof(PEDIDO), SEEK_SET);
    fwrite(&cliente, sizeof(PEDIDO), 1, Arq);
    fclose(Arq); // Fecha o arquivo PAGAMENTOS.DAT

    printf("Pagamento do pedido %03d registrado com sucesso!\n", cliente.Codpgto);
    getch(); // Espera tecla para continuar

    if (strcmp(cliente.Formapgto, "dinheiro") == 0) {
         // coloca cor verde se for dinheiro 
        printf("\n\nPEDIDO PAGO COM \x1b[32mDINHEIRO\x1b[0m\n");
    } else if (strcmp(cliente.Formapgto, "pix") == 0) {
         // coloca cor azul se for pix 
        printf("\n\nPEDIDO PAGO COM \x1b[34mPIX\x1b[0m\n");
    } else if (strcmp(cliente.Formapgto, "credito") == 0) {
         // coloca cor lilas se for credito 
        printf("\n\nPEDIDO PAGO COM CARTAO DE \x1b[35mCREDITO\x1b[0m\n");
    } else if (strcmp(cliente.Formapgto, "debito") == 0) {
        // coloca cor lilas se for debito
        printf("\n\nPEDIDO PAGO COM CARTAO DE \x1b[35mDEBITO\x1b[0m\n");
    } else {
        printf("\n\nPEDIDO PAGO\n");
    }
    getch();
}

void remover_prod (void)
{
	float valorped;
	Arq = fopen("PAGAMENTOS.DAT", "rb+");
	if (Arq == NULL)
	{
		printf("Arquivo PAGAMENTOS.DAT nao foi acessado com sucesso");
		getch();
		exit(0);
	} printf("\n==================================================");
	printf("\n\t\tREMOCAO DE PRODUTO");	printf("\n==================================================");
	printf("\n\t\tPedido nro = %03d", cliente_atual);
	printf("\nCodigo pedido\tCodigo\tProduto\tCusto unitario R$\tQuantidade pedida\tValor do item pedido R$\n");
	fseek(Arq, inicio_pedido*sizeof(cliente), SEEK_SET);
	for (i=0;final_pedido-inicio_pedido!=i;i++)
	{
		fread(&cliente, sizeof(cliente), 1, Arq);
		if(cliente.Codprod!=0)
		{
		printf("\n%i\t%i\t%s\t\tR$%.2f\t\t%i\t\t\tR$%.2f", i+1,
		cliente.Codprod, cliente.Nomeprod, cliente.Custoprod, cliente.Quantprod, cliente.Valortotalprod);
		}
	}
	printf("\nTotal da compra:\tR$%.2f", cliente.Valorpgto);
	printf("\n==================================================");
	do
	{
		do	
		{
			printf("\nCodigo do pedido [0=Voltar]: ");
			fflush(stdin);
		}
		while(scanf("%i", &codped)!=1 && codped >= 0 && codped <= i);
		if (codped == 0)
		{
			fclose(Arq);
			return;
		}
		fseek(Arq, (inicio_pedido+codped-1)*sizeof(cliente), SEEK_SET);
		fread(&cliente, sizeof(cliente), 1, Arq);
	}
	while (cliente.Codprod==0);
	valorped=cliente.Valortotalprod;
	fflush(stdin);
	printf("\nTem certeza que deseja remover %i*%s [0=Voltar]", cliente.Quantprod, cliente.Nomeprod);
	scanf("%c", &op2);
	if (op2 == '0')
	{
		fclose(Arq);
		return;
	}
	fseek(Arq, (inicio_pedido+codped-1)*sizeof(cliente), SEEK_SET);
	cliente.Codprod=0;
	fwrite(&cliente, sizeof(cliente), 1, Arq);
	fseek(Arq, (final_pedido-1)*sizeof(cliente), SEEK_SET);
	fread(&cliente, sizeof(cliente), 1, Arq);
	fseek(Arq, (final_pedido-1)*sizeof(cliente), SEEK_SET);
	cliente.Valorpgto=cliente.Valorpgto-valorped;
	fwrite(&cliente, sizeof(cliente), 1, Arq);
	fclose(Arq);
}

void adicionar_prod (void)
{
	// Processo de acrescimo de produto no pedido
	int quantped;
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
	while(scanf("%i", &codped)!=1 && codped >= 0);
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
	while(scanf("%i", &quantped)!=1 && quantped >= 0);
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
	// Monta cabecario do atendimento
	system("cls");
	system("color FC");
	printf("\n==================================================");
	printf("\n\t\tATENDIMENTO");
	printf("\n==================================================");
	printf("\n\t\tPedido nro = %03d", cliente_atual);
	printf("\nCodigo\tProduto\tCusto unitario R$\tQuantidade pedida\tValor do item pedido R$\n");
	// Configura inicio da leitura para 
	fseek(Arq, inicio_pedido*sizeof(cliente), SEEK_SET);
	cliente.Valorpgto = 0;
	for (i=0;final_pedido-inicio_pedido!=i;i++)
	{
		fread(&cliente, sizeof(cliente), 1, Arq);
		if (cliente.Codprod!=0)
		{
		printf("\n%i\t%s\t\tR$%.2f\t\t%i\t\t\tR$%.2f", 
		cliente.Codprod, cliente.Nomeprod, cliente.Custoprod, cliente.Quantprod, cliente.Valortotalprod);
		}
	}
	printf("\nTotal da compra:\tR$%.2f", cliente.Valorpgto);
	printf("\n==================================================");
	printf("\n\t1 = registrar produto no pedido");
	printf("\n\t2 = remover produto do pedido");
	printf("\n\t3 = finalizar pedido");
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
	while (op < '0' || op >'3');
	switch(op) 
		{
			case '1':
				adicionar_prod();
			break;
			case '2':
   if (inicio_pedido!=final_pedido)
    {
				remover_prod();
    }
   else
    {
    printf("\nNenhum produto para remover");
    getch();
    }
			break;
			case '3':
   if (inicio_pedido!=final_pedido)
    {
				finalizar_ped();
    }
   else
    {
				printf("\nNenhum produto no pedido");
    getch();
    }
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
		// Procura sequencialmente regressivamente ate achar o final do ultimo pedido concluido
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

void verificar_fila(int *vaga_disponivel)
{
	int inicio_fila, final_fila;
	Arq = fopen ("FILA.DAT", "rb");
	if (Arq==NULL)
	{
		printf("Arquivo FILA.DAT nao foi acessado com sucesso");
		getch();
		exit(0);
	}
	// Le a primeira linha do arquivo no qual apresentara o inicio e o final da fila respectivamente
	fread(&posicao, sizeof(posicao), 1, Arq);
	inicio_fila = posicao.Codpgto;
	final_fila = posicao.Poscod;
	// Confere se a fila esta cheia
	// Caso 1: o inicio da fila comecou em um numero diferente de 1 e o final da fila volta a posicao antecessora ao do inicio
	// Caso 2: o inicio da fila comeca na primeira posicao e o final da fila esta na ultima posicao
	if (inicio_fila==final_fila-1||(inicio_fila==1&&final_fila==TAMANHOFILA))
	{
		// Cancela atendimento
		vaga_disponivel=0;
	}
	fclose(Arq);
}

// CORPO DO PROGRAMA
int main () 
{
	int vaga_disponivel=1;
	do 
	{
	// Realiza atendimento se houver vaga na fila
		verificar_fila(&vaga_disponivel);
		if (vaga_disponivel==1)
		{
	// Configura qual o pedido atual a ser registrado
		configurar_pedido();
	// Loop registrando todos os novos produtos no mesmo pedido
		do	
		{
			atendimento();
		}
		while (op != '0' && op!='3');
		}
	}
	while (op=='3');
	return 0;
}
