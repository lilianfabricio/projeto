/*
 * huffnode.c
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */

#ifndef PRIORITY_QUEUE_C_
#define PRIORITY_QUEUE_C_

#include "huffnode.h"
#include "hash.h"
#include "lista.h"

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

/* Função create_node: Aloca um espaço de memória correspondente a um nó,
 * enviando como parâmetros um caracter e sua frequência no texto.
 */
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

/* Função create_priority_queue: Aloca um espaço de memória correspondente a
 * uma fila de prioridades vazia.
 */
Priority_Queue* create_priority_queue()
{
	Priority_Queue *new_pq = (Priority_Queue*) malloc(sizeof(Priority_Queue));
	new_pq->first = NULL;
	new_pq->last = NULL;

	return new_pq;
}

/* Funçâo is_unique: Dada uma fila de prioridades, a função verifica se
 * esta fila possui apenas um elemento. A função será utilizada na
 * construção da árvore de Huffman.
 */
int is_unique(Priority_Queue *pq)
{
	return (pq->first->next == NULL);
}

/* Função enqueue_sorted: Dada uma fila de prioridades e um nó, a função
 * insere este nó na fila de prioridade, em sua devida posição tendo
 * como parâmetro de ordenação sua frequência no texto.
 */
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
	Node *aux = pq->first;
	while(aux != NULL)
	{
		printf("%c %d\n", aux->item, aux->frequency);
		aux = aux->next;
	}
}

Node* dequeue(Priority_Queue *pq)
{
	if(pq->first != NULL)
	{
		Node *dequeued;

		dequeued = pq->first;
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

		Node *new_n = create_node('*', freq);

		new_n->left = aux1;
		new_n->right = aux2;

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
			fprintf(arq, "%c%c", '\\', root->item);
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
	else if((root->item == '*' || root->item == '\\') && is_leaf(root)){
		return 2;
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

void getcode(HashHuff *h, Node* tree, List* l)
{
	if(tree->left == NULL && tree->right == NULL)
	{
		put(h, tree->item, l);
	}
	else
	{
		insertnode(l, '0');
		getcode(h, tree->left, l);
		removenode(l);

		insertnode(l, '1');
		getcode(h, tree->right, l);
		removenode(l);
	}
}

#endif /* PRIORITY_QUEUE_C_ */
