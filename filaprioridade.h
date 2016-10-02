#include <stdio.h>
#include <stdlib.h>


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
	return newnode;
}

/*Adicionando elementos na fila de acordo com a prioridade*/
void enqueue(PriorityQueue *pq, int i, int p)
{
	Node* newnode = (Node*) malloc(sizeof(Node));
	newnode->value = i;
	newnode->priority= p;
	if((is_empty(pq)) || (p > pq->first->priority))
	{
		newnode->nextNode = pq->first;
		pq->first= newnode;
	}
	else
	{
		Node *current = pq->first;
		while((current->nextNode != NULL) && (current->nextNode->priority > p))
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
	int value,priority;
	while(!is_empty(pq))
	{
		value = pq->first->value;
		priority = pq->first->priority;
		printf("%d %d\n",value, priority);
	    dequeue(pq);
	}
}
