/*Solução Inicial para o problema - Randômica*/
void constroi_solucao(int n, int *y);

/*Calculo da demanda corrente para o problema*/
float calcula_demanda(int m, int *d, float porcentagem_d);

/*Cálculo de vetor de cobertura*/
void vetor_cobertura(int m, int n, int **A, int *y, int *z);

/*Calculo da função objetivo*/
float calcula_fo(int m, int n, float demand, int alpha, int *d, int *c, int *z, int *y);

//Funcao auxiliar
bool repeteindice(int *v, int valor, int n);

//Funcao auxiliar
void atribuirvetor(int *v1, int *v2, int n);

//Funcao auxiliar
void trocabit(int j, int *y);

//Funcao auxiliar
void refaz_vetor_cobertura(int pos, int m, int n, int **A, int *y, int *z);

//Funcao auxiliar
int calcula_clientes(int m, int *z);

//Funcao auxiliar
int calcula_facilidades(int n, int *y);
