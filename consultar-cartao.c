// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// PROTOTIPOS
void ver_cartoes_registrados(void);

// FUNCOES
void ver_cartoes_registrados(void) {
	system("cls");
    FILE *cartoes = fopen("CARTOES.DAT", "rb"); // Abre o arquivo em modo leitura binária

    if (cartoes == NULL) {
        printf("Erro ao abrir o arquivo CARTOES.DAT\n");
        return;
    }

    printf("\n=== CARTOES REGISTRADOS ===\n");
    printf("Cod. Pagamento\tNumero do Cartao\n");
    printf("---------------------------------\n");

    // Le os registros um a um
    while (fread(&cartao, sizeof(DADOSCARTAO), 1, cartoes) == 1) {
        printf("%03d\t%s\n", cartao.Codpgto, cartao.NumeroCartao);
    }
    fclose(cartoes);
    getch(); // Espera o usuario apertar uma tecla
}


// CORPO DO PROGRAMA
int main ()
{
	ver_cartoes_registrados();
	return 0;
}
