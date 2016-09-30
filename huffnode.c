/*
 * priority_queue.c
 *
 *  Created on: 23 de set de 2016
 *      Author: leony
 */

#ifndef PRIORITY_QUEUE_C_
#define PRIORITY_QUEUE_C_

#include "huffnode.h"

struct node{
	char item;
	int frequency;
	Node *next;
	Node *left;
	Node *right;
};

struct priority_queue{
	Node *first;
	Node *last;
};

Node *create_node(char carac, int freq){
	Node *new_node = (Node*) malloc (sizeof(Node));
	if (carac == '*') new_node->item = '\*';
	else new_node->item = carac;
	new_node->frequency = freq;
	new_node->next = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

Priority_Queue *create_priority_queue(){
	Priority_Queue *new_pq = (Priority_Queue*)malloc(sizeof(Priority_Queue));
	new_pq->first = NULL;
	new_pq->last = NULL;
	return new_pq;
}

int is_unique(Priority_Queue *pq){
	return (pq->first->next == NULL);
}

void enqueue_sorted(Priority_Queue *pq, Node *node){
	if(pq->first == NULL) {
		pq->first = node;
		pq->last = node;
	} else if(node->frequency <= pq->first->frequency) {
		node->next = pq->first;
		pq->first = node;
	} else if(node->frequency > pq->last->frequency) {
		pq->last->next = node;
		pq->last = node;
	} else {
		Node *aux = pq->first;
		while(node->frequency > aux->next->frequency && aux->next != NULL){
			aux = aux->next;
		}
		node->next = aux->next;
		aux->next = node;
	}
}

void print_queue(Priority_Queue *pq){
	Node *aux;
	for(aux = pq->first; aux != NULL; aux = aux->next){
		printf("%c %d\n", aux->item, aux->frequency);
	}
}

Node *dequeue (Priority_Queue *pq){
	if(pq->first != NULL){
		Node *dequeued = pq->first;
		pq->first = pq->first->next;
		dequeued->next = NULL;
		return dequeued;
	}
	else return NULL;
}

Node *build_tree (Priority_Queue *pq){
	while (!is_unique(pq)){
		Node *aux1 = dequeue(pq);
		Node *aux2 = dequeue(pq);
		int freq = aux1->frequency + aux2->frequency;
		Node *new = (Node*) malloc (sizeof(Node));
		new->frequency = freq;
		new->item = '*';
		new->left = aux1;
		new->right = aux2;
		new->next = NULL;
		enqueue_sorted(pq,new);
	}
	return pq->first;
}

void print_tree_pre_order(Node *root, FILE *arq){
	if(root != NULL){
		fprintf(arq, "%c", root->item);
		print_tree_pre_order(root->left);
		print_tree_pre_order(root->right);
	}
}

#endif /* PRIORITY_QUEUE_C_ */
