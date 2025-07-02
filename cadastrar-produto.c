/*BIBLIOTECAS*/
#include "Drive-Thru-Lib.h"

/* Variaveis globais */
char entrada[50];
float custoProduto;
int possuiErro;

/* PROTOTIPOS DE FUNCOES */
void cadastrar_produto(void);
void gravaArq (void);
int valida_simples(char *s);

/* IMPLEMENTACAO DAS FUNCOES */

/* Valida se a string so contem letras maiusculas, minusculas, numeros e espacos */
int valida_simples(char *s) {
    int i;
    for (i = 0; s[i]; i++) {
        if (!(s[i] >= 'a' && s[i] <= 'z') &&
            !(s[i] >= 'A' && s[i] <= 'Z') &&
            !(s[i] >= '0' && s[i] <= '9') &&
             s[i] != ' ') 
            return 0;  // Se caractere invalido encontrado, retorna 0
    }
    return 1; //  se estiver udo certo, retorna 1
}

/* Funcao principal para cadastrar produtos */
void cadastrar_produto(void) {
   char op;
    char opc;
    
    system("cls");
    
    printf("==================== Cadastrar produtos =====================\n");
    printf("Pressione qualquer tecla para continuar ou [0=VOLTAR AO MENU]");
    opc = getche();
    if(opc != '0'){
	

	    do {
	        system("cls");      // Limpa a tela
	        system("color 2f"); // Muda a cor do console para verde com fundo branco
	
	        /* Pede a descricao do produto e valida */
	        do {
	            printf("\nDescricao do produto (sem acento ou simbolo): ");
	            fflush(stdin);
	            fgets(produto.Nomeprod, sizeof(produto.Nomeprod), stdin);
	            produto.Nomeprod[strcspn(produto.Nomeprod, "\n")] = '\0'; // Remove '\n' do final
	
	            if (!valida_simples(produto.Nomeprod)) // Verifica se a entrada e invalida
	                printf("Entrada invalida. Tente novamente.\n"); // Mensagem de erro
	
	        } while (!valida_simples(produto.Nomeprod)); // Repete ate que seja valido
	        
	
	        /* Pede o custo do produto e valida */
	        do {
	            possuiErro = 0;    // Inicializa flag de erro
	            custoProduto = 0;  // Zera o custo temporario
	            int indice = 0;
	            int encontrouSeparador = 0;
	            int casasDecimais = 0;
	
	            printf("\nCusto do produto : ");
	            fgets(entrada, 50, stdin);
	
	            // Percorre cada caractere da string ate o '\0' ou '\n'
	            while (entrada[indice] && entrada[indice] != '\n') {
	                char caractere = entrada[indice];
	
	                if (caractere >= '0' && caractere <= '9') { 
	                    // Converte caractere numerico em valor inteiro e adiciona ao custoProduto
	                    custoProduto = custoProduto * 10 + (caractere - '0'); 
	                    if (encontrouSeparador) 
	                        casasDecimais++; // Conta as casas decimais apos o separador
	                } else if (caractere == '.' || caractere == ',') { 
	                    // Verifica se ja encontrou um separador decimal
	                    if (encontrouSeparador) 
	                        possuiErro = 1; // Erro se tiver mais de um separador
	                    encontrouSeparador = 1; // Marca que encontrou separador
	                } else {
	                    possuiErro = 1; // Caractere invalido -> erro
	                }
	
	                indice++; // Avanca para o proximo caractere
	            }
	
	            if (!possuiErro) {
	                // Ajusta o custo dividindo pelas casas decimais
	                while (casasDecimais--) 
	                    custoProduto /= 10;
	
	                produto.Custoprod = custoProduto; // Atribui o valor convertido a struct
	            } else {
	                printf("Valor invalido. Digite novamente apenas numeros e um separador decimal.\n");
	            }
	
	        } while (possuiErro); // Repete enquanto houver erro na entrada do custo
	
	        gravaArq(); // Chama funcao para gravar produto no arquivo
	
	        printf("\nDeseja cadastrar outro produto? [0=NAO]:");
	        fflush(stdin);
	        op = getche(); // Le a opcao do usuario sem esperar ENTER
	
	    } while (op != '0'); // Continua cadastrando enquanto nao digitar '0'
	}
}

/* Funcao para gravar o produto no arquivo PRODUTOS.DAT */
void gravaArq (void)
{
    CARDAPIO c;
    int codigo_atual = 0;
    /* Abre o arquivo em modo leitura e escrita binaria */
    Arq = fopen ("PRODUTOS.DAT", "rb+");

    /* Verifica se o arquivo existe */
    if (Arq == NULL)
    {
        printf ("\nERRO AO ABRIR O PRODUTOS.DAT");
        printf ("\nEndereco lido: %p", Arq);
        getch();
        exit(1);
    }

    /* Mostra endereco do arquivo aberto */
    printf ("\nEndereco de PRODUTOS.DAT: %p", Arq);

    /* Percorre o arquivo procurando por registro com Codigo 0 */
    do { 
        fread(&c, sizeof(c), 1, Arq);
        if (c.Codprod == 0) { // Se encontrou lugar vazio
            fseek(Arq, codigo_atual * sizeof(produto), SEEK_SET); 
            produto.Codprod = codigo_atual + 1; // Define codigo do produto
            fwrite(&produto, sizeof(produto), 1, Arq); // Grava o produto no arquivo
            fclose(Arq); 
            exit(1);     
        }
        codigo_atual++; // Incrementa codigo para proxima posicao
    } while (!feof(Arq)); // Continua enquanto nao chegar no final do arquivo

    /* Se nao encontrou espaco vazio, grava no final */
    produto.Codprod = codigo_atual;
    fwrite(&produto, sizeof(produto), 1, Arq);

    /* Fecha o arquivo */
    fclose(Arq);
}

/* CORPO PRINCIPAL DO PROGRAMA */
int main() {
    cadastrar_produto();
    return 0;
}
