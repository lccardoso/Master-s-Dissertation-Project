//Leitura de dados do arquivo txt
void obter_parametros_fl (char nomearq[], int *m, int *n);

//Leitura de todos os parametros das instancias (Custos, Demanda, etc)
void le_arq_matrizfl(char nomearq[], int m, int n, float **F, float **C, int *c,int *c_aux, int *d, int *Ind);

//Criação de Matriz de distancia FacilidadexCliente
float **cria_matriz_distfl(int m, int n, float **F, float **C);

