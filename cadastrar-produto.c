/*BIBLIOTECAS*/
#include "Drive-Thru-Lib.h"

/* Variáveis */
char entrada[50];
float custoProduto;
int possuiErro;


/* PROTOPIPOS DE FUNCOES */
void cadastrar_produto(void);
void gravaArq (void);
int valida_simples(char *s);

/* CONSTRUCAO DAS FUNCOES */

int valida_simples(char *s) {
    int i;
	/*faz a validacao que so aceita caracteres maisculos,minusculos e numeros*/
    for (i = 0; s[i]; i++) {
        if (!(s[i] >= 'a' && s[i] <= 'z') &&
            !(s[i] >= 'A' && s[i] <= 'Z') &&
            !(s[i] >= '0' && s[i] <= '9') &&
             s[i] != ' ') return 0;
    }
    return 1;
}

void cadastrar_produto(void) {
    char op;

    do {
        system("cls");
	system("color 2f");
	    
   /*PEDE A DESCRICAO DO PRODUTO*/
do {
    printf("\nDescricao do produto (sem acento ou simbolo): ");
    fflush(stdin);
    fgets(produto.Nomeprod, sizeof(produto.Nomeprod), stdin);
    produto.Nomeprod[strcspn(produto.Nomeprod, "\n")] = '\0'; // Remove o '\n' adicionado por fgets 
    
    if (!valida_simples(produto.Nomeprod)) //verifica se a entrada e invalida
        printf("Entrada inválida. Tente novamente.\n");// mensagem de erro
} while (!valida_simples(produto.Nomeprod)); //faz o loop enquanto a descricao nao estiver correta
  
	do {
    possuiErro = 0;
    custoProduto = 0;
    int indice = 0;
    int encontrouSeparador = 0;
    int casasDecimais = 0;

    printf("\nCusto do produto : ");
    fgets(entrada, 50, stdin);
		
    // Itera sobre cada caractere da string de entrada ate o final da string ou uma nova linha
    while (entrada[indice] && entrada[indice] != '\n') { // verifica se o caractere nao e \n
        char caractere = entrada[indice];

        if (caractere >= '0' && caractere <= '9') { // Verifica se o caractere e um dígito numerico (de '0' a '9')
            custoProduto = custoProduto * 10 + (caractere - '0'); //serve para transformar um caracter numerico como '5' pelo numero 5, ele pega um acaractere da tabela asc e tranforma no seu numero real
            if (encontrouSeparador) casasDecimais++;
        } else if (caractere == '.' || caractere == ',') { // Verifica se o caractere e um separador decimal valido (ponto ou virgula)
            if (encontrouSeparador) possuiErro = 1;
            encontrouSeparador = 1;
        } else {
            possuiErro = 1;
        }

        indice++; // avanca para o proximo caractere
    }

    if (!possuiErro) { // executa se posuir erro
    // Divide o valor por 10 para cada casa decimal contada
    // Exemplo: 1234 com 2 casas decimais vira 12.34
        while (casasDecimais--) custoProduto /= 10;
        produto.Custoprod = custoProduto; // Atribui o valor final convertido ao campo da struct
    } else {
        printf("Valor inválido. Digite novamente apenas números e um separador decimal.\n");
    }

} while (possuiErro);
        gravaArq();

        printf("\nDeseja cadastrar outro produto? [0=NAO]:");
        fflush(stdin);
        op = getche();

    } while (op != '0');
}






void gravaArq (void)
{
	CARDAPIO c;
	int codigo_atual=0;
	/* Abre o arquivo */
	Arq = fopen ("PRODUTOS.DAT", "rb+");
        /*VERIFICA SE O ARQUIVO EXISTE*/
	if (Arq == NULL)
	{	printf ("\nERRO AO ABRIR O PRODUTOS.DAT");
		printf ("\nEndereco lido: %p", Arq);
		getch();
		exit(0);
	}
        /*MOSTRA O ENDEREÇO DE MEMORIA DO ARQUIVO*/
	printf ("\nEndereco de PRODUTOS.DAT: %p", Arq);
	/* Grava no arquivo */
	do{ 
		fread ( &c, sizeof(c), 1, Arq );
			if(c.Codprod == 0){
				fseek(Arq, codigo_atual*sizeof(produto),SEEK_SET);
				produto.Codprod = codigo_atual + 1;
				fwrite ( &produto, sizeof(produto), 1, Arq );
				fclose(Arq);
				exit(0);
			}
			codigo_atual ++;
	  }while(!feof(Arq));
	produto.Codprod = codigo_atual;
		fwrite ( &produto, sizeof(produto), 1, Arq );
	/* Fecha o arquivo */
	fclose(Arq);
}

/*CORPO DO PROGRAMA*/
int main(){
cadastrar_produto();
return 0;
}
