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

//Função auxliar
bool repeteindice(int *v, int valor, int n)
	{
		int rep = 0;
		
		for (int i=0; i<n; i++){
			if (v[i]==valor) rep++;
		}
		
		if (rep > 1){
			return true;
		}else{
			return false;
		}
		
	}

//Função auxliar	
void atribuirvetor(int *v1, int *v2, int n){
	for (int i=0; i<n;i++){
		v1[i]=v2[i];
	}
}

//Função auxliar
void trocabit(int j, int *y)
{
	
	if (y[j]==0){
		y[j]=1;
	}else{
		y[j]=0;
	}
	
}

//Função auxiliar
void refaz_vetor_cobertura(int pos, int m, int n, int **A, int *y, int *z)
{
	int coberto = 0;
	int j;
	
	if (y[pos]==0)
	{
		//vetor_cobertura(m, n, A, y, z);
			
	int coberto;
	for (int i=0; i<m;i++){
		//if (z[i]==1) {
		if (A[i][pos]==1){
			
		coberto = 0;
		j=0;
		while((coberto==0) && (j<n)){
		
		z[i]=0;
		
			if (A[i][j]*y[j]==1){
				coberto = 1;
				z[i]=1;
			}else{
				j=j+1;
			}
		}	

		}
		
	}
				
	}
	
	if (y[pos]==1)
	{
		for (int i=0; i<m;i++){
			if (A[i][pos]==1){
				z[i]=1;
			}
			
		}
		
	}
	

}

//Função auxiliar
int calcula_facilidades(int n, int *y){
	int soma=0;
	
	for (int i=0; i<n; i++){
		soma=soma+y[i];
	}
	return soma;
}

//Função auxiliar
int calcula_clientes(int m, int *z){
	int soma=0;
	
	for (int i=0; i<m; i++){
		soma=soma+z[i];
	}
	return soma;
}




