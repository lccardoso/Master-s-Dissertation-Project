#pragma once
//Função VND
float vnd(int m, int n, int** A, int* d, int* c, int* z, int* y, int alpha, float demand, int itermax);

//Função ILS
float ils(int m, int n, int** A, int* z, int* y, int* d, int* c, int alpha, int itermax, int vezesnivel, float demand, float ilsmaxpercent);