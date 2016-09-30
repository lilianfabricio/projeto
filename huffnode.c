/*
 * priorityqueue.c
 *
 *  Created on: 25 de set de 2016
 *      Author: vitor_000
 */

#ifndef PRIORITY_QUEUE_C_
#define PRIORITY_QUEUE_C_

#include "huffnode.h"

typedef struct node
{
	unsigned char item;
	int frequency;
	Node *next;
	Node *left;
	Node *right;
}Node;

typedef struct pqueue
{
	Node *first;
	Node *last;
}Priority_Queue;

Node* create_node(unsigned char carac, int freq)
{
	Node* new_node = (Node*) malloc(sizeof(Node));

	new_node->item = carac;
	new_node->frequency = freq;

	new_node->left = NULL;
	new_node->next = NULL;
	new_node->right = NULL;

	return new_node;
}

Priority_Queue* create_priority_queue()
{
	Priority_Queue *new_pq = (Priority_Queue*) malloc(sizeof(Priority_Queue));
	new_pq->first = NULL;
	new_pq->last = NULL;

	return new_pq;
}

int is_unique(Priority_Queue *pq)
{
	return (pq->first->next == NULL);
}

void enqueue_sorted(Priority_Queue *pq, Node *node)
{
	if(pq->first == NULL)
	{
		pq->first = node;
		pq->last = node;
	}
	else if (node->frequency <= pq->first->frequency)
	{
		node->next = pq->first;
		pq->first = node;
	}
	else if (node->frequency > pq->last->frequency)
	{
		pq->last->next = node;
		pq->last = node;
	}
	else
	{
		Node *aux;

		aux = pq->first;
		while (node->frequency > aux->next->frequency && aux->next != NULL)
		{
			aux = aux->next;
		}

		node->next = aux->next;
		aux->next = node;
	}
}

void print_queue(Priority_Queue *pq)
{
	if(pq != NULL)
	{
		printf("%c %d\n", pq->first->item, pq->first->frequency);
	}
}

Node* dequeue(Priority_Queue *pq)
{
	if(pq->first != NULL)
	{
		Node *dequeued;

		dequeued= pq->first;
		pq->first = pq->first->next;
		dequeued->next = NULL;

		return dequeued;
	}
	else
	{
		return NULL;
	}
}

Node* build_tree(Priority_Queue *pq)
{
	while(!is_unique(pq))
	{
		Node *aux1 = dequeue(pq);
		Node *aux2 = dequeue(pq);

		int freq = aux1->frequency + aux2->frequency;

		Node *new_n = (Node*) malloc(sizeof(Node));

		new_n->frequency = freq;
		new_n->item = '*';
		new_n->left = aux1;
		new_n->next = aux2;

		enqueue_sorted(pq, new_n);
	}

	return pq->first;
}

void print_tree_pre_order(Node *root, FILE *arq)
{
	if(root != NULL)
	{
		if(root->item == '*' && root->left == NULL && root->right == NULL)
		{
			fprintf(arq, "%c%c", 92, 42);
		}
		else
		{
			fprintf(arq, "%c", root->item);
		}
		print_tree_pre_order(root->left, arq);
		print_tree_pre_order(root->right, arq);
	}
}

int tree_size(Node *root)
{
	if(root == NULL)
	{
		return 0;
	}
	else
	{
		return (1 + tree_size(root->left) + tree_size(root->right));
	}
}

int is_leaf(Node *node)
{
	return (node->left == NULL && node->right == NULL);
}

void funcao(HashHuff *h, Node *root, unsigned char *c)
{
	if(root != NULL)
	{
		if(is_leaf(root))
		{
			put( h, root->item, c);
			c = c - 1;
		}
		else
		{
			c[0] = 0;
			funcao( h, root->left, (c+1));
			c[0] = 1;
			funcao( h, root->right, (c+1));
		}
	}
}

#endif /* PRIORITY_QUEUE_C_ */
