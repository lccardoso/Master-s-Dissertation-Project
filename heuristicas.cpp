#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "Util.h"
#include "Construcao.h"


//Implementacao VND
float vnd(int m, int n, int **A, int *d, int *c, int *z, int *y, int alpha, float demand, int itermax){
	
	int i, j, iter, aux, fo, fo_viz;
		
	vetor_cobertura(m,n,A,y,z); //Atualização do vetor de cobertura com nova solução (sol. corrente)
	fo=calcula_fo(m,n,demand,alpha,d,c,z,y);
	
	int folinha, fomelhor;
	
	//printf("Solucao Inicial - VND: %d\n", fo);
	iter=0;
	
	int demanda_atendida; //demanda atendida pela solução
	int *v1;
	int *v2;
	int t;
	int h;
	int totalf; //total de facilidades
	int numf; //numero de facilidades
	int estr_viz; //tipo de estrutura
	int ninst; //Número de instalçoes ativadas
	int ncli; //Número de clientes cobertos
	
	int *zlinha;
	int *ylinha;
	int *zmelhor;
	int *ymelhor;
	
	zlinha = cria_vetor(m);
	ylinha = cria_vetor(n);
	
	zmelhor = cria_vetor(m);
	ymelhor = cria_vetor(n);
	bool melhorou;
	
	//Inicio descida completa
	
	do{
		melhorou = false;
		fomelhor = fo;
		
	for (int j=0; j<n;j++){
		folinha=fo;
		atribuirvetor(zlinha, z, m); 
		atribuirvetor(ylinha, y, n); 
		
		//gerar vizinho - trocar o bit de acordo com o vetor selecionado e a pocição
		trocabit(j, ylinha);
		
		refaz_vetor_cobertura(j, m, n, A, ylinha, zlinha);
		folinha=calcula_fo(m, n, demand, alpha, d, c, zlinha, ylinha);	
		
		if (folinha<fomelhor){
			fomelhor=folinha;
			atribuirvetor(zmelhor, zlinha, m); //z=zlinha
			atribuirvetor(ymelhor, ylinha, n); //y=ylinha
			printf("Sol. melhorada VND - estrutura 1: %d\n", fo);
		}
	}
	//se o melhor vizinho melhorar a solução corrente
	if (fomelhor<fo){
			//system("PAUSE");
			printf("\n SOL. MELHORADA PELO VND - ESTR. DE VIZ. 1 (INSTALAR/DESINSTALAR): %d\n", fomelhor);
			fo=fomelhor;
			atribuirvetor(z, zmelhor, m); //z=zlinha
			atribuirvetor(y, ymelhor, n); //y=ylinha
			melhorou = true;
		
		} else{
			//vetor_cobertura(m, n, A, B, C, x, z, k, y); //retornar o vetor cobertura
			melhorou = false;
		}
}while (melhorou == true);

	//Contar numero de facilidades da solucao otima corrente
	numf=0;
	for (int i=0; i<n;i++){
		numf=numf+y[i];
	}
	
	v1 = cria_vetor(numf);
		t=0;
	
	for (int i=0;i<n;i++){
		if (y[i]==1){
			v1[t]=i;
			t++;
		}
	}
						
	v2 = cria_vetor(n-numf);
	t=0;
	for (int i=0;i<n;i++){
		if (y[i]==0){
			v2[t]=i;
			t++;
		}
	}
	
	do{
		
	int i = 0;
	while (i<numf){
		
		melhorou = false;

		j=0;
		while (j<(n-numf)){
			
			folinha=fo;
			atribuirvetor(zlinha, z, m); 
			atribuirvetor(ylinha, y, n); 

			trocabit(v1[i], ylinha);
			refaz_vetor_cobertura(v1[i], m, n, A, ylinha, zlinha);
			
			trocabit(v2[j], ylinha);
			refaz_vetor_cobertura(v2[j], m, n, A, ylinha, zlinha);
	
			folinha=calcula_fo(m, n, demand, alpha, d, c, zlinha, ylinha);
			
				//se o melhor vizinho melhorar a solução corrente
			if (folinha<fo){
				printf("\n SOL. MELHORADA PELO VND - ESTR. DE VIZ. 2 (TROCAR POSICOES): %d\n", folinha);
				fo=folinha;
				atribuirvetor(z, zlinha, m); //z=zlinha
				atribuirvetor(y, ylinha, n); //y=ylinha
				//vetor_cobertura(m,n,A,y,z); //atualiza vetor cobertura com nova solucao
				melhorou = true;
				aux=v1[i];
				v1[i]=v2[j];
				v2[j]=aux;
				//i=0;
				j=0;
		
			}else{
				j=j+1;
			}
	}
	
	i=i+1;
		
	}
		
	melhorou = false;
		
}while (melhorou == true);			
	libera_vetor(v1);
	libera_vetor(v2);
	return fo;		
	}
	
//Implentação do ILS
float ils(int m, int n, int **A, int *z, int *y, int *d, int *c, int alpha, int itermax, int vezesnivel,  float demand, float ilsmaxpercent){
	
	//Busca Local na solução inicial
	//Estratégia do ILS2 - o movimento utilizado para perturbar a solução atual consiste em, dada uma solução corrente com k facilidades instaladas, remover algumas facilidades e aplicar o VND
	int fo;
	int folinha;
	int nivel; //nível de perturbação
	int *v; //vetor de índices
	int *aux; //vetor de indices para identificar x, z e k
	
	int *zlinha;
	int *ylinha;
	int j;
	int ilsmax;
	int numf;
	int t;
	
	zlinha = cria_vetor(m);
	ylinha = cria_vetor(n);
	
	int *v1;
	int *v2;
	
	vetor_cobertura(m,n,A,y,z); //atualiza vetor cobertura com nova solucao	
	
	fo=vnd(m, n,A, d, c, z, y, alpha, demand, itermax);
	
	numf=0;
	
	for (int i=0; i<n;i++){
		numf=numf+y[i];
	}
	
	v1 = cria_vetor(numf);
		t=0;
			
	for (int i=0;i<n;i++){
		if (y[i]==1){
			v1[t]=i;
			t++;
		}
	}
			
				
	v2 = cria_vetor(n-numf);
	t=0;
	for (int i=0;i<n;i++){
		if (y[i]==0){
			v2[t]=i;
			t++;
		}
	}		
	
	ilsmax=numf*ilsmaxpercent;
	//printf("\nILS max: %d\n", ilsmax);
	
	nivel =1;
	while (nivel<=ilsmax)
	{
		

		atribuirvetor(ylinha, y, n); 
		
		int vezes = 0;
		
		while (vezes<vezesnivel){
		
		printf("\n*******************************************************");
		printf("\nNIVEL PERTURBACAO: %d - VEZES: %d \n",nivel, vezes+1);
		printf("\nRETIRA %d FACILIDADES NA SOL. CORRENTE E APLICA VND",nivel+1);
		printf("\n*******************************************************\n");
		
		v=cria_vetor(nivel+1);
		aux=cria_vetor(nivel+1);
		bool rep = false;
		
		//srand((unsigned) time(NULL)); // pega a hora do relogio como semente
		for (int i=0; i<=nivel; i++)
		{
			j=rand()%(numf);
			rep=repeteindice(v1, j, numf+1);
			while (rep==true){
				j=rand()%(numf);
				rep=repeteindice(v1, j, numf+1);
			}
			v[i]=v1[j];
		}
		
		for (int j=0; j<=nivel;j++){
			trocabit(v[j], ylinha);
		}

		vetor_cobertura(m,n,A,ylinha,zlinha);
		folinha = vnd(m, n,A, d, c, zlinha, ylinha, alpha, demand, itermax);
		
	
		if (folinha<fo){
			printf("\n SOLUCAO MELHORADA PELO ILS NA PERTURBACAO: %d\n", nivel);
			fo=folinha;
			atribuirvetor(z, zlinha, m); //z=zlinha
			atribuirvetor(y, ylinha, n); //y=ylinha
			nivel = 1;
			vezes=0;
			
			libera_vetor(v1);
			libera_vetor(v2);
			
			numf=0;
	
			
	
			for (int i=0; i<n;i++){
				numf=numf+y[i];
			}
	
			v1 = cria_vetor(numf);
			t=0;
			
			for (int i=0;i<n;i++){
				if (y[i]==1){
					v1[t]=i;
					t++;
				}
			}
			
				
			v2 = cria_vetor(n-numf);
			t=0;
			for (int i=0;i<n;i++){
				if (y[i]==0){
					v2[t]=i;
					t++;
				}
			}		
	
	
			ilsmax=numf*ilsmaxpercent;
			//printf("\nILS max: %d\n", ilsmax);
			

		} 
		vezes++;
		
	}
			nivel++;
	
		libera_vetor(v);
		libera_vetor(aux);

	}
	
		libera_vetor(zlinha);
		libera_vetor(ylinha);
	
	return fo;
}			



