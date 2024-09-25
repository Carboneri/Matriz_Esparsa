typedef struct elem
{
    int dados;
    int coluna;
    int linha;
    struct elem *baixo;
    struct elem *dir;
    struct elem *esq;
    struct elem *cima;
} Elem;

typedef struct Matriz
{
    Elem *pont;
    struct Matriz *colunas;
    struct Matriz *linhas;
    struct Matriz *ant;
    int linha;
    int coluna;
} Matriz, *ma;
ma criar();
void gerar_colunas(ma cabeca, int j);
void gerar_linhas(ma cabeca, int i);
void tamanho_matriz(ma matriz, int linhas, int colunas);
void inserir(ma matriz, int dados, int x, int y);
void imprimir(ma matriz);
void encontrar(ma matriz, int valor);
void liberar(ma matriz);
void Consultar(ma matriz, int x, int y);
void vizinhos(ma matriz, int x, int y);
void funcoes();
int menu();
void Transposta(ma matriz);
