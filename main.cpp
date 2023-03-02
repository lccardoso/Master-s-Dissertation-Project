/*
Projeto de Dissertação Mestrado - Metaheurísticas Aplicadas ao Problema de Localização de Conjuntos Parciais
Autor: Leonardo Correa Cardoso
Local: Centro Federal de Educação Tecnológica de Minas Gerais  - CEFET MG
Data: 02/01/2023
*/


/*
Bibliotecas e Imports
*/
//---------------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "Arquivos.h"
#include "Construcao.h"
#include "Util.h"
#include "heuristicas.h"
using namespace std;
//---------------------------------------------------------------------------

/*
Método main
*/

int main(int argc, char* argv[]){
	
	int n, 			//número de facilidades
		m, 			//numero de clientes
		*y,			//vetor de facilidades atendidas
		* Ind, 		//Indice de facilidades 
		*c,			//vetor de custo de instalações
		* c_aux,	//vetor AUXILIAR de custo de instalação das facilidades
		*d,			//vetor de demandas de clientes
		*z,			//vetor binário de facilidades atendidas
		**A;		//matriz de cobertura binária - Adjacências
	
	float 	**F, 	//matriz  nx2 com as coordenadas das facilidades
			**C, 	//matriz mx2 com as coordenadas dos clientes
			**D;	//matriz de adjacências (distâncias)
	
	clock_t 	inicio_CPU,		// clock no inicio da aplicacao do metodo
            	fim_CPU;     	// clock no final da aplicacao do metodo
            
   float demand;	//valor da demanda
   float fo; 		//valor da solução - função objetivo
   int ninst;		//quantidade de instalações ativas
   int ncli;		//quantidade de clientes cobertos
   
   //Leitura dos arquivos das instâncias, montagem das matrizes e vetores para resolução do modelo
   
    float raio=5.750;	//raio de cobertura 
    float porcentagem_d = 0.5;	//percentual da demanda atendido
    int alpha = 1000;
	int itermax=100;	//numero maximo de iterações - ILS
	int ilsmax=10;		
	int vezesnivel = 2; 
	
	char arquivo[] = "inst2.txt";
		
		obter_parametros_fl(arquivo, &m, &n);
		
		printf("Facilidades - Clientes: %d - %d\n\n", n,m);
		
	F= cria_matriz_float(n, 2); //matriz de coordenadas das Facilidades
	C= cria_matriz_float(m, 2); //matriz de coordenadas dos clientes
	D= cria_matriz_float(m, n); //matriz de distancias
	c= cria_vetor(n); //vetor de custo das intalações
	c_aux = cria_vetor(n); //vetor auxiliar de custo das instalações
	d= cria_vetor(m); //vetor de demandas dos clientes
	Ind = cria_vetor(n); //vetor de indice de facilidades
	y= cria_vetor(n); //vetor de facilidades abertas
	z= cria_vetor(m); //vetor de clientes atendidos por pelo menos uma facilidade
	A= cria_matriz(m, n); //matriz de Adjacências
	
	le_arq_matrizfl(arquivo, m, n, F, C, c, c_aux, d, Ind);
	D=cria_matriz_distfl(m, n, F, C);
	cria_matriz_adj(m, n, raio, D, A);
	
	/*Inicio da Execução dos Métodos Heurísticos*/
		
	/*Calculo da demanda corrente para o problema*/
	demand=calcula_demanda(m, d, porcentagem_d);	
	//printf("Demanda atual do problema %.5f\n ",  demand);
	
	/*Construção de solução inicial - Randômica*/
	//constroi_solucao(n, y);
	
	/*Construção de solução inicial - Gulosa*/
	//construcao_gulosa(m, n, c, c_aux, Ind, y,  z, d, A, demand);
	
	construcao_parcial_gulosa(n, m, c, d, Ind, y, A);
	
	/*
	vetor_cobertura(m,n,A,y,z);
	fo=calcula_fo(m, n, demand, alpha, d, c, z, y);
	ninst = calcula_facilidades(n, y);
	ncli = calcula_clientes(m, z);
	printf("Fo da solucao incial: %.5f - Clientes atendidos: %d - Facilidades abertas: %d\n",fo, ncli, ninst);
	
	inicio_CPU = clock();
	srand((unsigned) time(NULL)); // pega a hora do relogio como semente	
	
	//Refinamento	
	fo=ils (m, n, A, z, y, d, c, alpha, itermax,  vezesnivel,  demand, 0.6);
	
	fim_CPU = clock();
	printf("Tempo execucao = %10.2f segundos\n",(float)(fim_CPU - inicio_CPU)/CLOCKS_PER_SEC);
	
	ninst = calcula_facilidades(n, y);
	ncli = calcula_clientes(m, z);
	
	float demanda_atendida=0;
		for (int i=0; i<m;i++){
			demanda_atendida=demanda_atendida + z[i]*d[i];
		}
	
	printf("Fo da solucao Final Refinada: %f - Clientes atendidos: %d - Facilidades abertas: %d - Demanda atendida: %f\n",fo, ncli, ninst, demanda_atendida);
	for (int i=0; i<n; i++){
		if (y[i]==1) printf("Facilidade aberta: %d\n",i);
	}
	
	fim_CPU = clock();
	
*/
	
	system("PAUSE");
    return 0;
   	            
}

