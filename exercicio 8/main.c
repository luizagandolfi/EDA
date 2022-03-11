#include <stdio.h>
#include <stdlib.h>

struct _node{
  int index;
  int distance;
  struct _node *next;
};
typedef struct _node node;

struct _queue{
  node *beginning;
  node *end;
};

typedef struct _queue queue;

struct _graph{
    int vertix;
    int **matrix;
};
typedef struct _graph Graph;

void add(Graph *g, int v, int a){
  v = v - 1;
  a = a - 1;
  g->matrix[v][a] = 1;
  g->matrix[a][v] = 1;
}

void runPrivate(Graph *g, int *visit, queue *q)
{
    if(q->beginning == 0)
        return;
    
    for (int i = 0; i < g->vertix; i++)
    {
        if(visit[i] != 1 && g->matrix[q->beginning->index][i] == 1)
        {
            node *aux = malloc(sizeof(node));
            aux->distance = q->beginning->distance + 1;
            aux->next = 0;
            aux->index = i;
            q->end->next = aux;
            q->end = aux;
            visit[i] = 1;
        }
    }
    node *rem = q->beginning;
    q->beginning = rem->next;
    printf("%d %d\n", rem->index + 1, rem->distance);
    free(rem);
    runPrivate(g, visit, q);
}

void run(Graph *g, int beginning){
  int *visit = malloc(sizeof(int) * g->vertix);
  printf("Origem da busca: %d\nVertices alcancados e distancias:\n", beginning);
  queue *q = malloc(sizeof(queue));
  q->beginning = malloc(sizeof(node));
  q->beginning->next = 0;
  q->beginning->distance = 0;
  q->beginning->index = beginning - 1;
  q->end = q->beginning;
  visit[beginning - 1] = 1;
  runPrivate(g, visit, q);
  free(visit);
}

void initialize(Graph *g, int v)
{
    g->vertix = v;
    g->matrix = (int**)malloc(sizeof(int*)* v);
    for(int i = 0; i < v; i++)
    {
        g->matrix[i] = (int*)malloc(sizeof(int)* v);
    }
}

void destroy(Graph *g)
{
  for(int i = 0; i < g->vertix; i = i + 1)
  {
    free(g->matrix[i]);
  }
  free(g->matrix);
}

int main()
{
  Graph g;
  int vertix = 0,v,a;
  int beginning = 0;

  scanf("%d", &vertix);
  initialize(&g, vertix);
  scanf("%d, %d", &v, &a);
    
  while(v != 0 && a != 0){
    add(&g, v, a);
    scanf("%d, %d", &v, &a);
  }

  scanf("%d", &beginning);
    run(&g, beginning);
    destroy(&g);
    return 0;
}