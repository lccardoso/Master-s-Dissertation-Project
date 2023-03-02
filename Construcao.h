/*Solução Inicial para o problema - Randômica*/
void constroi_solucao(int n, int *y);

void construcao_gulosa(int m, int n, int *c,int *c_aux, int *Ind, int *y, int *z,int *d, int **A, float demand);

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

//Implementação de uma construção com uma lista de instalações candidatas
void construcao_parcial_gulosa(int n, int m, int *c, int *d, int *Ind, int *y, int **A);
