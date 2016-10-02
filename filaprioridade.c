/* * filaprioridade.c
 *
 *  Created on: 2 de out de 2016
 *      Author: Leony
 */

#include "filaprioridade.h"

struct node
{
	int value;
	int priority;
	struct node *nextNode;
};

typedef struct node Node;

struct Priority_Queue
{
	Node *first;
	Node *last;
};

typedef struct Priority_Queue PriorityQueue;

/*Verifica se a fila está vazia*/
int is_empty(PriorityQueue *pq)
{
	if(pq->first == NULL)
	{
		return 1;
	}
	else return 0;
}

/*Criação da Fila de prioridade*/
PriorityQueue* create_priority_queue()
{
	PriorityQueue* newnode = (PriorityQueue*) malloc(sizeof(PriorityQueue));
	newnode -> first = NULL;
	newnode -> last = NULL;
	return newnode;
}

/*Adicionando elementos na fila de acordo com a prioridade*/
void enqueue(PriorityQueue *pq, int i, int p)
{
	Node* newnode = (Node*) malloc(sizeof(Node));
	newnode->value = i;
	newnode->priority= p;
	newnode->nextNode = NULL;
	if(is_empty(pq))
	{
		pq->first = newnode;
		pq->last = newnode;
	}
	else if(newnode->priority > pq->first->priority)
	{
		newnode->nextNode = pq->first;
		pq->first = newnode;
	}
	else if(newnode->priority < pq->last->priority)
	{
		pq->last->nextNode = newnode;
		pq->last = newnode;
	}
	else
	{
		Node *current = pq->first;
		while((current->nextNode != NULL) && (current->priority > p))
		{
			current = current->nextNode;
		}
		newnode->nextNode = current->nextNode;
		current->nextNode = newnode;
	}
}

/*Desenfileirando o elemento de maior prioridade*/
Node *dequeue(PriorityQueue *pq)
{
	if(!is_empty(pq))
	{
		Node *current = pq->first;
		pq->first = pq->first->nextNode;
		current->nextNode = NULL;
		return current;
	}
	else
	{
		printf("Empty priority queue!");
		return NULL;
	}
}

/*Imprimir fila de prioridade*/
void print_queue(PriorityQueue *pq)
{
	Node *aux = pq->first;
	while(aux != NULL)
	{
		printf("%d %d\n",aux->value, aux->priority);
		aux = aux->nextNode;
	}
}

