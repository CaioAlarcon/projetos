#ifndef __AVL__
#define  __AVL__

typedef struct N{               //TAD da árvore
   int ch;                      //Chave
   int valor;                   //Valor (registro)
   int prof;                    //Profundidade
   struct N *es;                //Referência ao filho esquerdo
   struct N *di;                //Referência ao filho direito
} * no;


int insere(no*, int,int);	    //Insere na árvore e retorna 1 se conseguir, 0 caso contrário. Argumentos: Arvore chave valor
no busca(no, int);		        //Busca chave
int rem(no*, int);		        //Remove chave
void preO(no);				    //Imprime em pré ordem



#endif


