#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


no novoN(int ch, int val){				    //Retorna endereço do nó recem criado.
	no N = (no)	malloc(sizeof(struct N));   //Aloca na memória o espaço necessário para um nó.
	N->ch = ch;                             //Registra a chave
	N->valor = val;                         //Registra o valor
	N->es = NULL;                           //Indica que não tem filho esquerdo
	N->di = NULL;                           //Indica que não tem filho direito
	N->prof = 1;                            //Profundidade padrão
	return(N);                              //Retorna a referencia para o nó recém criado
}

int prof(no N){							    //Retorna a profundidade da árvore.
	if(N)
		return N->prof;                     //Busca no nó sua profundidade.
    return 0;                               //Retorna 0 caso não exista nó.
}

int fatorB(no N){						    //Retorna o fator de balanceamento.
	if(N)
		return prof(N->es) - prof(N->di);   //Calcula e retorna o fator de balanceamento.
    return 0;                               //Caso o nó não exista retorna zero.
}

int max(int a, int b){				    	//Retorna o maior.
	return (a >= b)? a : b;                 //Se a>=b retorna a, caso contrário retorna b.
}

void ActProf(no x){                         //Atualiza profundidade.
    x->prof = max(prof(x->es), prof(x->di))+1; //Calcula a profundidade baseando-se nas profundidades dos filhos.
}

void giraD(no * N){						    //Rotação a direita.
	no A = (*N)->es;
	no B = A->di;
    //Efetua a rotação:
	A->di = *N;
	(*N)->es = B;

	//Atualiza profundidades:
	ActProf(*N);
	ActProf(A);
	*N = A;
}

void giraE(no * N){						    //Rotação a esquerda.
	no A = (*N)->di;
	no B = A->es;

    //Efetua a rotação.
	A->es = *N;
	(*N)->di = B;

	//Atualiza profundidades:
	ActProf(*N);
	ActProf(A);
	*N = A;
}

void balancear(no * N){                     //Balanceia a arvore.
    int b;

    if(*N){
        ActProf(*N);
        b = fatorB(*N);
        //return;//Desativa balanceamento
        if(b > 1){
            if(fatorB((*N)->es)>=0)		//Esquerda esquerda
                giraD(N);
            else{						//Esquerda direita
                giraE(&(*N)->es);
                giraD(N);
            }
        }
        if(b < -1){
            if(fatorB((*N)->es)<=0)		//Direita direita
                giraE(N);
            else{						//Direita esquerda
                giraD(&(*N)->di);
                giraE(N);
            }
        }
    }

}

int insere(no * N, int ch, int val){	    //Função recursiva de inserção em árvore.
	int retval;
	if(!*N){
    	*N = (novoN(ch, val));              //Se não existir nada, apenas cria o novo nó.
        retval = 1;
	}
	else if(ch < (*N)->ch)                  //Se a chave for menor
        retval = insere(&((*N)->es), ch, val);       //procura na prole da esquerda
	else if(ch > (*N)->ch)                  //caso seja maior
		retval = insere(&(*N)->di, ch, val);         //procura na da direita
	else{
        (*N)->valor = val;                  //Apenas atualiza o valor.
        retval = 0;
	}                                   //Se não for nem direita nem esquerda, o nó já existe

	balancear(N);                           //Balanceia a árvore das folhas para a raiz.
	return retval;
}

no meNOr(no N){                             //Dada uma árvore, retorna referêcia de seu menor elemento.
    if(N->es)
		return meNOr(N->es);                //Se ainda há o que percorrer, continuar a recursão.
    return N;                               //Se não existe elemento a esquerda, então este já é o menor.
}

int rem(no * N, int ch){                   //Função de remoção: dada uma chave, remove o elemento tentando manter a árvore balanceada.
    int RetVal;
    if(*N){
        if (ch < (*N)->ch )
                RetVal = rem(&(*N)->es, ch);
        else if( ch > (*N)->ch )

                RetVal = rem(&(*N)->di, ch);
        else{
            if(!(((*N)->es) && ((*N)->di))){
                no aux = (*N)->es ? (*N)->es : (*N)->di;//Aux é o filho que existir
                if (!aux) {     //Sem filhos
                    aux = *N;
                    *N = NULL;
                }
                else                    //Filho único
                    **N = *aux;         //Copia o conteúdo do filho único
                free(aux);
                RetVal = 1;
            }
            else{                                   //Dois filhos

                no aux = meNOr((*N)->di);           //Procurar o menor do lado dos maiores

                (*N)->ch = aux->ch;                 //Copia ele para a raiz
                (*N)->valor = aux->valor;           //Copia o valor também
                RetVal = rem(&(*N)->di, aux->ch);
            }
        }

        if (*N)
            balancear(N);

    }else
        RetVal =  0;

    return RetVal;
}

no busca(no N,int ch){   	                //Função recursiva de busca em árvore.
	if(!N)return 0;
	if(N->ch == ch)					        //Se o nó em questão for igual a chave buscada
    	return N;						    //Retorna resultado positivo

	if(ch < N->ch)
		return busca(N->es,ch);           	//Se a chave é menor, busca à esquerda.
                                            //Caso contrário
	return busca(N->di, ch);		        //busca à direita.
}

void preO(no n){						    //Imprime a árvore em pre ordem.
    if(n){
		printf("<%d %d %d> ", n->ch, n->valor, n->prof); //Imprime a chave, o valor e a profundidade onde o elemento se encontra.
		preO(n->es);
		preO(n->di);
	}
}




