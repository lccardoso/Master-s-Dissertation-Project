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

	int SAmax = 100; // Varivel global, deve vir de fora como parametro
	int i, j, aux;
	float fo_estrela;
	float fo_linha, delta;
	float alphaSA=0.18; //Definir fator de resfriamento, deve vir de fora como parametro
	int IterT;

	float T_zero;
	float T_inicial; //implementar logica para a tempetatura inicial - Utilizando 0.0001 ate a implementacao

	//Inicio do metodo Simulate Anelling

	fo_estrela = fo;
	
	T_inicial = 100;

	while (T_inicial > 0.01) {
		IterT = 0;
		while (IterT < SAmax) {
			IterT += 1;
			
			//Gerar uma nova solucao - Troca  bits
			i = rand() % (n);
			if(y[i]==1){
				y[i] = 0;
			}

			//calcula novo vetor de cobertura
			vetor_cobertura(m, n, A, y, z);

			//calcula nova FO
			fo_linha = calcula_fo(m, n, demand, alpha, d, c, z, y);

			//Calculo Delta
			delta = fo_linha - fo;
			if (delta < 0) {
				fo = fo_linha;
				if (fo_linha < fo_estrela) {
					fo_estrela = fo_linha;
					printf("Solucao melhorada - Novo valor de FO e %f\n " , fo_estrela);
				}
			}
			else
			{
				double x;
				x = randomico(0, 1);
				if (x < exp(-delta / T_inicial)) {
					fo = fo_linha;
				}
				/* Desfaz o movimento caso o vizinho nao seja de melhora
				ou nao passe no teste de aceitacao */
				else {
					if(y[i]==0){
						y[i] = 1;
						}
				}
			}
		}// final de SAmax iteracoes
		T_inicial = T_inicial * alphaSA;
	}// temperatura de congelamento do sistema

	//calcula novo vetor de cobertura
	return fo_estrela;

}
