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
//Implementa��o do Simulate Anneling

//	Procedimento (f(.), N(.), Alfa, SAmax, To, s)
//	s* <-- s; {recebe a melhor solu��o obtida ate ent�o}
// 	IterT<--0 {Numero de itera��es na temperatura T - Nesta aplica��o ser� utilizado a Demanda corrente para o problema}
//	T<-- To {Temperatura Corrente}


float SimulateAnneling(int m, int n, float demand, int alpha, int* d, int* c, int* z, int* y, int itermax)
{
	float D;
	int SAmax;



}