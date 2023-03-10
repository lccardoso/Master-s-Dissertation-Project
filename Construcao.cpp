#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include "Util.h"
#include "Construcao.h"

/*Solução Inicial para o problema - Randômica*/
void constroi_solucao(int n, int *y){
 	srand((unsigned) time(NULL)); // pega a hora do relogio como semente
 	for (int j=0; j<n; j++){
 		y[j]= rand() % (2);
	 }
}

//----------------------------------------------------------------------------------------// 
//Construcao Gulosa - Leonardo Cardoso
void construcao_gulosa(int m, int n, int *c,int *c_aux, int *Ind, int *y, int *z,int *d, int **A, float demand) // ordenar os maiores fluxos e seus indices
{
	  
    int aux = 0;
    int aux2 = 0;
    int cont =0;
    int dem = 0;
	int iterMax = 0;
	int cont2 = 0;
	int somaC=0;
	int somaF=0;
	int demanda = 0;
	double demand1 = 0;
	int FO = 0;
	
	//Ordena? dos vetores de custo de abertura das facilidades em ordem crescente 
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (c[j] < c[i]) {
                aux = c[j];
                aux2 = Ind[j];
                c[j] = c[i];                // Ordena os custos e os indices
                Ind[j] = Ind[i];
                c[i] = aux;
                Ind[i] = aux2;
            }
        }
        
        printf("  O custo de abertura da instalacao  %d  e  %d  \n", Ind[i] , c[i]  );

    }
    
	//Implementa? do Vetor de abertuta de facilidades (0-1) 
	for(int i=0; i < n; i++){	
		y[i]=0;
	    //printf(" %d", y[i]);		
	}
	
	//Calculo da demanda total a ser atendida
	for(int j=0; j<m; j++){
		demanda = demanda+d[j];
	}
	printf("  O valor da demanda total  e %d \n", demanda);

	//Calculo d do percentual da  demanda a atendida
	demand = (demanda) *0.5;
	printf("  O Valor de demanda minimo a ser atendida e %f \n", demand);
	
   while(demand >= dem){
  
    //----------------------------------------------------------------------------------------// 
		int aux3=0;	
		//Ativa? das facilidades
		aux3 = Ind[cont];
		for(int i=0; i<n; i++){			
			if(aux3==i)
				y[i]=1;
			//printf(" %d ", y[i]);
		}
    
    	//Declara? vari?l de Fun? Objetivo
	
    	
    	//Calculo de vetor de Cobertura
    	int soma;
		for (int i=0; i<m;i++){
			soma=0;
			z[i]=0; //inicialmente, o v?ice i n??oberto
				for (int j=0; j<n;j++){
					soma=soma+A[i][j]*y[j];
				}
			if (soma>0) z[i]=1; //Caso o n??seja coberto por alguma facilidade, y[i] ser?rocado para 1
			//printf(" %d", z[i]);
		}
		
		//Calculo de demanda atendida
		for(int j=0; j<m;j++){
			dem = dem+d[j]*z[j];
		}	
		
	cont2 ++;
	cont ++;	
	iterMax ++;
	printf(" O Valor da demanda atendida e  %d \n", dem);
	//system("PAUSE");
	
	}
	
	for(int i=0; i<n; i++){			
			if(y[i]==1)somaF=somaF+1;
			//printf(" %d ", y[i]);
			//Calculo FO Inicial
			if(y[i]!=0){
				FO = FO+c_aux[i];
			}
	}
	
	for(int i=0; i<m; i++){			
			if(z[i]==1)somaC=somaC+1;
	}

	
	printf(" O Valor da demanda atendida e  %d \n", dem);
	printf("\n");
	printf("FO da Solucao Inicial Gulosa e %d \n", FO);
	printf(" Facilidades Abertas   %d \n", somaF);
	printf(" Clientes Atendidos  %d \n", somaC);
	
	//system("PAUSE");
   
}


/*Calculo da demanda corrente para o problema*/
float calcula_demanda(int m, int *d, float porcentagem_d){
	float demand=0;
	for(int i=0; i<m; i++){
		demand = demand+d[i];
	}
	return porcentagem_d*demand;
}

/*Cálculo de vetor de cobertura*/
void vetor_cobertura(int m, int n, int **A, int *y, int *z){	
	int soma =0;
	int j;
	
	for(int i=0; i<m ;i++){
		//Inicialmente todas os vertices não são cobertos
		z[i]=0;
		for(int j=0; j<n; j++){
			soma =+ A[i][j]*y[j];
		}
	if(soma>0) z[i]=1;	
	}
}

/*Calculo da função objetivo*/
float calcula_fo(int m, int n, float demand, int alpha, int *d, int *c, int *z, int *y){
	float demand_y=0;
	float f=0;
	
	for (int j=0; j<n;j++){
		f=f+c[j]*y[j];
	}
	for (int i=0; i<m;i++){
		demand_y=demand_y+d[i]*z[i];
	}
	if (demand_y<demand){
		f=f+alpha*(demand-demand_y);
	}	
	return f;
}

//Função auxliar
bool repeteindice(int *v, int valor, int n)
	{
		int rep = 0;
		
		for (int i=0; i<n; i++){
			if (v[i]==valor) rep++;
		}
		
		if (rep > 1){
			return true;
		}else{
			return false;
		}
		
	}

//Função auxliar	
void atribuirvetor(int *v1, int *v2, int n){
	for (int i=0; i<n;i++){
		v1[i]=v2[i];
	}
}

//Função auxliar
void trocabit(int j, int *y)
{
	
	if (y[j]==0){
		y[j]=1;
	}else{
		y[j]=0;
	}
	
}

//Função auxiliar
void refaz_vetor_cobertura(int pos, int m, int n, int **A, int *y, int *z)
{
	int coberto = 0;
	int j;
	
	if (y[pos]==0)
	{
		//vetor_cobertura(m, n, A, y, z);
			
	int coberto;
	for (int i=0; i<m;i++){
		//if (z[i]==1) {
		if (A[i][pos]==1){
			
		coberto = 0;
		j=0;
		while((coberto==0) && (j<n)){
		
		z[i]=0;
		
			if (A[i][j]*y[j]==1){
				coberto = 1;
				z[i]=1;
			}else{
				j=j+1;
			}
		}	

		}
		
	}
				
	}
	
	if (y[pos]==1)
	{
		for (int i=0; i<m;i++){
			if (A[i][pos]==1){
				z[i]=1;
			}
			
		}
		
	}
	

}

//Função auxiliar
int calcula_facilidades(int n, int *y){
	int soma=0;
	
	for (int i=0; i<n; i++){
		soma=soma+y[i];
	}
	return soma;
}

//Função auxiliar
int calcula_clientes(int m, int *z){
	int soma=0;
	
	for (int i=0; i<m; i++){
		soma=soma+z[i];
	}
	return soma;
}

//Implementação de uma construção com uma lista de instalações candidatas
int *construcao_parcial_gulosa(int n, int m, float demand, float porcentagem_d, int *c, int *d, int *z, int *Ind, int *y, int **A){
	
	
	int *cus_inst; // Vetor com o custo de abertura da instalação  "i"
	int *total_cob; // Vetor com o total de instalações cobertas pela instalaçao "i"
	int demanda_fac; //Soma das demandas atendidas pela facilidade corrente "i"
	float *demanda_custo; // Indice de atendimento(RELACAO CUSTO COBERTURA) ** Ind = Demanda / custo de abertura da instalação "i"
	float *maior;
	int *ind_maior;
	int *y_linha;
	int dem_atual;
	int maior_ind;
	int fo;
	int aux1=0;
	int aux2=0; 
	int cont=0;
		
	cus_inst = cria_vetor(n);
	total_cob = cria_vetor(m);
	maior = cria_vetor_float(n);
	ind_maior = cria_vetor(n);
	demanda_custo = cria_vetor_float(n);
	y_linha = cria_vetor(n);
	
	//Demanda atual do problema
	printf("Demanda atual do problema a ser atendida e %.5f\n ",  demand);
		
	for(int i=0; i<n; i++){
		cus_inst[i] = c[i];// recebe os custo de abertura das instalações 
		for(int j=0; j<m; j++){
			if(A[i][j] == 1 ) demanda_fac += d[j]; 		
		}
		
		demanda_custo[i] = demanda_fac/cus_inst[i];
		
		//maior[i]=demanda_custo;
	/*	
		printf("Demanda atendida pela instalacao  %d e %d\n",i, demanda_fac);
		printf("Custo da instalacao %d\n" , c[i]);
		demanda_fac = 0;
		printf("Relacao - Custo de Cobertura %f\n",demanda_custo[i]);
		printf("\n");
		system("PAUSE");
	*/	
	}
	
	//Criar lista ordenada Relacao Custo Cobertura
	for(int i=0; i<n; i++){
		for(int j = i+1; j<n; j++){
			if(demanda_custo[j]>demanda_custo[i]){
			aux1 = demanda_custo[j];
			aux2 = Ind[j];	
			demanda_custo[j] = demanda_custo[i];
			Ind[j] = Ind[i];
			demanda_custo[i] = aux1;	
			Ind[i] = aux2;
			}
		}
	 //printf("  A Relacao do custo/demanda de abertura da instalacao  %d  e  %f  \n", Ind[i] , demanda_custo[i] );	
	}
	
	while (dem_atual<demand){
	
	//Calculo da função objetivo
		int aux3=0;	
		//Ativacao das facilidades 
		aux3 = Ind[cont];
		
		for(int i=0; i<n; i++){	
			if(aux3==i)
				y[i]=1;
			printf(" %d ", y[i]);
			//system("PAUSE");
		}
		printf("\n");
	//Calculo do  vetor de cobertura
	int soma;
		for (int i=0; i<m;i++){
			soma=0;
			z[i]=0; //inicialmente, o v?ice i n??oberto
				for (int j=0; j<n;j++){
					soma+=A[i][j]*y[j];
				}
			if (soma>0) z[i]=1;
			//printf(" %d", z[i]);
		}
	
	//Calculo do demanda atendida
	for(int j=0; j<m;j++){
			dem_atual += d[j]*z[j];	
	}
	printf("Demanda atendida atual %d\n", dem_atual);
	printf("\n");
	
	cont++;
	}
	
	
	
	for(int i=0; i<n; i++){
		y_linha[i]=y[i];
	}
	
	return y_linha;
}






