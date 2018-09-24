//Define Fun como tipo ponteiro para função void que recebe um vetor int e um int:
typedef void (*Fun)(int [],int);

//Protótipo das funções:
void print(int*, int);
void CriaCenario(char [], int *, int, char []);
void ajuda(int);
void init(int [], int, int, int);
void troca(int *,int *);
Fun SelAlg(char []);
void salvar (char [], char [],int, char []);
