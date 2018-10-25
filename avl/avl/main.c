#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int incluir(no*);
int remover(no*);
void buscar(no);
void crlf();
void profundidade(no);
void log(no,int);

int main(){
	no a=NULL;
	int avlcont=0;

	for(;;){
		printf("1 incluir elemento\n");
		printf("2 remover elemento\n");
		printf("3 buscar elemento\n");
		printf("4 sair do programa\n");
		fflush(stdin);
		switch(getchar()){
			case '1':
				avlcont += incluir(&a);		//Inserir elemento.
			break;
			case '2':
				avlcont -= remover(&a);		//Remover elemento.
			break;
			case '3':
				buscar(a);		//Buscar elemento.
			break;
			case '4':
				exit(1);		//Sair.
			case '5':
				preO(a);		//Mostra arvre em pre ordem
				crlf();
				break;
            case 'p':
                profundidade(a);//mostra a profundidade da arvore
                break;
		}
		log(a,avlcont);
	}
	return 0;
}

void profundidade(no a){
    printf("%d\n",a?a->prof:0);
}


int inteiro(){                      //Apenas lê um inteiro com scanf
	int i;
	scanf("%d",&i);
	return i;
}

int chave(){                        //Interage com o usuário para obter um valor de chave
	printf("Insira uma chave:");
	return inteiro();
}

int valor(){                        //Interage com o usuário para obter um valor de registro.
	printf("Insira um valor:");
	return inteiro();
}

int incluir(no * av){              //Interage com o usuário pedindo uma chave e um valor e insere o resultado na árvore
    return insere(av, chave(),valor());    //Chama a função para inserir os dados.
}

int remover(no * av){              //Interage com o usuário pedindo uma chave de remoção.
    return rem(av,chave());
}

void buscar(no av){                 //Efetua a busca da chave obtida atravéz de interação com o usuário.
	no aux=NULL;
	aux = busca(av,chave());
	if(aux)                         //Informa caso o elemento for encontrado, juntamente com sua profundidade na árvore.
		printf("Valor:\t%d\nNivel:\t%d\n",aux->valor,aux->prof);
	else                            //Emite um aviso caso a chave não esteja presente na árvore.
		printf("Elemento inexistente na arvore.\n");
}

void crlf(){                                //Imprime uma quebra de linha
    printf("\n");

}

void log(no a,int avlcont){
    FILE * p=0;
	while(p==NULL)//Tenta abrir o arquivo até conseguir
		p = fopen ("saida.log","a");
    fprintf(p,"%d %d\n",a?a->prof:0, avlcont);
    fclose(p);
}







