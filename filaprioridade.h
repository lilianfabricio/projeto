#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

typedef struct Priority_Queue PriorityQueue;

/*Verifica se a fila está vazia*/
int is_empty(PriorityQueue *pq);

/*Criação da Fila de prioridade*/
PriorityQueue* create_priority_queue();

/*Adicionando elementos na fila de acordo com a prioridade*/
void enqueue(PriorityQueue *pq, int i, int p);

/*Desenfileirando o elemento de maior prioridade*/
Node *dequeue(PriorityQueue *pq);

/*Imprimir fila de prioridade*/
void print_queue(PriorityQueue *pq);
