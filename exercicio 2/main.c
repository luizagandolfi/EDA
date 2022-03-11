#include <stdio.h>
#include <malloc.h>


typedef struct notemp {
float valor;
int coluna;
struct notemp* prox;
} node;

typedef node* pont;

typedef struct {
pont* a;
int linhas;
int colunas;
} matriz;

/////funcoes/////
void inicializar(matriz* m, int lin, int col) {
int i;
m->linhas = lin;
m->colunas = col;
m->a = (pont*) malloc(lin*sizeof(pont));
for (i=0;i<lin;i++) m->a[i] = NULL;
}

int atribui(matriz* m,int lin, int col,
float val) 
{
  if (lin<0 || lin >= m->linhas ||
    col<0 || col >= m->colunas) return 0;

    pont ant = NULL;
    pont atual = m->A[lin];
    while (atual != NULL && atual->coluna<col) 
    {
      ant = atual;
      atual = atual->prox;
    }
  if (atual != NULL && atual->coluna == col) 
  {
    if (val == 0) 
    {
      if (ant==NULL) 
        m->A[lin] = atual->prox;
      else 
        ant->prox = atual->prox;

      free(atual);
    }
    else 
      atual->valor = val;
  }

  else if (val != 0) 
  {
    pont novo = (pont) malloc(sizeof(node));
    novo->coluna = col;
    novo->valor = val;
    novo->prox = atual;
    if (ant == NULL) 
      m->A[lin] = novo;
    else 
      ant->prox = novo;
  }
  return 1;
}

float valor(matriz* m, int lin, int col) 
{
  if (lin<0 || lin>=m->linhas || col<0 || col >= m->colunas) 
    return 0;
  pont atual = m->A[lin];
  while (atual != NULL && atual->coluna < col)
    atual = atual->prox;
  if (atual !=NULL && atual->coluna == col)
    return atual->valor;
  return 0;
}

/////////////////

