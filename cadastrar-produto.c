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

	   
do {
    printf("\nDescricao do produto (sem acento ou simbolo): ");
    fflush(stdin);
    fgets(produto.Nomeprod, sizeof(produto.Nomeprod), stdin);
    produto.Nomeprod[strcspn(produto.Nomeprod, "\n")] = '\0';
    
    if (!valida_simples(produto.Nomeprod))
        printf("Entrada inválida. Tente novamente.\n");
} while (!valida_simples(produto.Nomeprod)); 
  
	do {
    possuiErro = 0;
    custoProduto = 0;
    int indice = 0;
    int encontrouSeparador = 0;
    int casasDecimais = 0;

    printf("\nCusto do produto : ");
    fgets(entrada, 50, stdin);

    while (entrada[indice] && entrada[indice] != '\n') {
        char caractere = entrada[indice];

        if (caractere >= '0' && caractere <= '9') {
            custoProduto = custoProduto * 10 + (caractere - '0');
            if (encontrouSeparador) casasDecimais++;
        } else if (caractere == '.' || caractere == ',') {
            if (encontrouSeparador) possuiErro = 1;
            encontrouSeparador = 1;
        } else {
            possuiErro = 1;
        }

        indice++;
    }

    if (!possuiErro) {
        while (casasDecimais--) custoProduto /= 10;
        produto.Custoprod = custoProduto;
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
