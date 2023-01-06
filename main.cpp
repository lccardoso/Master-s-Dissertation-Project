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
using namespace std;
//---------------------------------------------------------------------------

/*
M�todo main
*/

int main(int argc, char* argv[]){
	
	int n, 			//n�mero de facilidades
		m, 			//numero de clientes
		*y,			//vetor de facilidades atendidas
		*c,			//vetor de custo de instala��es
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
   
   //Leitura dos arquivos das inst�ncias, montagem das matrizes e vetores para resolu��o do modelo
   
    float raio=5.5;	//raio de cobertura 
    float porcentagem_d = 0.5;	//percentual da demanda atendido
    int alpha = 1000;
	int itermax=100;	//numero maximo de itera��es - ILS
	int ilsmax=10;		
	int vezesnivel = 2; 
	
	char arquivo[] = "inst1.txt";
		
		obter_parametros_fl(arquivo, &m, &n);
		
		printf("Facilidades - Clientes: %d - %d\n\n", n,m);
		
	F= cria_matriz_float(n, 2); //matriz de coordenadas das Facilidades
	C= cria_matriz_float(m, 2); //matriz de coordenadas dos clientes
	D= cria_matriz_float(m, n); //matriz de distancias
	c= cria_vetor(n); //vetor de custo das intala��es
	d= cria_vetor(m); //vetor de demandas dos clientes
	y= cria_vetor(n); //vetor de facilidades abertas
	z= cria_vetor(m); //vetor de clientes atendidos por pelo menos uma facilidade
	A= cria_matriz(m, n); //matriz de Adjac�ncias
	
	le_arq_matrizfl(arquivo, m, n, F, C, c, d);
	D=cria_matriz_distfl(m, n, F, C);
	cria_matriz_adj(m, n, raio, D, A);
	
	/*Inicio da Execu��o dos M�todos Heur�sticos*/
	inicio_CPU = clock();
	srand((unsigned) time(NULL)); // pega a hora do relogio como semente	
	
	demand=calcula_demanda(m, d, porcentagem_d);	
	printf("Demanda atual do problema %.5f\n ",  demand);
	
	fim_CPU = clock();
	
	
	system("PAUSE");
    return 0;
   	            
}

