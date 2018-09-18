/******************************************/
/****************Cabeçalho*****************/
/******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp()
/******************************************/
/******Declarações de variáveis************/
/******************************************/

//Mensagem de ajuda:
char ajuda[]="mensagem de ajuda\nalgoritmo cenario k nome do arquivo\n";
int vetor[1000000];//Vetor para testes

/******************************************/
/**********Função Principal****************/
/******************************************/

int main(int argc, char *argv[])  {
//Exibe a mensagem de ajuda caso o número de argumentos esteja errado:
	if(argc != 5){
		printf(ajuda);
		return 0;
	}


	printf("%s %s %s %s \n", argv[1],  argv[2],  argv[3],  argv[4]);
	return 0;
}

/*****************************************/
/***Criação das condições iniciais********/
/*****************************************/

void init(int a[], int n, int step, int range) {
	int i;
	for (i = 0; i < n; i++) {
		int base = i * step;
		int offset = rand() % range;
		a[i] = base + offset;
	}
}		


/*****************************************/
/********Algritmos de ordenação***********/
/*****************************************/
	

