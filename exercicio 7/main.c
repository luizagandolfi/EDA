#include <stdio.h>
#include <stdlib.h>

struct conection_{
  int data;
  struct conection_ *next;
};
typedef struct conection_ Conection;

struct node{
  int data;
  Conection *beginning;
  int timestamp[2];
  char visited;
};
typedef struct node Node;

struct graph_{
  int vertix;
  Node **list;
};
typedef struct graph_ Graph;

void add(Graph *g, int v, int a){
  Conection *aux = malloc(sizeof(Conection));
  aux->data = a - 1;
  aux->next = g->list[v - 1]->beginning;
  g->list[v - 1]->beginning = aux;
}


int runPrivate(Graph *g, Node *n, int *visit){
  int result = 0;
  if(n){
    Conection *c = g->list[g->vertix]->beginning;
    if(!c){
      Conection *aux = malloc(sizeof(Conection));
      aux->data = n->data;
      aux->next = NULL;
      g->list[g->vertix]->beginning = aux;
    }
    else{
      while(c->next){
        c = c->next;
      }
      Conection *aux = malloc(sizeof(Conection));
      aux->data = n->data;
      aux->next = NULL;
      c->next = aux;
    }

    n->visited = 1;
    n->timestamp[0] = (*visit);
    (*visit) = (*visit) + 1;
    c = n->beginning;
    while(c != NULL){
      if(g->list[c->data]->visited == 0){
        if(runPrivate(g, g->list[c->data], visit)){
          result = 1;
        }
      }
      else if(g->list[c->data]->visited == 1){
        result = 1;
      }
      c = c->next;
    }
    n->visited = 2;
    n->timestamp[1] = (*visit);
    (*visit) = (*visit) + 1;
  }
  return result;
}


void run(Graph *g){
  int visit = 1;
  int result = 0;
  for(int i = 0; i < g->vertix; i++){
    if(g->list[i]->visited == 0){
      if(runPrivate(g, g->list[i], &visit)){
        result = 1;
      }
    }
  }

  Conection *c = g->list[g->vertix]->beginning;
  while(c){
    printf("%d [%d,%d]\n", c->data + 1, g->list[c->data]->timestamp[0], g->list[c->data]->timestamp[1]);
    c = c->next;
  }

  if(result){
    printf("aciclico: nao");
  }
  else{
    printf("aciclico: sim");
  }
}

void timestamp(Graph *g, Node *n){
  if(n){
    printf("%d [%d,%d]\n", n->data + 1, n->timestamp[0], n->timestamp[1]);
    Conection *c = n->beginning;
    n->visited = 0;
    while(c != NULL){
      if(g->list[c->data]->visited == 1){
        timestamp(g, g->list[c->data]);
      }
      c = c->next;
    }
  }
}

int checkCicle(Graph *g, Node *n){
  int result = 0;
  if(n){ 
    n->visited = 0;
    Conection *c = n->beginning;
    while(c != NULL){
      if(g->list[c->data]->visited == 1 || g->list[c->data]->visited == 2){
        if(checkCicle(g, g->list[c->data])){
          result = 1;
        }
      }
      else{
        result = 1;
      }
      c = c->next;
    }
    n->visited = 2;
  }
  return result;
}

void initialize(Graph *g, int v){
  g->vertix = v;
  g->list = malloc(sizeof(Node*)* (v + 1));
  for(int i = 0; i < v + 1; i++){
    g->list[i] = malloc(sizeof(Node));
    g->list[i]->data = i;
    g->list[i]->beginning = NULL;
    g->list[i]->timestamp[0] = 0;
    g->list[i]->timestamp[1] = 0;
    g->list[i]->visited = 0;
  }
}

void destroy(Graph *g)
{
    for(int i = 0; i < g->vertix + 1; i = i + 1)
    {
        Conection *c = g->list[i]->beginning;
        while(c)
        {
            Conection *aux = c;
            c = c->next;
            free(aux);
        }
    }
    free(g->list);
}

int main()
{
    Graph g;
    int vertix = 0;

    scanf("%d", &vertix);

    initialize(&g, vertix);

    int v, a;
    scanf("%d, %d", &v, &a);
    
    while(v != 0 && a != 0)
    {
        add(&g, v, a);
        scanf("%d, %d", &v, &a);
    }

    run(&g);

    destroy(&g);
    return 0;
}
