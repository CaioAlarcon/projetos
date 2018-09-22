#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){//O proposito desse programa é criar um script que efetue todos os testes necessários
	int i,j,k,l;
	const char * algs[8] = {"Bolha","BolhaSe","BolhaCo","Insercao","Selecao","Intercala","heapSort","quickSort"};
	const char * cena[4] = {"Aleatorio","QOrdenado","QInversaO","Repetidos"};
	FILE * p=0;
		while(p==NULL)
			p = fopen ("testatudo.sh","w");
	
	for(i=0;i<4;i++)
		for(j=0;j<8;j++)
			for(k=2;k<=6;k++)
				for(l=0;l<5;l++)
					fprintf(p,"./sort %s %s %d saida.txt %u &\ndisown\n",algs[j],cena[i],(int)pow(10,k),(unsigned int)rand());
	fclose (p);
}

