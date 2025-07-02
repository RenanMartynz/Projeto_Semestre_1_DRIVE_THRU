// BIBLIOTECAS
#include "Drive-Thru-Lib.h"

// CORPO DO PROGRAMA
int main ()
{
	Arq = fopen ("FILA.DAT", "rb");
	do
	{
		fread(&posicao, sizeof(posicao), 1,Arq);
		if (!feof(Arq))
		{
		printf("\n%i\t%i", posicao.Codpgto, posicao.Poscod);
		}
	}
	while(!feof(Arq));
	fclose(Arq);
	getch();
	return 0;
}
