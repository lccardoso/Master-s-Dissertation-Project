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
//Implementação do Simulate Anneling

//	Procedimento (f(.), N(.), Alfa, SAmax, To, s)
//	s* <-- s; {recebe a melhor solução obtida ate então}
// 	IterT<--0 {Numero de iterações na temperatura T}
//	T<-- To {Temperatura Corrente}


float SimulateAnneling(int m, int n, float demand, int alpha, int* d, int* c, int* z, int* y, int itermax, float fo, int **A)
{

	int SAmax = 150; // Varivel global, deve vir de fora como parametro
	int i, j, aux;
	float fo_estrela;
	float fo_linha, delta;
	float alphaSA=0.98; //Definir fator de resfriamento, deve vir de fora como parametro
	int IterT;
	int *zlinha;
	int *ylinha;
	int *zestrela;
	int *yestrela;
	bool melhorou;

	float T_zero;
	float T_inicial; //implementar logica para a tempetatura inicial - Utilizando 0.0001 ate a implementacao
	
	zlinha = cria_vetor(m);
	ylinha = cria_vetor(n);
	zestrela = cria_vetor(m);
	yestrela = cria_vetor(n);

	//Inicio do metodo Simulate Anelling

	fo_estrela = fo;
	
	T_inicial = 100;

	while (T_inicial > 0.001) {
		IterT = 0;
		while (IterT < SAmax) {
			IterT += 1;

			j = rand() % (n);
			atribuirvetor(zlinha, z, m); 
			atribuirvetor(ylinha, y, n); 
			
			//gerar vizinho - trocar o bit de acordo com o vetor selecionado e a pocição
			trocabit(j, ylinha);
			//calcula novo vetor de cobertura
			refaz_vetor_cobertura(j, m, n, A, ylinha, zlinha);	
			//calcula nova FO
			fo_linha = calcula_fo(m, n, demand, alpha, d, c, zlinha, ylinha);

			//Calculo Delta
			delta = fo_linha - fo;
			if (delta < 0) {
				fo = fo_linha;
				if (fo_linha < fo_estrela) {
					fo_estrela = fo_linha;
					atribuirvetor(zestrela, zlinha, m); //z=zlinha
					atribuirvetor(yestrela, ylinha, n); //y=ylinha
					printf("Solucao melhorada pelo Simulate Annelling %8.2f - Temperatura  -   %8.2f\n " , fo_estrela, T_inicial );
				}
			}
			else
			{
				double x;
				x = randomico(0, 1);
				if (x < exp(-delta / T_inicial)) {
					fo = fo_linha;
					atribuirvetor(z, zlinha, m); //z=zlinha
					atribuirvetor(y, ylinha, n); //y=ylinha
					//printf("Solucao de piora aceita %8.2f - Temperatura  -   %8.2f\n " , fo_estrela, T_inicial );
					melhorou = false;
				}
				else {
					trocabit(j, ylinha);
					melhorou = true;		
				}
			}
		}// final de SAmax iteracoes
	//final do FOR
		T_inicial = T_inicial * alphaSA;
	}// temperatura de congelamento do sistema

	//calcula novo vetor de cobertura
	
	atualiza_vetor(y,yestrela,n);
	atualiza_vetor(z,zestrela,m);
	return fo_estrela;

}
