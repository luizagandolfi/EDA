#include<stdio.h>
#include<stdlib.h>

struct queueNode{
    char data;
    int freq;
    struct queueNode *left;
    struct queueNode *right;
};
typedef struct queueNode node;

struct queue_struct{
    int size;
    node *priority[28];
};
typedef struct queue_struct queue;

void up(queue *q, int pos);

void down(queue *q, int pos);

void insert(queue *q, node *n);

node* remov(queue *q);

void swap(queue *q, int a, int b);

int count(node *n, int dist);

int main(){
  char sequency;
  queue list;
  list.size = 0;
  int frequency[28] = {0};
    
  while(scanf("%c", &sequency) != EOF){
    if(sequency == '\n')
      frequency[27] = frequency[27] + 1;

    else if(sequency == ' ')
      frequency[26] = frequency[26] + 1;

    frequency[sequency - 'a'] = frequency[sequency - 'a'] + 1;
  }
  
  for (int i = 0; i < 28; i++){
    if(frequency[i] > 0){
      node *new = (node*)malloc(sizeof(node));
      new->data = 'a' + i;
      new->freq = frequency[i];
      new->right = NULL;
      new->left = NULL;
      insert(&list, new);
    }
  }
  while(list.size > 1){
    node *temp = remov(&list);
    node *aux = remov(&list);
    node *new = (node*)malloc(sizeof(node));
    new->right = temp;
    new->left = aux;
    new->freq = temp->freq + aux->freq;
    new->data = '\0';
    insert(&list, new);
    }
    
    if(list.size > 0)
      printf("%d\n", count(list.priority[0], 0));

    return 0;
}

void up(queue *q, int pos){
  if(pos == 0)
    return;
  int father = 0;
  if(pos % 2 == 1)
    father = (pos - 1)/2;

  else
    father = (pos - 2)/2;

  if(q->priority[father]->freq > q->priority[pos]->freq){
    swap(q, father, pos);
    up(q, father);
  }

}

void down(queue *q, int pos){
  if(pos*2 + 1 >= q->size)
    return;
        
  else if(pos*2 + 2 >= q->size){
    if(q->priority[pos]->freq > q->priority[pos*2 + 1]->freq){
      swap(q, pos*2 + 1, pos);
      down(q, pos*2 + 1);
    }
  }
  else{
    if(q->priority[pos*2 + 2]->freq < q->priority[pos*2 + 1]->freq){
      if(q->priority[pos]->freq > q->priority[pos*2 + 2]->freq){
        swap(q, pos*2 + 2, pos);
        down(q, pos*2 + 2);
      }
    }
    else{
      if(q->priority[pos]->freq > q->priority[pos*2 + 1]->freq){
        swap(q, pos*2 + 1, pos);
        down(q, pos*2 + 1);
      }
    }
  }
}

void swap(queue *q, int a, int b)
{
  node *aux = q->priority[a];
  q->priority[a] = q->priority[b];
  q->priority[b] = aux;
}

int count(node *n, int dist)
{
  if(!n)
    return 0;
    
    if(n->data != '\0'){
      if(dist == 0)
        dist = 1;
      
      return n->freq * dist;
    }

  return count(n->left, dist + 1) + count(n->right, dist + 1);
}

void insert(queue *q, node *n)
{
  if(q->size == 0)
    q->priority[0] = n;

  else{
    q->priority[q->size] = n;
    up(q, q->size);
  }
  q->size++;
}

node* remov(queue *q)
{
  node *n = q->priority[0];
  q->priority[0] = q->priority[q->size - 1];
  q->size--;
  down(q, 0);
  
    return n;
}
