// cria memoria para um vetor de tam posicoes
int *cria_vetor(int tam);

// cria memoria para um vetor de tam posicoes
float *cria_vetor_float(int tam);

// Cria matriz de ponteiros para inteiros com nlinhas e ncolunas
int **cria_matriz(int nlinhas, int ncolunas);

// Cria matriz de ponteiros para inteiros com nlinhas e ncolunas
float **cria_matriz_float(int nlinhas, int ncolunas);

// Cria matriz de adjjacencias para inteiros com nlinhas e ncolunas 
void **cria_matriz_adj(int m, int n, float raio, float **D, int **A);

// libera memoria de um vetor 
void libera_vetor(int *vetor);

// libera memoria Matriz
void libera_matriz(int **matriz, int nlinhas);

// libera memoria Matriz 
void libera_matriz_float(float **matriz, int nlinhas);

// imprime a solucao 
void imprime_vetor(int *s, int n);

// imprimir matriz
void imprime_matriz(int **adj, int m, int n);

// imprimir matriz
void imprime_matriz_float(float **adj, int m, int n);

/* Gera numero aleatorio entre min e max */
float randomico(float min, float max);

/*Atualiza vetor de solucao*/
void atualiza_vetor(int *s_star, int *s, int n);

/*Gera a temperatura inicial para o m�todo Simulate Annelling*/
float Temp_InicialSA(int betha, float gama, int SAmax,float demand, int *y,int *z, float fo, int n, int m,int alpha, int* d, int* c,int **A);
