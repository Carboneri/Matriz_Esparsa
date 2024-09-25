#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
ma criar()
{
	ma matriz = malloc(sizeof(Matriz));
	if (matriz != NULL)
	{
		matriz->colunas = matriz->linhas = NULL;
		matriz->pont = NULL;
		matriz->ant = NULL;
		matriz->linha = matriz->coluna = 0;
	}
	return matriz;
}

void gerar_colunas(ma cabeca, int j)
{
	Matriz *no = malloc(sizeof(Matriz));
	if (no == NULL)
	{
		printf("Erro ao alocar memoria para a coluna.\n");
		exit(1);
	}
	no->coluna = j;
	no->colunas = NULL;
	no->linhas = NULL;
	no->ant = NULL;
	no->pont = NULL;
	if (cabeca->colunas == NULL)
	{
		cabeca->colunas = no;
		no->colunas = cabeca;
		no->ant = cabeca;
		return;
	}
	else
	{
		Matriz *aux = cabeca;
		while (aux->colunas != cabeca)
		{
			aux = aux->colunas;
		}
		aux->colunas = no;
		no->colunas = cabeca;
		no->ant = aux;
	}
}

void gerar_linhas(ma cabeca, int i)
{
	Matriz *no = malloc(sizeof(Matriz));
	if (no == NULL)
	{
		printf("Erro ao alocar memoria para a linha.\n");
		exit(1);
	}
	no->linha = i;
	no->linhas = NULL;
	no->colunas = NULL;
	no->ant = NULL;
	no->pont = NULL;
	if (cabeca->linhas == NULL)
	{
		cabeca->linhas = no;
		no->linhas = cabeca;
		no->ant = cabeca;
		return;
	}
	else
	{
		Matriz *aux = cabeca;
		while (aux->linhas != cabeca)
		{
			aux = aux->linhas;
		}
		aux->linhas = no;
		no->linhas = cabeca;
		no->ant = aux;
	}
}

void tamanho_matriz(ma matriz, int linhas, int colunas)
{
	if (linhas <= 0 || colunas <= 0)
	{
		printf("Tamanho de matriz invalido. Linhas e colunas devem ser maiores que zero.\n");
		return;
	}
	for (int i = 0; i < linhas; i++)
	{
		gerar_linhas(matriz, i);
	}
	for (int j = 0; j < colunas; j++)
	{
		gerar_colunas(matriz, j);
	}
	matriz->linha = linhas;
	matriz->coluna = colunas;
}

void inserir(ma matriz, int dados, int x, int y) {
	Elem *no = malloc(sizeof(Elem));
	if (no == NULL) {
		printf("Erro ao alocar memC3ria para o nC3.\n");
		exit(1);
	}
	no->dados = dados;
	no->coluna = y;
	no->linha = x;
	no->dir = NULL;
	no->baixo = NULL;
	no->esq = NULL;
	no->cima = NULL;

	// Encontrar a linha correta
	Matriz *linha = matriz->linhas;
	while (linha != matriz && linha->linha != x) {
		linha = linha->linhas;
	}

	// Encontrar a coluna correta
	Matriz *coluna = matriz->colunas;
	while (coluna != matriz && coluna->coluna != y) {
		coluna = coluna->colunas;
	}

	// Insercao na linha
	if (linha != matriz) {
		Elem *aux = linha->pont;
		Elem *prev = NULL;

		while (aux != NULL && aux->coluna < y) {
			prev = aux;
			aux = aux->dir;
		}


		if (aux != NULL && aux->coluna == y) {
			aux->dados = dados;
			free(no);
			return;
		}

		// Inserir o novo nC3 na lista da linha
		no->dir = aux;
		no->esq = prev;
		if (prev != NULL) {
			prev->dir = no;
		} else {
			linha->pont = no;
		}
		if (aux != NULL) {
			aux->esq = no;
		}
	}

	// Insercao na coluna
	if (coluna != matriz) {
		Elem *aux = coluna->pont;
		Elem *prev = NULL;

		while (aux != NULL && aux->linha < x) {
			prev = aux;
			aux = aux->baixo;
		}


		if (aux != NULL && aux->linha == x) {
			return;
		}


		no->baixo = aux;
		no->cima = prev;
		if (prev != NULL) {
			prev->baixo = no;
		} else {
			coluna->pont = no;
		}
		if (aux != NULL) {
			aux->cima = no;
		}
	}
}

void imprimir(ma matriz)
{
	Matriz *linha = matriz->linhas;
	while (linha != matriz)
	{
		Elem *elem = linha->pont;
		for (int j = 0; j < matriz->coluna; j++)
		{
			if (elem != NULL && elem->coluna == j)
			{
				printf("[%d]", elem->dados);
				elem = elem->dir;
			}
			else
			{
				printf("[ ]");
			}
		}
		printf("\n");
		linha = linha->linhas;
	}
}
void encontrar(ma matriz, int valor) {
	Matriz* aux = matriz->linhas;
	int count = 0;
	while(aux != matriz) {
		Elem* elem = aux->pont;
		while(elem != NULL) {
			if(elem->dados == valor) {
				printf("\n[%d],(%d,%d)", elem->dados, elem->linha, elem->coluna);
				count++;
			}
			elem = elem->dir;
		}
		aux = aux->linhas;
	}
	printf("\nexistem %d numeros iguais!\n", count);
}
void liberar(ma matriz) {
	Matriz* Linha = matriz->linhas;
	while(Linha != matriz) {
		Matriz* prox = Linha->linhas;
		Elem* elem = Linha->pont;
		while(elem != NULL) {
			Elem* aux1 = elem->dir;
			free(elem);
			elem = aux1;
		}
		free(Linha);
		Linha = prox;
	}
	Matriz* Coluna = matriz->colunas;
	while(Coluna != matriz) {
		Matriz* proxy = Coluna->colunas;
		free(Coluna);
		Coluna = proxy;
	}
	free(matriz);
}
void Consultar(ma matriz, int x, int y) {
	if (x < 0 || y < 0 || x >= matriz->linha || y >= matriz->coluna)
	{
		printf("Erro: Posicao (%d,%d) fora dos limites da matriz.\n", x, y);
		return;
	}
	Matriz* aux_i = matriz->linhas;
	Matriz* aux_j = matriz->colunas;
	while( aux_i != matriz && aux_i->linha != x ) {
		aux_i = aux_i->linhas;
	}
	while(aux_j != matriz && aux_j->coluna != y ) {
		aux_j = aux_j->colunas;
	}
	if(aux_i == matriz || aux_j == matriz) {
		printf("nao existe!");
		return;
	} else {
		Elem* i = aux_i->pont;
		while(i != NULL && i->coluna != y) {
			i = i->dir;
		}
		if( i == NULL) {
			printf("nao existe!(%d,%d)", x,y);
			return;
		} else {
			printf("\nNumero na posicao escolhida: [%d]\n", i->dados);
		}

	}

}
void vizinhos(ma matriz, int x, int y) {
	Matriz* aux_i = matriz->linhas;
	Matriz* aux_j = matriz->colunas;
	while( aux_i != matriz && aux_i->linha != x ) {
		aux_i = aux_i->linhas;
	}
	while(aux_j != matriz && aux_j->coluna != y ) {
		aux_j = aux_j->colunas;
	}
	if(aux_i == matriz || aux_j == matriz) {
		printf("nao existe!");
		return;
	} else {
		Elem* i = aux_i->pont;
		while(i != NULL && i->coluna != y) {
			i = i->dir;
		}
		if( i == NULL) {
			printf("nao existe!(%d,%d)", x,y);
			return;
		} else {
			if (i->dir) {
				printf("\ndireita(%d,%d):[%d]\n", i->dir->linha,i->dir->coluna, i->dir->dados);
			} else {
				printf("\ndireira:[vazio]\n");
			}
			if (i->esq) {
				printf("\nesquerda(%d,%d):[%d]\n", i->esq->linha,i->esq->coluna, i->esq->dados);
			} else {
				printf("\nesquerda:[vazio]\n");
			}
			if (i->baixo) {
				printf("\nbaixo(%d,%d):[%d]\n", i->baixo->linha,i->baixo->coluna, i->baixo->dados);
			} else {
				printf("\nbaixo:[vazio]\n");
			}
			if (i->cima) {
				printf("\ncima(%d,%d):[%d]", i->cima->linha,i->cima->coluna, i->cima->dados);
			} else {
				printf("\ncima:[vazio]\n");
			}

		}
	}
}
void funcoes() {
	printf("1-Criar tamanho da matriz:\n");
	printf("2-Inserir dados na matriz:\n");
	printf("3-Imprimir matriz:\n");
	printf("4-Consultar(x,y):\n");
	printf("5-Encontrar numero:\n");
	printf("6-Vizinhos(x,y):\n");
	printf("7-Transposta:\n");
	printf("8-Sair:\n");
}


int menu() {
	ma Matriz = criar();
	int i = 0;
	system("cls");
	do {
		funcoes();
		scanf("%d", &i);

		switch (i) {
		case 1: {
			int x, y;
			printf("\nEscolha o tamanho da matriz(x,y)\n");
			scanf("%d", &x);
			scanf("%d", &y);
			tamanho_matriz(Matriz, x, y);
			break;
		}
		case 2: {
			if (Matriz->linhas == NULL) {
				printf("\nEscolha um tamanho de matriz primeiro!\n");
				break;
			}
			int x, y, z;
			printf("\nInsira um dado na matriz e sua posicao (x,y):\n");
			printf("Dado: \n");
			scanf("%d", &z);
			printf("Coordenadas (x,y): \n");
			scanf("%d", &x);
			scanf("%d", &y);
			inserir(Matriz, z, x, y);
			break;
		}
		case 3: {
			if (Matriz->linhas == NULL) {
				printf("\nEscolha um tamanho de matriz primeiro!\n");
				break;
			}
			printf("\nMatriz Completa:\n");
			imprimir(Matriz);
			break;
		}
		case 4: {
			if (Matriz->linhas == NULL) {
				printf("\nEscolha um tamanho de matriz primeiro!\n");
				break;
			}
			int x, y;
			printf("\nQual linha e colunas deseja consultar?(x,y):\n");
			scanf("%d", &x);
			scanf("%d", &y);
			Consultar(Matriz, x, y);
			break;
		}
		case 5: {
			if (Matriz->linhas == NULL) {
				printf("\nEscolha um tamanho de matriz primeiro!\n");
				break;
			}
			int num;
			printf("\nQual numero deseja encontrar?:\n");
			scanf("%d", &num);
			encontrar(Matriz, num);
			break;
		}
		case 6: {
			if (Matriz->linhas == NULL) {
				printf("\nEscolha um tamanho de matriz primeiro!\n");
				break;
			}
			int x, y;
			printf("\nQual numero deseja ver os vizinhos?(x,y):\n");
			scanf("%d", &x);
			scanf("%d", &y);
			vizinhos(Matriz, x, y);
			break;
		}
		case 8: {
			if (Matriz->linhas == NULL) {
				printf("\nMatriz nao foi inicializada!\n");
			} else {
				liberar(Matriz);
				printf("Matriz liberada e programa finalizado.\n");
			}
			break;
		}
        case 7: {
			if (Matriz->linhas == NULL) {
				printf("\nMatriz nao foi inicializada!\n");
			}
            printf("\nMatriz Transposta:\n");
            Transposta(Matriz);
			break;
		}
		default: {
			printf("Entrada invalida! Tente novamente.\n");
			break;
		}
		}
	} while (i != 8);

	return 0;
}
void Transposta(ma matriz){
    Matriz *aux = matriz->colunas;
    while (aux != matriz)
	{
		Elem *elem = aux->pont;
		for (int j = 0; j < matriz->linha; j++)
		{
			if (elem != NULL && elem->linha == j)
			{
				printf("[%d]", elem->dados);
				elem = elem->baixo;
			}
			else
			{
				printf("[ ]");
			}
		}
		printf("\n");
		aux = aux->colunas;
	}
}
