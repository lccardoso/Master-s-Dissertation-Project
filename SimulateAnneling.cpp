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
// 	IterT<--0 {Numero de iterações na temperatura T - Nesta aplicação será utilizado a Demanda corrente para o problema}
//	T<-- To {Temperatura Corrente}


float SimulateAnneling(int m, int n, float demand, int alpha, int* d, int* c, int* z, int* y, int itermax)
{
	float D;
	int SAmax;



}