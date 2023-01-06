#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "Util.h"
#include "Construcao.h"

/*Solu��o Inicial para o problema - Rand�mica*/
void constroi_solucao(int n, int *y){
 	srand((unsigned) time(NULL)); // pega a hora do relogio como semente
 	for (int j=0; j<n; j++){
 		y[j]= rand() % (2);
	 }
}

/*Calculo da demanda corrente para o problema*/
float calcula_demanda(int m, int *d, float porcentagem_d){
	float demand=0;
	for(int i=0; i<m; i++){
		demand = demand+d[i];
	}
	return porcentagem_d*demand;
}


