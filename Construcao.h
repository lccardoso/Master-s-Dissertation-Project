/*Solu��o Inicial para o problema - Rand�mica*/
void constroi_solucao(int n, int *y);

/*Calculo da demanda corrente para o problema*/
float calcula_demanda(int m, int *d, float porcentagem_d);

/*C�lculo de vetor de cobertura*/
void vetor_cobertura(int m, int n, int **A, int *y, int *z);

/*Calculo da fun��o objetivo*/
float calcula_fo(int m, int n, float demand, int alpha, int *d, int *c, int *z, int *y);

