#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int nat;//Numero natural

int strnum(char * str){//Converte uma string que contem um número em um número inteiro
	int ret;
	sscanf(str,"%d", &ret);
	return ret;
}

int init(nat cache[][100]){//Função auxiliar, inicializa o cache da função bin
	int i,j;
	for(i=0;i<100;i++)
		for(j=0;j<100;j++)
			cache[i][j]=(j==0 || j==i)?1:0;
	return 1;
}

nat bin(int n, int k){//Calcula o coeficiente binomial utilizando programação dinâmica
	static nat cache[100][100],ini=0;	//Declaração do cache e da variavel de controle ini
	ini = ini?1:init(cache);			//inicializa o cache apenas uma vez
	if(cache[n][k])					//Se o resultado estiver em cache, retorna de imediato
		return cache[n][k];
	//Caso contrário, efetua chamada recursiva, guarda em cache e retorna.
	cache[n][k]= bin(n-1, k-1) + bin(n-1, k);
	return  cache[n][k];
}

//Função que bisca o número de possibilidades para n dados de s lados que somam p quando jogados
nat soma(int n, int s, int p){
	int Kmax, k;
	nat ret=0;
	//Trata os casos base
	{	if(n==0)
			return 0;
		if (s*n <= p) 
			return (s*n == p); 
		if (n >= p) 
			return (n == p); 
	}
	Kmax = (p-n)/s;
	//Aplica o conceito matemático encontrado em http://mathworld.wolfram.com/Dice.html
	for(k=0;k<=Kmax;k++)
		ret+= bin(n,k)*bin(p-s*k-1,n-1)*(k%2?-1:1);
	return ret;
}


int main(int argc, char * args[]){
	int m,n,x;
	//Captura os argumentos:
	n=strnum(args[1]);
	m=strnum(args[2]);
	x=strnum(args[3]);
	
	//Resolve e imprime a solução:
	printf("Ha %llu modos de se obter %d lancando %d dados com %d lados\n", soma(n,m,x),x,n,m);

    return 0;
}



