/*
Projeto de Disserta��o Mestrado - Metaheur�sticas Aplicadas ao Problema de Localiza��o de Conjuntos Parciais
Autor: Leonardo Correa Cardoso
Local: Centro Federal de Educa��o Tecnol�gica de Minas Gerais  - CEFET MG
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
#include "SimulateAnneling.h"
using namespace std;
//---------------------------------------------------------------------------

/*
M�todo main
*/

int main(int argc, char* argv[]){
	
	int n, 			//n�mero de facilidades
		m, 			//numero de clientes
		*y,			//vetor de facilidades atendidas
		* Ind, 		//Indice de facilidades 
		*c,			//vetor de custo de instala��es
		* c_aux,	//vetor AUXILIAR de custo de instala��o das facilidades
		*d,			//vetor de demandas de clientes
		*z,			//vetor bin�rio de facilidades atendidas
		**A;		//matriz de cobertura bin�ria - Adjac�ncias
	
	float 	**F, 	//matriz  nx2 com as coordenadas das facilidades
			**C, 	//matriz mx2 com as coordenadas dos clientes
			**D;	//matriz de adjac�ncias (dist�ncias)
	
	clock_t 	inicio_CPU,		// clock no inicio da aplicacao do metodo
            	fim_CPU;     	// clock no final da aplicacao do metodo
            
   float demand;	//valor da demanda
   float fo; 		//valor da solu��o - fun��o objetivo
   int ninst;		//quantidade de instala��es ativas
   int ncli;		//quantidade de clientes cobertos
   float TSA;
   
   //Leitura dos arquivos das inst�ncias, montagem das matrizes e vetores para resolu��o do modelo
   
    float raio=5;	//raio de cobertura 
    float porcentagem_d = 0.6;	//percentual da demanda atendido
    int alpha = 1000;
    int betha = 2;
    float gama = 0.95; // Taxa de aceita��o de 95% 
	int itermax=100;	//numero maximo de itera��es - ILS
	int ilsmax=100;		
	int vezesnivel = 2; 
	int SAmax = 10;
	
	char arquivo[] = "inst1.txt";
		
		obter_parametros_fl(arquivo, &m, &n);
		
		printf("Facilidades - Clientes: %d - %d\n\n", n,m);
		
	F= cria_matriz_float(n, 2); //matriz de coordenadas das Facilidades
	C= cria_matriz_float(m, 2); //matriz de coordenadas dos clientes
	D= cria_matriz_float(m, n); //matriz de distancias
	c= cria_vetor(n); //vetor de custo das intala��es
	c_aux = cria_vetor(n); //vetor auxiliar de custo das instala��es
	d= cria_vetor(m); //vetor de demandas dos clientes
	Ind = cria_vetor(n); //vetor de indice de facilidades
	y= cria_vetor(n); //vetor de facilidades abertas
	z= cria_vetor(m); //vetor de clientes atendidos por pelo menos uma facilidade
	A= cria_matriz(m, n); //matriz de Adjac�ncias
	
	le_arq_matrizfl(arquivo, m, n, F, C, c, d);
	D=cria_matriz_distfl(m, n, F, C);
	cria_matriz_adj(m, n, raio, D, A);
	
	/*Inicio da Execu��o dos M�todos Heur�sticos*/
		
	/*Calculo da demanda corrente para o problema*/
	demand=calcula_demanda(m, d, porcentagem_d);	
	printf("Demanda atual do problema a ser atendida e %.5f\n ",  demand);
	
	/*Constru��o de solu��o inicial - Rand�mica*/
	constroi_solucao(n, y);
	
	/*Constru��o de solu��o inicial - Gulosa*/
	//construcao_gulosa(m, n, c, c_aux, Ind, y,  z, d, A, demand);
	
	
	//construcao_parcial_gulosa(n,m,demand,porcentagem_d,c,d,z,Ind,y,A);
	//fo=calcula_fo(m, n, demand, alpha, d, c, z, y);
	
	
	vetor_cobertura(m, n, A, y, z);
	fo = calcula_fo(m, n, demand, alpha, d, c, z, y);
	ncli = calcula_clientes(m, z);
	ninst = calcula_facilidades(n, y);
	
	printf("FO da solucao incial: %.5f - Clientes Atendidos: %d - Instalacoes Abertas: %d\n", fo, ncli, ninst);
	
	inicio_CPU = clock();
	srand((unsigned) time(NULL)); // pega a hora do relogio como semente
	
	//Metodo Simulate Annelling
	//Calculo da temperatura inicial
	TSA = Temp_InicialSA(betha, gama,SAmax,demand,y,z,fo,n,m,alpha,d,c,A);
	printf("Temperatura inicial %f\n " , TSA);
	system("PAUSE");
	//Define vetro de cobertura
	vetor_cobertura(m, n, A, y, z);
	ninst = calcula_facilidades(n, y);
	ncli = calcula_clientes(m, z);
	//Execucao do metodo SA
	fo = SimulateAnneling(m, n, demand, alpha, d, c, z, y, itermax, fo, A);
	
	/*
	vetor_cobertura(m,n,A,y,z);
	fo=calcula_fo(m, n, demand, alpha, d, c, z, y);
	ninst = calcula_facilidades(n, y);
	ncli = calcula_clientes(m, z);
	printf("Fo da solucao incial: %.5f - Clientes atendidos: %d - Facilidades abertas: %d\n",fo, ncli, ninst);
	*/
		
	
	/*
	//Refinamento	
	fo=ils (m, n, A, z, y, d, c, alpha, itermax,  vezesnivel,  demand, 0.6);
	*/
	
	fim_CPU = clock();
	printf("Tempo execucao = %10.2f segundos\n",(float)(fim_CPU - inicio_CPU)/CLOCKS_PER_SEC);
	
	ninst = calcula_facilidades(n, y);
	ncli = calcula_clientes(m, z);
	
	float demanda_atendida=0;
		for (int i=0; i<m;i++){
			demanda_atendida=demanda_atendida + z[i]*d[i];
		}
	
	printf("FO Solucao Final - Simulate Anneling: %f - Clientes Atendidos: %d - Instalacoes Abertas: %d - Demanda Atendida: %f\n",fo, ncli, ninst, demanda_atendida);
	for (int i=0; i<n; i++){
		if (y[i]==1) printf("Facilidade aberta: %d\n",i);
	}
	
	
	fim_CPU = clock();
	

	
	system("PAUSE");
    return 0;
   	            
}

