#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "Util.h"
#include "Construcao.h"

/*Solução Inicial para o problema - Randômica*/
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

/*Cálculo de vetor de cobertura*/
void vetor_cobertura(int m, int n, int **A, int *y, int *z){	
	int soma =0;
	int j;
	
	for(int i=0; i<m ;i++){
		//Inicialmente todas os vertices não são cobertos
		z[i]=0;
		for(int j=0; j<n; j++){
			soma =+ A[i][j]*y[j];
		}
	if(soma>0) z[i]=1;	
	}
}

/*Calculo da função objetivo*/
float calcula_fo(int m, int n, float demand, int alpha, int *d, int *c, int *z, int *y){
	float demand_y=0;
	float f=0;
	
	for (int j=0; j<n;j++){
		f=f+c[j]*y[j];
	}
	for (int i=0; i<m;i++){
		demand_y=demand_y+d[i]*z[i];
	}
	if (demand_y<demand){
		f=f+alpha*(demand-demand_y);
	}	
	return f;
}


