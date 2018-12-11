#include <stdio.h>
#include <stdlib.h>

#define Estrelas '*'
#define Bolas 'o'
void Inicializa(char matrix[][10]);
void limpa(char matrix[][10]);
void bordas(char matrix[][10]);

void Recarrega(char Tabuleiro[][10],char *joga);
void Salva(char Tabuleiro[][10],char joga);
void imprime (char matrix[][10]);
int PodeJogar(char tabuleiro[][10],char jogador);
int LerJogada(int *X,int *Y);
int JogadaValida(char Tabuleiro[][10],char jogador,int x , int y);
void Joga(char tabuleiro[][10], char joga, int lin, int col);
void estatisticas(char matriz[][10]);
void ajuda();

int EscolheJogada(char tabuleiro[][10], char jogador, int *lin, int *col);
char Adversario(char jogador);
int Busca(char matriz[][10], int x, int y, int a, int b);
void vira(char matriz[][10], int x, int y, int a, int b);
void AchaPossibilidades(char Tabuleiro[][10],int JP[],char Jogagor);
int NJogadas(char tabuleiro[][10],char jogador);
int PontuaPossibilidades(char Tabuleiro[][10],char joga,int P[],int jp[]);
void organiza (int jp[],int P[],int N);
void troca (int *a, int *b);

int pontuajogada(int A,int B);
void MostraPossibilidades(char Tabuleiro[][10],char joga);

int main(){
    char matriz[10][10],joga;
    int x, y;

    Inicializa(matriz);

    imprime (matriz);
    joga = Estrelas;
    do{

        do{
            printf("%c joga.\n",joga);
            if (PodeJogar(matriz,joga)){

                printf("De as coordenadas da sua jogada:\n");

                switch (LerJogada(&x,&y)){
                    case 1://computador joga
                        EscolheJogada(matriz, joga, &y,&x);
                        Joga(matriz,joga,y,x);
                        system("pause");
                        system("cls");
                        imprime (matriz);
                        joga = Adversario(joga);
                        continue;
                    case 2://sai
                        return 0;
                    case 3://salvar
                        Salva(matriz,joga);
                        printf("Jogo salvo.\n");
                        system("pause");
                        continue;
                    case 4://Recarregar
                        Recarrega(matriz,&joga);
                        system("cls");
                        imprime (matriz);
                        continue;
                    case 5://Reiniciar
                        Inicializa(matriz);
                        joga = Estrelas;
                        system("cls");
                        imprime (matriz);
                        continue;
                    case 6://Ajuda
                        system("cls");
                        ajuda();
                        system("pause");
                        system("cls");
                        imprime (matriz);
                        continue;

                }

                if (!JogadaValida(matriz, joga, x, y)){
                    printf("\nJogada invalida.\n");
                    printf("As jogadas validas sao:\n\n");
                    MostraPossibilidades(matriz,joga);
                    printf("\n\n");

                }
                else{
                    Joga(matriz,joga,y,x);
                    break;
                }
            }
            else{
                if(PodeJogar(matriz,Adversario(joga))){
                    printf ("%c perdeu a vez.\n",joga);
                    break;
                }
                else{
                    estatisticas(matriz);
                    system("pause");
                    Inicializa(matriz);
                    joga = Estrelas;
                    system("cls");
                    imprime (matriz);
                }

            }

        }while (1);

        system("pause");
        system("cls");
        imprime (matriz);

        joga = Adversario(joga);

        printf("%c joga.\n",joga);

        if (PodeJogar(matriz,joga)){
            EscolheJogada(matriz, joga, &y,&x);
            Joga(matriz,joga,y,x);
        }
        else{
            if(PodeJogar(matriz,Adversario(joga)))printf ("%c perdeu a vez.\n",joga);
            else{
                estatisticas(matriz);
                system("pause");
                Inicializa(matriz);
                joga = Estrelas;
                system("cls");
                imprime (matriz);
                continue;

            }
        }

        joga = Adversario(joga);
        system("pause");
        system("cls");
        imprime (matriz);
    }while(1);




    return 0;

}

void Inicializa(char matrix[][10]){//Prepara a matriz-tabuleiro para um inicio de jogo.
    limpa(matrix);
    bordas(matrix);
    matrix[4][4]=Estrelas;
    matrix[5][5]=Estrelas;
    matrix[5][4]=Bolas;
    matrix[4][5]=Bolas;
}
void bordas(char matrix[][10]){//Coloca as bordas na matriz-tabuleiro para indicar as extremidades.
    int i;
    for (i = 0;i<=8;i++){
        matrix[0][i]='!';
        matrix[i][9]='!';
        matrix[9][9-i]='!';
        matrix[9-i][0]='!';
    }
}
void limpa(char matrix[][10]){//torna as casas do tabuleiro iguais a ' '(um espaço em branco)
    int x,y;
    for (x=1;x<=8;x++)for(y=1;y<=8;y++)matrix[y][x]=' ';
}

void Recarrega(char Tabuleiro[][10],char *joga){//lê o arquivo rothelo.txt (se existir) e carreça a matriz com ele.
    char matriz[8][8];
    int x, y;
    FILE *Ta;
    Ta = fopen("rothelo.txt", "r");
    if (Ta == NULL)printf("arquivo nao existe.\n");
    else{
        fscanf(Ta,"%c",joga);
        for(x=0;x<8;x++)for(y=0;y<8;y++)fscanf(Ta,"%c",&matriz[x][y]);
        for(x=0;x<8;x++)for(y=0;y<8;y++)Tabuleiro[x+1][y+1]=matriz[x][y];
        fclose(Ta);
    }
}
void Salva(char Tabuleiro[][10],char joga){//Salva a situação atual no arquivo rothelo.txt
    char matriz[8][8];
    int x, y;
    FILE *Ta;
    Ta = fopen("rothelo.txt", "w");
    for(x=0;x<8;x++)for(y=0;y<8;y++){
        matriz[x][y]= Tabuleiro[x+1][y+1];
    }
    fprintf(Ta,"%c",joga);
    for(x=0;x<8;x++)for(y=0;y<8;y++)fprintf(Ta,"%c",matriz[x][y]);
    fclose(Ta);
}
void imprime (char matrix[][10]){//Imprime o tabuleiro.
    int x, y;
    printf("  | A | B | C | D | E | F | G | H |");
    for(y=1;y<=8;y++){
        printf("\n----------------------------------");
        printf("\n%d |",y);
        for(x=1;x<=8;x++)printf(" %c |",matrix[y][x]);
    }
    printf("\n----------------------------------\n");
}
int PodeJogar(char tabuleiro[][10],char jogador){//Retorna 1 se existir pelomenos uma jogada válida para jogador.
    int x, y;
    for (x=1;x<=8;x++)for (y=1;y<=8;y++)if(JogadaValida(tabuleiro,jogador,x,y))return 1;
    return 0;
}
int LerJogada(int *X,int *Y){//Lê a jogada que será digitada e toma as decisões necessárias.
    int  N,k=1;
    char A;
    while(k){
        A = getchar();
        switch (A){
            case 'j':
                return 1;
                break;
            case 't':
                return 2;
                break;
            case 's':
                return 3;
                break;
            case 'r':
                return 4;
                break;
            case 'z':
                return 5;
                break;
            case '?':
                return 6;
                break;

        }
        scanf("%d",&N);
        *Y = N;
        if(A>='A' && A<='H') *X=A-64;//letras maiusculas
        if(A>='a' && A<='h') *X=A-96;//letras minusculas
        if(*X>=1 && *X<=8 && *Y>=1 && *Y<=8)k=0;
    }

    return 0;
}
int JogadaValida(char Tabuleiro[][10],char jogador,int x , int y){//Retorna 1 se a jogada for válida e 0 caso contrário.
    int m,n;
    if (Tabuleiro[y][x]!=' ')return 0;

    for(n=-1;n<=1;n++){
        for(m=-1;m<=1;m++){/*Analiza as posições em volta da jogada desejada*/
            if (m==0 && n==0)m++;/*Isso faz pular a posição n,m(central)*/
            if(Tabuleiro[y+n][x+m]==Adversario(jogador))if(Busca(Tabuleiro, x, y, m, n))return 1;
        }
    }
    return 0;
}
void Joga(char tabuleiro[][10], char joga, int lin, int col){//Efetua a jogada.
    int m,n;
    for(n=-1;n<=1;n++){
        for(m=-1;m<=1;m++){
            if (m==0 && n==0)m++;/*Isso faz pular a posição n,m*/
            if(tabuleiro[lin+n][col+m]==Adversario(joga))
                if(Busca(tabuleiro, col, lin, m, n))
                    vira(tabuleiro, col, lin, m, n);
        }
    }
}
void estatisticas(char matriz[][10]){//Exibe quem ganhou e de quanto ganhou.

    int x,y, estrela=0, bola=0;
    system("cls");
    imprime(matriz);

    printf("O jogo acabou.\n");
    for (x=1; x<9;x++) for (y=1; y<9;y++){
        if (matriz[x][y]== Bolas) bola++;
        if (matriz[x][y]== Estrelas) estrela ++;
    }
    if(bola == estrela)printf("\nDeu empate.\n");
    if(bola > estrela)printf("\n%c ganhou.\n",Bolas);
    if(bola < estrela)printf("\n%c ganhou.\n",Estrelas);
    printf("\n%c: %d\n%c: %d\n",Estrelas,estrela,Bolas,bola);
}
void ajuda(){//Exibe a ajuda.
    printf("\t\t\tAJUDA DO ROTHELO:\n");
    printf("-Para jogar, basta digitar as coordenadas da sua jogada.\n");
    printf("\tAs coordenadas aceitas vao de A1 a H8 (as letras podem ser maiusculas ou minusculas).\n");
    printf("-Alguns comandos de controle podem ser utilizados:\n");
    printf("\tj : O computador faz a jogada e a jogada seguinte passa a ser sua a menos que aperte j novamente.\n");
    printf("\tt : Encerra o programa.\n");
    printf("\ts : Salva a partida.\n");
    printf("\tr : Recarrega a ultima partida salva.\n");
    printf("\tz : Reinicia o jogo.\n");
    printf("\t? : Exibe esta tela de ajuda.\n");
}

int EscolheJogada(char tabuleiro[][10], char jogador, int *lin, int *col){//seleciona a jogada que vale mais.
    int N,x;
    int jp[32];//Jogadas Possiveis
    int P[32]; // Pontuação.
    for(x=0;x<32;x++){
        jp[x]=0;//Limpa jp e P
        P[x]=0;
    }
    AchaPossibilidades(tabuleiro,jp,jogador);
    if (NJogadas(tabuleiro,jogador)==1){
        *lin = jp[0]%10;
        *col = jp[0]/10;
        return 0;
    }
    N = PontuaPossibilidades(tabuleiro,jogador,P,jp);//Fornece também o número de linhas da matriz (que é o numero de jjogadas).
    organiza (jp,P,N);


    //verificar se a jogada de maior valor tem repetições e escolher aleatóriamente entre elas.
    x=0;
    while(P[x]==P[x+1])x++;
    if (x!=0)x = rand()%x;
    *lin = jp[x]%10;
    *col = jp[x]/10;
    return 0;
}
char Adversario(char jogador){//retorna o adversário de jogador.
    switch (jogador){
        case Bolas: return Estrelas;
        case Estrelas: return Bolas;
    }
    return '?';
}
int Busca(char matriz[][10], int x, int y, int a, int b){//xy é uma posição vazia ab é uma direção para onde existe uma peça adversária encostada na casa vazia. Essa função devolve 1 se for possivel virar essa peça e 0 se não for.
    int f=0,g=0;//a e b indicam a direção pra onde a peça adversária se encontra.
    f=f+a;//
    g=g+b;//assim é possivel "andar" nesta direção....
    char adversario = matriz[y+g][x+f];
    do{
        f=f+a;
        g=g+b;
    }while(matriz[y+g][x+f]==adversario);//Descobrir o que tem lá (Aqui)

    if (matriz[y+g][x+f]==Adversario(adversario))return 1;//e finalmente ver o se é possivel virar a peça adversária.
    return 0;
}
void vira(char matriz[][10], int x, int y, int a, int b){//Vira as peças apenas em uma direção
    int f=0,g=0;

    char jogador = Adversario(matriz[y+b][x+a]);
    char adversario = matriz[y+b][x+a];
    do{
        matriz[y+g][x+f]=jogador;
        f=f+a;
        g=g+b;

    }while(matriz[y+g][x+f]==adversario);


}
void AchaPossibilidades(char Tabuleiro[][10],int JP[],char Jogador){//Preenche a matriz das jogadas com todas as jogadas válidas para jogador
    int x,y,linha=0;
    for (x=1;x<9;x++)for (y=1;y<9;y++){
        if(JogadaValida(Tabuleiro,Jogador,x,y)){
            JP[linha]=x*10+y;//guarda a jogada em um numero de 11 a 88.
            linha++;
        }
    }
}
int NJogadas(char tabuleiro[][10],char jogador){//retorna o valor de jogadas possiveis para jogador
    int x, y,conta=0;
    for(x=1;x<=8;x++) for(y=1;y<=8;y++) if(JogadaValida(tabuleiro,jogador,x,y)) conta++;
    return conta;

}
int PontuaPossibilidades(char Tabuleiro[][10],char joga,int P[],int jp[]){//pontua cada possibilidade e garda na matriz dos pontos
    char Auxiliar[10][10];
    int x,y,linha=0;
    while (jp[linha]!=0){
        for(x=0;x<10;x++)for(y=0;y<10;y++)Auxiliar[x][y]=Tabuleiro[x][y];
        x=jp[linha]/10;
        y=jp[linha]%10;
        Joga(Auxiliar,joga,y,x);//Isso é uma simulação.
        P[linha] = pontuajogada(x,y);
        linha++;
    }
    return linha;
}
void organiza (int jp[],int P[],int N){//Organiza a matriz com os valores da jogada sem desvincular a matriz das jogadas.
    int x,y;
    for (x=0;x<N;x++){
        for (y=x+1;y<N;y++){
            if(P[x]<P[y]){
                troca(&jp[x],&jp[y]);
                troca(&P[x],&P[y]);
            }

        }
    }

}
void troca (int *a, int *b){//Efetua a troca de valores entre duas variáveis inteiras
    int c;
    c=*a;
    *a=*b;
    *b=c;
 }
int pontuajogada(int A,int B){//Retorna a pontuação da jogada baseado na localização da jogada.
    int conta=0,m;

    //peça na quina vale muito.
    if(A==1&&B ==8)conta +=200;
    if(A==8&&B ==8)conta +=200;
    if(A==1&&B ==1)conta +=200;
    if(A==8&&B ==1)conta +=200;

    //peças nas paredes mas longe da quina
    for (m=3;m<7;m++){
        if(A==m && B==1)conta +=150;
        if(A==m && B==8)conta +=150;
        if(A==8 && B==m)conta +=150;
        if(A==1 && B==m)conta +=150;
    }

    for (m=2;m<8;m+=5){//parede perto da quina
        if(A==m && B==1)conta +=-100;
        if(A==m && B==8)conta +=-100;
        if(A==8 && B==m)conta +=-100;
        if(A==1 && B==m)conta +=-100;
    }

    for (m=3;m<7;m++){//as casas encostadas nas casas da parede valem pouco pois permitem alcançar as paredes
        if(A==m && B==2)conta +=-50;
        if(A==m && B==7)conta +=-50;
        if(A==7 && B==m)conta +=-50;
        if(A==2 && B==m)conta +=-50;
    }

    for (m=3;m<7;m++){//as casas encostadas nas casas centrais iniciais valem pois obrigam o oponente a jogaar onde não vale.
        if(A==m && B==3)conta +=25;
        if(A==m && B==6)conta +=25;
        if(A==6 && B==m)conta +=25;
        if(A==3 && B==m)conta +=25;
    }

    if(A==2 && B==7)conta +=-200;//diagonal perto da quina (não jogue se tiver outra opção)
    if(A==7 && B==7)conta +=-200;
    if(A==2 && B==2)conta +=-200;
    if(A==7 && B==2)conta +=-200;

    return  conta;
}

void MostraPossibilidades(char Tabuleiro[][10],char joga){//Exibe ao jogador suas possibilidades de jogo.
    int x,y;
    for (x=1;x<9;x++)for (y=1;y<9;y++){
        if(JogadaValida(Tabuleiro,joga,x,y)){
            printf("%c%d\n",(x+'A'-1),y);
        }
    }

}


