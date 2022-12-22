#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "Util.h"
#include "Arquivos.h"

using namespace std;

void obter_parametros_fl(char nomearq[], int *m, int *n)
{
	FILE *arquivo;
	int num_facilidades;
	int num_clientes;
	
	arquivo = fopen(nomearq, "r");
	if(!arquivo){
		printf("O arquivo %s nao pode ser aberto. \n", nomearq);
		getchar();
		exit(1);
	}
	
	fscan(arquivo, "%d %d", &num_facilidades, &num_clientes);
	
	*n = num_facilidades;
	*m = num_clientes;
	
	fclose(arquivo);
}


