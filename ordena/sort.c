/******************************************/
/**Caio Alarcon n° 7241109*****************/
/******************************************/
#include <stdio.h>	//printf sscanf scanf fprintf 
#include <stdlib.h>	//malloc sizeof rand srand 
#include <time.h>	//time
#include <string.h> //strcmp
#include "sort.h"
#define MAX 1000000

/**************Cabeçalho da depuração************************************/
/*Para ativar a depuração basta descomentar a linha abaixo e tornar global
a variável tamanho e o ponteiro vetor que está dentro da main. 
Isso fará com que o vetor seja impresso a cada alteração.
*/

#define debug //print(vetor,tamanho);
//int tamanho;
//int * vetor;

/******************************************/
/******Declarações de variáveis************/
/******************************************/
long long int atrib=0;//Número de atribuições 
long long int comp=0;//Número de comparações

/******************************************/
/**********Função Principal****************/
/******************************************/
int main(int argc, char *argv[]){
	//Comentar tamanho e vetor para ativar depuração, ver cabeçalho
	int tamanho;
	int * vetor;//Vetor para testes
	Fun algoritmo=0;//Ponteiro para a função correspondente ao algoritmo a ser utilizado
	
	//Exibe mensagem de ajuda se o número de argumentos estiver errado
	if(argc < 4 || argc > 6){
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
	CriaCenario(argv[2], vetor, tamanho,argc==6?argv[5]:NULL);		//Aloca e preenche o vetor
	
	//Ordena o vetor utilizando o algoritmo selecionado
	algoritmo(vetor,tamanho);
	
	printf("Algoritmo: %s\tk: %d\tCenario: %s\tComp: %lld\t Atrib: %lld\n",
						argv[1],tamanho,	 argv[2],  comp, 		  atrib);
	if(argc>=5)
		salvar(argv[1],argv[4],tamanho,argv[2]);
	return 0;
}

/*****************************************/
/********Algritmos de ordenação***********/
/*****************************************/
void Bolha(int A[], int n){ // Vetor A, tamanho n
	int trocou = 1,i;
	while(trocou){//Percorre o vetor inteiro enquanto trocas estiverem ocorrendo
		trocou = 0;
		for (i=1;i<n;i++){
			/*Trocar se o par não estiver ordenado*/
			comp++;
			if(A[i-1] > A[i]){
				troca(&A[i-1],&A[i]);
				trocou = 1;
			}
			
		}
		n--;
	}
}
void BolhaSentinela(int A[], int n){// Vetor A, tamanho n
	int NovoN,i;
	while(n!=0){//Percorre enquanto houver vetor 
		NovoN = 0;
		for (i = 1; i <= n-1; i++){//Percorre o vetor inteiro efetuando as trocas necessarias
			comp++;
			if (A[i-1] > A[i]){
				troca(&A[i-1], &A[i]);
				NovoN = i;
			}
		}
		n = NovoN;//Reduz o vetor excluindo a parte já ordenada
	}
}
void BolhaCoquetel(int A[], int n){
	int trocou=1,i;
	while(trocou){//Percorre o vetor inteiro enquanto trocas estiverem ocorrendo
		trocou = 0;
		for (i=0;i<=n-2;i++){//Percorre o vetor inteiro no sentido ascendente efetuando as trocas necessárias
			comp++;
			if (A[i] > A[i+1]){ 
				troca(&A[i], &A[i+1]);
				trocou = 1;
			}
		}
		if (!trocou){
			break;
		}
		trocou = 0;
		for (i=n-2;i>=0;i--){//Percorre o vetor no sentido descendente efetuando as trocas necessárias
			comp++;
			if (A[i] > A[i+1]){
				troca(&A[i],&A[i+1]);
				trocou = 1;
			}
		}
	}
}
void Insercao(int A[], int n){//Algoritmo de inserção
	for (int i=0; i<n; i++) {
		int aux=A[i];
		int j=i;
		while (aux<A[j-1] && j>0){//percorre o vetor enquanto houver trocas a fazer
			troca(&A[j], &A[j-1]);
			j--;
			comp++;
		}
	}
}
void Selecao(int A[], int n){//Algoritmo de seleção
	int i, j, imin;
	for (i=0; i<n-1; i++){//percorre o vetor todo, cada vez uma pocição a menos
		imin = i;
		for (j = i+1; j < n; j++,comp++)//
			if (A[j] < A[imin])
				imin = j;
		troca(&A[imin], &A[i]);
	}
}
void Mescla(int A[], int l, int m, int r){ //Função auxiliar do MergeSort
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 =  r - m; 

	/*Vetores temporarios*/
	int L[n1], R[n2]; 

	/*Copia para L[] e R[] */
	for (i=0; i<n1; i++,atrib++) 
		L[i] = A[l+i]; 
	for (j=0; j<n2; j++,atrib++) 
		R[j] = A[m+1+j]; 

	/*Intercala vetores temporarios em A[l..r]*/
	i = 0;  
	j = 0; 
	k = l; 
	while (i < n1 && j < n2){
		if (L[i] <= R[j]){
			A[k] = L[i++];
			atrib++;
			comp++;
		}			
		else{
			A[k] = R[j++]; 
			atrib++;
		}
		k++;
	}
	while (i < n1){
		A[k++] = L[i++];
		atrib++;
	}		
	while (j < n2){
		A[k++] = R[j++];
		atrib++;
	}
}
void mergeSort(int A[], int l, int r){ //Algoritmo MergeSort
	if (l < r){
		int m = l+(r-l)/2; 
		mergeSort(A, l, m); 
		mergeSort(A, m+1, r); 
		Mescla(A, l, m, r); 
	} 
}
void Intercala(int A[], int n){//Adapta a chamada para o padrão
	mergeSort(A, 0, n-1); 
}
void heapify(int A[], int n, int i){//Função auxiliar do heapsort
	int maior = i;
	int l = 2*i + 1;
	int r = 2*i + 2;
	comp++;
	if (l<n && A[l]>A[maior])//Se o filho da esquerda for maior que a raiz
		maior = l;
	comp++;
	if (r<n && A[r]>A[maior])//Se o filho da direita for maior que a raiz
		maior = r;
	if (maior != i){//Se o maior não for a raiz
		troca(&A[i], &A[maior]);
		heapify(A, n, maior);//Cria o heap recursivamente
	}
}
void heapSort(int A[], int n){//Função HeapSort
	for (int i=n/2-1; i>=0; i--)//Cria o heap rearanjando o vetor
		heapify(A, n, i);
	
	for (int i=n-1; i>=0; i--){//Extrai um por um dos elementos do heap
		troca(&A[0], &A[i]);//Move para o fim a raiz atual 
		heapify(A, i, 0);//cria o heap no heap reduzido
	}
}
int partition (int A[], int m, int M){//Função auxiliar do quick
	//m = menor M = MAIOR
	int pivo = A[M]; //Pivo
	int i = (m - 1); //Indice do menor elemento

	for (int j=m; j <= M-1; j++,comp++){
		if (A[j] <= pivo){
			troca(&A[++i], &A[j]); //troca se o elemento atual for menor ou igual o pivo
		} 
	} 
	troca(&A[i+1], &A[M]); 
	return (i+1); 
} 
void quick(int A[], int m, int M){//Quicksort
	if (m < M){
		int pi = partition(A, m, M); //pi é o índice de particionamento
		quick(A, m, pi-1); //Separadamente ordena as partições
		quick(A, pi+1, M); 
	} 
} 
void quickSort(int A[], int N){//Adaptação do formato da função
	quick(A,0,N-1);//Faz a chamada da função
}

/******************************************/
/*********Funções auxiliares***************/
/******************************************/
void troca(int *A,int *B){//Troca o elemento A com B
	int aux;
	aux = *A;
	*A = *B;
	*B = aux;
	atrib +=2;//Cada troca são duas atribuições
	debug //função para depuração, ver cabeçalho
}
void ajuda(int erro){//Exibe mensagem de ajuda e sai
	//Mensagem de ajuda:
	char ajudamsg[]="~~~~~~~~Mensagem de ajuda~~~~~~~~\nDescricao dos parametros:\nsort Algoritmo Cenario Tamanho Arquivo seed\n\nAlgoritmo:\nBolha, BolhaSe, BolhaCo, Insercao, Selecao, Intercala, heapSort, quickSort\n\nCenario:\nAleatorio, QOrdenado, QInversaO, Repetidos\n\nTamanho:\nValor positivo inteiro referente ao tamanho do vetor a ser ordenado\n\nArquivo(opcional):\nNome do arquivo de saida.\n\nSeed(opcional):\nValor tipo unsigned int a ser usado para configurar o algoritmo pseudo aleatorio \n\nExemplo:\nsort Bolha Aleatorio 500 Saida.txt 4564654\nUsara o algoritmo bolha para ordenar um vetor aleatorio de 500 elementos gerado com o seed 4564654 salvando a saida no arquivo Saida.txt";

	switch (erro){//Emite o erro de acordo com o que for especificado
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
Fun SelAlg(char c[]){//Selecionar algoritmo 
	//Retorna ponteiro pra função de acordo com o que for especificado no parametro fornecido pelo usuario
	if(!strcmp(c,"Bolha"))return Bolha;
	if(!strcmp(c,"BolhaSe"))return BolhaSentinela;
	if(!strcmp(c,"BolhaCo"))return BolhaCoquetel;
	if(!strcmp(c,"Insercao"))return Insercao;
	if(!strcmp(c,"Selecao"))return Selecao;
	if(!strcmp(c,"Intercala"))return Intercala;
	if(!strcmp(c,"heapSort"))return heapSort;
	if(!strcmp(c,"quickSort"))return quickSort;
	ajuda(3);//Emite mensagem de erro caso o parâmetro não seja reconhecido
	return 0;
}
void CriaCenario(char c[], int *a, int n,char seed[]){//Função personalizada de criar o cenario de acordo com o que foi instruído na descrição do trabalho
	unsigned int aux;
	if(seed==NULL)//Caso o seed venha vazio
		srand(time(NULL));//Usar o tempo como seed
	else{//Caso haja seed
		sscanf(seed,"%u",&aux);//Ler da string 
		srand(aux);//Usar seed específico
	}
	//Aplicar função de acordo com o que foi especificado
	if(!strcmp(c,"Aleatorio"))init(a, n,  0, 5*n);
	else if(!strcmp(c,"QOrdenado"))init(a, n, 10, 100);
	else if(!strcmp(c,"QInversaO"))init(a, n, -1, 100);
	else if(!strcmp(c,"Repetidos"))init(a, n, 0, n/10);
	else ajuda(4);//Emitir mensagem de erro caso o argumento não seja reconhecido
}
void init(int * A, int n, int step, int range) {//Função inicializadora do vetor
	int i;
	for (i = 0; i < n; i++) {
		int base = i * step;
		int offset = rand() % range;
		A[i] = base + offset;
	}
	debug //função para depuração, ver cabeçalho
}		
void print(int * A, int n){//Função auxiliar para imprimir o vetor
	int i;
	for(i=0;i<n;i++)//Para cada elemento do vetor
		printf("%d ",A[i]);//Imprimir o elemento 
	printf("\n");//Quebra de linha ao terminar
}
void salvar (char alg[], char arquivo[],int tamanho,char cenario[]){//Função para salvar no arquivo o resultado da execução do processo
	FILE * p=0;
	while(p==NULL)//Tenta abrir o arquivo até conseguir
		p = fopen (arquivo,"a");
		//Imprime no arquivo no formato especificado
	fprintf(p,"Algoritmo: %s\tk: %d\tCenario: %s\tComp: %lld\t Atrib: %lld\n",
							  alg,   tamanho,	  cenario,  comp, 		  atrib);
	fclose (p);//Fecha arquivo
}

