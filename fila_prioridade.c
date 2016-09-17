#include <stdio.h>
#include <stdlib.h>

struct elemento
{
	int value;
	int priority;
	struct elemento *prox;
};

typedef struct elemento Elemento;

struct priority
{
	Elemento *first;
};

typedef struct priority PriorityQueue;

PriorityQueue* creat_queue()
{	
	/* Cria uma nova fila, que, como até agora esta vazia, aponta pra NULL; */
	PriorityQueue* new = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	new -> first = NULL;
	return new;
}
int is_empty(PriorityQueue *pq)
{
	if(pq -> first == NULL)
	{
		return 1;
	}
	else return 0;
}

void enqueue(PriorityQueue *pq, int i, int p) 
/* Enfileira um novo elemento de acordo com a prioridade */ 
{
	/* Cria o novo elemento da fila */
	Elemento *new = (Elemento*)malloc(sizeof(Elemento));
	new -> value = i;
	new -> priority = p;
	if ((is_empty(pq)) || (p > pq -> first -> priority)) 
	{
		/* Se a lista não estiver vazia e a prioridade do primeiro da fila for menor
		que a do novo elemento, entao o novo agora passa a ser o primeiro e aponta para 
		o antigo primeiro e a fila agora aponta para o novo */
		new->prox = pq->first;
		pq->first = new;

	} 
	else 
	{
		Elemento *current = pq -> first;

		while ((current -> prox != NULL) && (current -> prox -> priority > p)) 
		{
			/* Como a prioridade do novo elemento é menor que a do primeiro elemento, vamos 
			procurar onde a prioridade do novo vai se encaixar, navegando pela fila */

			current = current -> prox;
		}
		/* O atual é guardado temporariamente, já q a prioridade do proximo é menor que a do 
		novo elemento. O novo passa a apontar para onde o atual aponta e o atual agora passa
		a apontar para no novo */

		new -> prox = current -> prox;
		current -> prox = new;
	}
}

Elemento* dequeue(PriorityQueue *pq)
{
	/* Remove o primeiro da fila, ou seja, o de maior prioridade */ 
	if (!is_empty(pq)) 
	{
		Elemento *current = pq -> first;
		pq -> first = pq -> first -> prox;
		current -> prox = NULL;
		int v = current -> value;
		/* return v ---> Caso queira retornar apenas o valor ao inves do nó inteiro */
		return current;

	} 
	else 
	{
		return NULL;
	}
}

int maximum(PriorityQueue *pq)
{
	if (!is_empty(pq)) 
	{
		return pq -> first -> value;
	}
 	else 
 	{
 		printf("IS EMPTY\n");
 		return -1;
	}
}
void print(PriorityQueue *fila)
{
	int z;
	while(!is_empty(fila))
	{		
		z = maximum(fila);
	    printf("%d\n", z);
	    dequeue(fila);		
	}
}

