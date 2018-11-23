#include <stdio.h>
#include <stdlib.h>

//Tamanho máximo do vetor de entrada
#define MAX 64

void troca(int *a, int*b){//Função auxiliar da função Bolha
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}
void Bolha(int * A, int n){ // Ordena o vetor A de tamanho n usando o algoritmo bolha
	int trocou = 1,i;
	while(trocou){//Percorre o vetor inteiro enquanto trocas estiverem ocorrendo
		trocou = 0;
		for (i=1;i<n;i++){
			/*Trocar se o par não estiver ordenado*/
			if(A[i-1] > A[i]){
				troca(&A[i-1],&A[i]);
				trocou = 1;
			}
		}
		n--;
	}
}

void PrintSet(int * s){//Imprime o set
	int i;
	if(!s)
        printf("Vazio");//Caso o set esteja vazio, imprime um aviso
	else
	for(i=1;i<=*s;i++)
		printf("%d ",s[i]);
	printf("\n");
}

//Retorna o maior conjunto já encontrado contendo a PA solicitada
int * MaxSet(int vet[], int a, int b, int c){
    static int * Tabela[MAX][MAX],i,j;
    static int init = 0;
	int ra,ultimo,*vetor;
	//Inicializa a Tabela
	if(!init)for(i=0,init=1;i<MAX;i++)for(j=0;j<MAX;j++)Tabela[i][j]=NULL;
    
    //Tabela[razão][indice do menor elemento da PA]
    vetor = &vet[1];
    //Verifica se trinca já foi incluida na tabela
    ra = vetor[b]-vetor[a];

    for(i=0;i<MAX;i++)//Busca na tabela 
        if(Tabela[ra][i]!=NULL){
            ultimo = Tabela[ra][i][0];
            if(Tabela[ra][i][ultimo]==vetor[c]-ra){
                Tabela[ra][i][ultimo+1]=vetor[c];
                Tabela[ra][i][0]=ultimo+1;
                return Tabela[ra][i];//Se o valor é encontrado, retorna
            }
        }
    //caso contrário insere e retorna
    Tabela[ra][a]=(int*)calloc(MAX, sizeof(int));
    Tabela[ra][a][0]=3;
    Tabela[ra][a][1]=vetor[a];
    Tabela[ra][a][2]=vetor[b];
    Tabela[ra][a][3]=vetor[c];
    return Tabela[ra][a];
}

int * MaiorPA(int set[]){
    int i,j,k,n;
    int * max=NULL, *s,*aux;

    if (*set<=2)  return set;

    s = &set[1];    //s é o vetor sem o primeiro elemento que indica seu tamanho
    n = *set;       //n é o tamanho do vetor

    for (j=1; j<n; j++){//Para cada elemento, do segundo até o penúltimo
        i = j-1;
        k = j+1;

        while (i >= 0 && k <= n){//Se ainda houver próximos das pontas para buscar
            if (s[i] + s[k] == 2*s[j]){//Se for uma PA
                aux = MaxSet(set,i--,j,k++);
                if(max)//Guarda o resultado máximo
                    max = *aux>*max?aux:max;
                else
                    max = aux;
            }
            s[i]+s[k]<2*s[j]?k++:i--;//Busca qual elemento das pontas substituir pelo próximo
        }
    }

    return max;
}

int main(int argc, char * args[]){
    int i;
    int v[MAX]={6,22,15,23,82,29,66};//Um dos casos é testado caso não haja argumentos

    if(argc>1){//Captura os argumentos
        for(i=1;i<argc;i++)
            sscanf(args[i],"%d",&v[i]);
        v[0]=argc-1;
    }

    Bolha(&v[1],*v);//Ordena o vetor do set 
	
    PrintSet(MaiorPA(v));//Resolve e imprime a soluçao


    return 0;
}




