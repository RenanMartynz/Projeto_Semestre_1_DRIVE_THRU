/*BIBLIOTECAS*/
#include "Drive-Thru-Lib.h"

/* PROTOPIPOS DE FUNCOES */
void cadastrar_produto(void);
void gravaArq (void);

/* CONSTRUCAO DAS FUNCOES */

// Remove acentos e caracteres especiais, mantendo apenas letras simples, números e espaços
void sanitizar_nome(char *str) {
    int i, j = 0;
    char ch;
    for (i = 0; str[i] != '\0'; i++) {
        ch = str[i];
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9') || ch == ' ') {
            str[j++] = ch;
        }
    }
    str[j] = '\0';
}

void cadastrar_produto(void) {
    char op;

    do {
        system("cls");

        printf("\nDescricao do produto (max 100 caracteres): ");
        fflush(stdin);
        fgets(produto.Nomeprod, MAX_NOME, stdin);

        // Remove quebra de linha se estiver presente
        produto.Nomeprod[strcspn(produto.Nomeprod, "\n")] = '\0';

        // Limpa acentos e caracteres especiais
        sanitizar_nome(produto.Nomeprod);

        printf("\nCusto do produto    : ");
        fflush(stdin);
        scanf("%f", &produto.Custoprod);

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
