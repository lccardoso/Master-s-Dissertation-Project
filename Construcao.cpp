#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <vector>
#include "Util.h"
#include "Construcao.h"

/*Solu��o Inicial para o problema - Rand�mica*/
void constroi_solucao(int n, int* y) {
	srand((unsigned)time(NULL)); // pega a hora do relogio como semente
	for (int j = 0; j < n; j++) {
		y[j] = rand() % (2);
	}
}

/*Construcao de Solucao Inicial Gulosa*/
void construcao_gulosa(int m, int n, int* c, int* c_aux, int* Ind, int* y, int* z, int* d, int** A, float demand) {
	int aux = 0;
	int aux2 = 0;
	int cont = 0;
	int dem = 0;
	int iterMax = 0;
	int cont2 = 0;
	int somaC = 0;
	int somaF = 0;
	int demanda = 0;
	double demand1 = 0;
	int FO = 0;

	//Ordena�ao dos vetores de custo de abertura das facilidades em ordem crescente 
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (c[j] < c[i]) {
				aux = c[j];
				aux2 = Ind[j];
				c[j] = c[i];                // Ordena os custos e os indices
				Ind[j] = Ind[i];
				c[i] = aux;
				Ind[i] = aux2;
			}
		}

		printf("  O custo de abertura da instalacao  %d  e  %d  \n", Ind[i], c[i]);

	}

	//Implementa�ao do Vetor de abertuta de facilidades (0-1) 
	for (int i = 0; i < n; i++) {
		y[i] = 0;
		//printf(" %d", y[i]);		
	}

	//Calculo da demanda total a ser atendida
	for (int j = 0; j < m; j++) {
		demanda = demanda + d[j];
	}
	printf("  O valor da demanda total  e %d \n", demanda);

	//Calculo d do percentual da  demanda a atendida
	demand = (demanda) * 0.5;
	printf("  O Valor de demanda minimo a ser atendida e %f \n", demand);

	//Implementa��o do m�todo
	while (demand >= dem) {

		//----------------------------------------------------------------------------------------// 
		int aux3 = 0;
		//Ativa��o das facilidades
		aux3 = Ind[cont];
		for (int i = 0; i < n; i++) {
			if (aux3 == i)
				y[i] = 1;
			//printf(" %d ", y[i]);
		}

		//Declara�ao vari�vel de Fun�ao Objetivo


		//Calculo de vetor de Cobertura
		int soma;
		for (int i = 0; i < m; i++) {
			soma = 0;
			z[i] = 0; //inicialmente, o v�rtice i n�o � coberto
			for (int j = 0; j < n; j++) {
				soma = soma + A[i][j] * y[j];
			}
			if (soma > 0) z[i] = 1; //Caso o n� i seja coberto por alguma facilidade, y[i] ser� trocado para 1
			//printf(" %d", z[i]);
		}

		//Calculo de demanda atendida
		for (int j = 0; j < m; j++) {
			dem = dem + d[j] * z[j];
		}

		cont2++;
		cont++;
		iterMax++;
		//printf(" O Valor da demanda atendida e  %d \n", dem);
		//system("PAUSE");

	}

	//Retorno do m�todo
	for (int i = 0; i < n; i++) {
		if (y[i] == 1)somaF = somaF + 1;
		//printf(" %d ", y[i]);
		//Calculo FO Inicial
		if (y[i] != 0) {
			FO = FO + c_aux[i];
		}
	}

	for (int i = 0; i < m; i++) {
		if (z[i] == 1)somaC = somaC + 1;
	}

	printf(" O Valor da demanda atendida e  %d \n", dem);
	printf("\n");
	printf("  FO da Solucao Inicial Gulosa e %d \n", FO);
	printf(" Facilidades Abertas   %d \n", somaF);
	printf(" Clientes Atendidos  %d \n", somaC);

}

/*Calculo da demanda corrente para o problema*/
float calcula_demanda(int m, int* d, float porcentagem_d) {
	float demand = 0;
	for (int i = 0; i < m; i++) {
		demand = demand + d[i];
	}
	return porcentagem_d * demand;
}

/*C�lculo de vetor de cobertura*/
void vetor_cobertura(int m, int n, int** A, int* y, int* z) {
	int soma = 0;
	int j;

	for (int i = 0; i < m; i++) {
		//Inicialmente todas os vertices n�o s�o cobertos
		z[i] = 0;
		for (int j = 0; j < n; j++) {
			soma = +A[i][j] * y[j];
		}
		if (soma > 0) z[i] = 1;
	}
}

/*Calculo da fun��o objetivo*/
float calcula_fo(int m, int n, float demand, int alpha, int* d, int* c, int* z, int* y) {
	float demand_y = 0;
	float f = 0;

	for (int j = 0; j < n; j++) {
		f = f + c[j] * y[j];
	}
	for (int i = 0; i < m; i++) {
		demand_y = demand_y + d[i] * z[i];
	}
	if (demand_y < demand) {
		f = f + alpha * (demand - demand_y);
	}
	return f;
}

//Fun��o auxliar
bool repeteindice(int* v, int valor, int n)
{
	int rep = 0;

	for (int i = 0; i < n; i++) {
		if (v[i] == valor) rep++;
	}

	if (rep > 1) {
		return true;
	}
	else {
		return false;
	}

}

//Fun��o auxliar	
void atribuirvetor(int* v1, int* v2, int n) {
	for (int i = 0; i < n; i++) {
		v1[i] = v2[i];
	}
}

//Fun��o auxliar
void trocabit(int j, int* y)
{

	if (y[j] == 0) {
		y[j] = 1;
	}
	else {
		y[j] = 0;
	}

}

//Fun��o auxiliar
void refaz_vetor_cobertura(int pos, int m, int n, int** A, int* y, int* z)
{
	int coberto = 0;
	int j;

	if (y[pos] == 0)
	{
		//vetor_cobertura(m, n, A, y, z);

		int coberto;
		for (int i = 0; i < m; i++) {
			//if (z[i]==1) {
			if (A[i][pos] == 1) {

				coberto = 0;
				j = 0;
				while ((coberto == 0) && (j < n)) {

					z[i] = 0;

					if (A[i][j] * y[j] == 1) {
						coberto = 1;
						z[i] = 1;
					}
					else {
						j = j + 1;
					}
				}

			}

		}

	}

	if (y[pos] == 1)
	{
		for (int i = 0; i < m; i++) {
			if (A[i][pos] == 1) {
				z[i] = 1;
			}

		}

	}


}

//Fun��o auxiliar
int calcula_facilidades(int n, int* y) {
	int soma = 0;

	for (int i = 0; i < n; i++) {
		soma = soma + y[i];
	}
	return soma;
}

//Fun��o auxiliar
int calcula_clientes(int m, int* z) {
	int soma = 0;

	for (int i = 0; i < m; i++) {
		soma = soma + z[i];
	}
	return soma;
}



