#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "Util.h"
#include "Arquivos.h"

using namespace std;


void obter_parametros_fl(char nomearq[], int *m, int *n)
{

  FILE *arquivo;
  int num_facilidades;
  int num_clientes;

  arquivo = fopen(nomearq,"r");
  if (!arquivo) {
     printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
     getchar();
     exit(1);
  }
  
  fscanf(arquivo, "%d %d", &num_facilidades, &num_clientes);

  *n = num_facilidades;
  *m = num_clientes;

  fclose(arquivo);
}


void le_arq_matrizfl(char nomearq[], int m, int n, float **F, float **C, int *c, int *d)
{
  int i, j, index, valor;
  float x,y;
  float **Coord;
  int *valores;
  char type[1];
  FILE *arquivo;
  
  Coord = cria_matriz_float(m+n+1, 2);
  valores = cria_vetor(m+n+1);
	
	i=0;
	j=0;
	
  //vet_x = cria_vetor(n);
  //vet_y = cria_vetor(n);
  arquivo = fopen(nomearq,"r");
  if (!arquivo) {
     printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
     getchar();
     exit(1);
  }
  
  i=0;
  while (!feof(arquivo)){

		fscanf(arquivo, "%c %d %f %f %d \n", type, &index, &x, &y, &valor);
		Coord[i][0]=x;
		Coord[i][1]=y;
		valores[i]=valor;
		i++;
	}

	for (j=1; j<= n; j++){
		F[j-1][0]=Coord[j][0];
		F[j-1][1]=Coord[j][1];
		c[j-1]=valores[j];
	}
	
	//imprime_matriz_float(F,n,2);
	
	
	for (j=0; j< m; j++){
		C[j][0]=Coord[j+n+1][0];
		//printf("%.5f ",C[j][0]);
		C[j][1]=Coord[j+n+1][1];
		//printf("%.5f ",C[j][0]);
		d[j]=valores[j+n+1];
	}

	//imprime_matriz_float(F,m,2);
	
  fclose(arquivo);

}


float **cria_matriz_distfl(int m, int n, float **F, float **C){
	float **matriz;
	matriz = cria_matriz_float(m, n);
	int i,j;
	for (i=0; i<m;i++){
		
		for (j=0; j<n; j++){
			matriz[i][j]=(float) sqrtf(pow(C[i][0]-F[j][0],2)+pow(C[i][1]-F[j][1],2));
		}
	}	
	
	return matriz;
}



//FIM DAS NOVAS FUNÇÕES DE LEITURA




/* le um arquivo no formato num_cid coord_x coord_y e calcula as distancias d_ij  */
void le_arq_matriz(char nomearq[], int n, int **adj)
{
  int *vet_x, *vet_y;
  int x, y, i, j, a, k;
  FILE *arquivo;

  //vet_x = cria_vetor(n);
  //vet_y = cria_vetor(n);
  arquivo = fopen(nomearq,"r");
  if (!arquivo) {
     printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
     getchar();
     exit(1);
  }
i=0;
j=0;
while (!feof(arquivo)){
    for (j=0; j < n; j++) {
    	fscanf(arquivo, "%d", &a);
  		adj[i][j]=a;
    }
	i++;
	/*fscanf(arquivo, "%d %d %d", &i, &x, &y);
    vet_x[i] = x;
    vet_y[i] = y;*/
  }
  
  /*
  while (!feof(arquivo)){
    fscanf(arquivo, "%d %d %d", &i, &x, &y);
    vet_x[i] = x;
    vet_y[i] = y;
  }


  // gera a matriz de distancias calculado a partir das distancias euclidianas dos pontos
  for(i=0; i < n-1; i++)
  {
     distancia[i][i] = 0;
     for(j=i+1; j < n; j++){
        distancia[i][j] = (float) sqrtf(pow(vet_x[i]-vet_x[j],2)+pow(vet_y[i]-vet_y[j],2));
        distancia[j][i] = distancia[i][j];
     }
  }
  fclose(arquivo);
  libera_vetor(vet_x);
  libera_vetor(vet_y);*/
  fclose(arquivo);

}


/* le um arquivo no formato "numero_cidades melhor_fo_literatura" */
void obter_parametros_pcv(char nomearq[], int *n, float *melhor_fo_lit)
{

  FILE *arquivo;
  int num_cidades;
  float melhor_fo_literatura;

  arquivo = fopen(nomearq,"r");
  if (!arquivo) {
     printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
     getchar();
     exit(1);
  }
  fscanf(arquivo, "%d %f", &num_cidades, &melhor_fo_literatura);

  *n = num_cidades;
  *melhor_fo_lit = melhor_fo_literatura;

  fclose(arquivo);
}



void imprime_fo(char nomearq[], float tempo, float fo, int iteracao)
{
    FILE *arquivo;
    arquivo = fopen(nomearq,"a+");

    if (!arquivo){
        printf("O arquivo %s nao pode ser aberto",nomearq);
        getchar();
        exit(1);
    }
    fprintf(arquivo,"%4.2f\t  %4d\t  %7.2f\n",tempo, iteracao, fo);
    fclose(arquivo);
}


/* le um arquivo no formato i, valor */
void le_arq_vetor(char nomearq[], int *vetor)
{
  int j,
    valor;
  FILE *arquivo;

  arquivo = fopen(nomearq,"r");
  if (!arquivo) {
     printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
     getchar();
     exit(1);
  }
  while (!feof(arquivo)){
    fscanf(arquivo, "%d, %d", &j, &valor);
    vetor[j] = valor;
  }
  fclose(arquivo);
}


/* Nesta leitura, vetor[j] = valor para todo j=0...n */
void le_arq_vetor_denso(char nomearq[], int *vetor)
{
  int j,
    valor;
  FILE *arquivo;

  arquivo = fopen(nomearq,"r");
  if (!arquivo) {
     printf("O Arquivo %s nao pode ser aberto.\n", nomearq);
     getchar();
     exit(1);
  }
  j = 0;
  while (!feof(arquivo)){
    fscanf(arquivo, "%d", &valor);
    vetor[j] = valor;
    j++;
  }
  fclose(arquivo);
}


void limpa_arquivo(char nomearq[])
{
  FILE *arquivo;
  arquivo = fopen(nomearq,"w");
  if (!arquivo){
     printf("O arquivo %s nao pode ser aberto",nomearq);
     getchar();
     exit(1);
  }
  fclose(arquivo);
}



