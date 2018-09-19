/******************************************/
/****************Cabeçalho*****************/
/******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp()
#include "sort.h"
#define MAX 1000000
/******************************************/
/******Declarações de variáveis************/
/******************************************/

//Mensagem de ajuda:
char ajudamsg[]="Mensagem de ajuda:\nsort Algoritmo Cenario Tamanho Arquivo\n\nAlgoritmo:\nBolha, BolhaSentinela, BolhaCoquetel\n\nCenario:\nAleatorio, QOrdenado, OInversamente, Repetidos\n\nTamanho:\nValores positivos inteiros\n\nArquivo:\nNome do arquivo de saida. Opcional.\n\nExemplo:\nsort Bolha Aleatorio 500 Saida.txt\nUsara o algoritmo bolha para ordenar um vetor aleatorio de 500 elementos salvando a saida no arquivo Saida.txt\n";

/******************************************/
/**********Função Principal****************/
/******************************************/
int trocas=0;
int comp=0;
int tamanho;
int main(int argc, char *argv[]){	
	
	int * vetor;//Vetor para testes
	
	
	Fun algoritmo=0;//Ponteiro para a função correspondente ao algoritmo a ser utilizado
	
	//Exibe mensagem de ajuda se o número de argumentos estiver errado
	if(argc < 4 || argc > 5){
		ajuda(1);
		return 0;
	}
	//Encontrar tamanho do vetor:
	sscanf(argv[3],"%d",&tamanho);
	
	if(tamanho >MAX || tamanho <= 1)
		ajuda(2);//Chama ajuda para o erro no tamanho do vetor
	
	
	//Selecionar algoritmo a ser usado:
	algoritmo = SelAlg(argv[1]);
	
	//Preparar cenário:
	vetor = (int*)malloc(tamanho*sizeof(int));	//Aloca o vetor na memória
	if (vetor==0)ajuda(5);					//Emite erro caso a alocação não seja possível
	CriaCenario(argv[2], vetor, tamanho);		//Aloca e preenche o vetor
	
	//Ordena o vetor utilizando o algoritmo selecionado
	algoritmo(vetor,tamanho);
	
	printf("Comp\t%d\tTrocas\t%d\n", comp,trocas);
	return 0;
}

/*****************************************/
/********Algritmos de ordenação***********/
/*****************************************/

void Bolha(int A[], int n){ // Vetor A, tamanho n
	int trocou = 1,i;
	while(trocou){
		trocou = 0;
		for (i=1;i<n;i++){
			/*Trocar se o par não estiver ordenado*/
			comp++;
			if(A[i-1] > A[i]){
				troca(&A[i-1],&A[i]);
				print(A,tamanho);
				trocou = 1;
			}
			
		}
		n--;
	}
}
void BolhaSentinela(int A[], int n){// Vetor A, tamanho n
	int NovoN,i;
	while(n!=0){
		NovoN = 0;
		for (i = 1; i <= n-1; i++){
			comp++;
			if (A[i-1] > A[i]){
				troca(&A[i-1], &A[i]);
				print(A,tamanho);
				NovoN = i;
			}
		}
		n = NovoN;
	}
}
void BolhaCoquetel(int A[], int n){
	int trocou=1,i;
	while(trocou){
		trocou = 0;
		for (i=0;i<=n-2;i++){
			comp++;
			if (A[i] > A[i+1]){ 
				troca(&A[i], &A[i+1]);
				print(A,tamanho);
				trocou = 1;
			}
		}
		if (!trocou){
			break;
		}
		trocou = 0;
		for (i=n-2;i>=0;i--){
			comp++;
			if (A[i] > A[i+1]){
				troca(&A[i],&A[i+1]);
				print(A,tamanho);	
				trocou = 1;
			}
		}
	}
}

/******************************************/
/*********Funções auxiliares***************/
/******************************************/
void troca(int *A,int *B){//Troca o elemento A com B
	int aux;
	aux = *A;
	*A = *B;
	*B = aux;
	trocas++;
}
void ajuda(int erro){//Exibe mensagem de ajuda
	switch (erro){
		case 1:
			printf("Erro na quantidade de argumentos\n");
			break;
		case 2:
			printf("Erro no tamanho do vertor\n");
			break;
		case 3:
			printf("Erro no nome do algoritmo\n");
			break;
		case 4:
			printf("Erro no nome do inicializador\n");
			break;
		case 5:
			printf("Erro na alocacao do vetor\n");
			break;
		
	}
	printf(ajudamsg);
	exit(erro);
}
Fun SelAlg(char c[]){
	if(!strcmp(c,"Bolha"))return Bolha;
	if(!strcmp(c,"BolhaSentinela"))return BolhaSentinela;
	if(!strcmp(c,"BolhaCoquetel"))return BolhaCoquetel;
	//...
	ajuda(3);
	return 0;
}
void CriaCenario(char c[], int *a, int n){
	if(!strcmp(c,"Aleatorio"))init(a, n,  0, 5*n);
	else if(!strcmp(c,"QOrdenado"))init(a, n, 10, 100);
	else if(!strcmp(c,"QInversaO"))init(a, n, -1, 100);
	else if(!strcmp(c,"Repetidos"))init(a, n, 0, n/10);
	else ajuda(4);
}
void init(int * A, int n, int step, int range) {
	int i;
	for (i = 0; i < n; i++) {
		int base = i * step;
		int offset = rand() % range;
		A[i] = base + offset;
	}
}		
void print(int * A, int n){
	int i;
	for(i=0;i<n;i++)
		printf("%d ",A[i]);
	printf("\n");
	
}

