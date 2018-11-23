#include <stdio.h>
#include <stdlib.h>

#define MAXHASH 480008831

int len(char * s){//Calcula comprimento de uma string s
    int i=0;
    while(s[i++]);
    return i-1;
}
int tam(int * s,int l){//Calcula o número de particões contidas em s de tamanho l
    int i=0,t=0;
    while(i<l)
        t += s[i++];
    return t-1;
}
int pal(char * s, int l){//Testa se uma string é um palindromo
	//Casos base:
	if(l<=1)return 1;		//Toda string unitária ou vazia é palindromo
	if(l==2 && s[0]==s[1])	//A string de dois elementos iguais também é palindromo
		return 1;
	//recursão:
	if(s[0]==s[l-1])
		return pal(&s[1],l-2);
	else return 0;
}

int hash(char *s, int l){//Algoritmo de hash
	int i=0,ret=0;
	while(l--)
		ret = (11*ret%MAXHASH + s[i++]) % MAXHASH;
	return ret>0?ret:-ret ;
}

//Retorna tabela de particionamento 
int * fun(char *s, int l){
	int * p = (int*)calloc(sizeof(int),l);	//Reserva e limpa um pedaço da memória
	static int * H[MAXHASH];				//Reserva espaço para guardar resultados

	int atual,*menord=NULL,*menore=NULL,*auxe,*auxd;
	int i,min=l,j,k,tamenore,tamenord,tame,tamd;

	if(pal(s,l)){//Verifica se o caso é a solução base
        p[l-1]=1;
        return p;//Se já for palindromo
	}

	//Caso não seja um palindromo, é necessário verificar para cada partição possível
	if(H[hash(s,l)]){//Se o resultado já foi encontrado antes,
		return H[hash(s,l)];
	}
	
	for(i=1;i<l;i++){//O laço divide a string em duas de todas as formas possíveis
		auxd = fun(&s[i],l-i);
		auxe = fun(s,i);
		//Faz chamadas recursivas para cada quebra
        tame = tam(auxe,i);
        tamd = tam(auxd,l-i);

		atual = tame+tamd;//Conta o número de quebras de s para o caso atual


		if(min>atual){
            k=i;//Guarda posição da partição que resulta no menor número de partições
			min = atual;
			menord = auxd;
			menore = auxe;
			tamenore = i;
            tamenord = l-i;
		}
	}
	
	//Nessa parte as tabelas menores da esquerda e da direita são concatenadas
	for(j=0,i=0;j<tamenore;j++){
		p[i++]=menore[j];
	}
	for(j=0;j<tamenord;j++){
        p[i++]=menord[j];
	}

	H[hash(s,l)] = p;//Guarda o resultado para que possa ser usado em outras instâncias

	return p;
}

int main(int argc, char *args[]){
    char a[512]="aaaabbbbabaabbbababaaababbbbaaaaabbbaaabbbbbaaabbbbaababbabbaaaabbbbabaabbbababaaababbbbaaaaabbbaaabbbbbaaabbbbaababbabb";//bbbbaababbabb
    char * s;
	int * ret;
	int i=0;

    if(argc==1){
        argc = 2;
        args[1]= a;
    }

    s = args[1];

	ret = fun(s,len(s));

    i=0;
    while(i<len(s)){
         printf("%c",s[i]);
         if(ret[i++]){
            printf(" ");
         }

    }
   
    return 0;
}




