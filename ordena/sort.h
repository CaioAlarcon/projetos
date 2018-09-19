//Declara Fun como ponteiro para função void que recebe um vetor int e um int:
typedef void (*Fun)(int [],int);

void print(int*, int);
void CriaCenario(char [], int *, int);
void ajuda(int);//Exibe a mensagem de ajuda
void init(int [], int, int, int);//Cria os diferentes cenários
void troca(int *,int *);
Fun SelAlg(char []);
