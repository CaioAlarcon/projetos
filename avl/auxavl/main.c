#include <stdio.h>
#include <stdlib.h>


int main(){
    int i,aux;
    FILE * fp;

    srand(13);
    //Inserção de 1023 valores aleatórios
    fp = fopen("insere.txt","w+");
    for(i=0,aux=rand();i<=1023;i++,aux = rand())
        fprintf(fp,"1\n%d\n%d\n",aux, aux);
    fclose(fp);

    srand(13);

    //busca de 1023 valores aleatórios
    fp = fopen("busca.txt","w+");
    for(i=0,aux=rand();i<=1023;i++,aux = rand())
        fprintf(fp,"1\n%d\n",aux);
    fclose(fp);

    srand(13);
    //remoção de 1023 valores aleatórios
    fp = fopen("remove.txt","w+");
    for(i=0,aux=rand();i<=1023;i++,aux = rand())
        fprintf(fp,"2\n%d\n",aux);
    fclose(fp);



    //Inserção de 1023 valores sequenciais
    fp = fopen("insereS.txt","w+");
    for(i=0,aux=rand();i<=1023;i++)
        fprintf(fp,"1\n%d\n%d\n",i, i);
    fclose(fp);


    //busca de 1023 valores aleatórios
    fp = fopen("buscaS.txt","w+");
    for(i=0,aux=rand();i<=1023;i++)
        fprintf(fp,"1\n%d\n",i);
    fclose(fp);

     //remoção de 1023 valores aleatórios
    fp = fopen("removeS.txt","w+");
    for(i=0,aux=rand();i<=1023;i++)
        fprintf(fp,"2\n%d\n",i);
    fclose(fp);

    return 0;
}

