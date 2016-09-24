/*
 * priority_queue.c
 *
 *  Created on: 23 de set de 2016
 *      Author: leony
 */

#ifndef PRIORITY_QUEUE_C_
#define PRIORITY_QUEUE_C_

#include "priorityqueue.h"

struct node{
	char item;
	int frequency;
	Node *next;
	Node *left;
	Node *right;
};

struct priority_queue{
	Node *first;
};

Node *create_node(char carac, int freq){
	Node *new_node = (Node*) malloc (sizeof(Node));
	new_node->item = carac;
	new_node->frequency = freq;
	new_node->next = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

Priority_Queue *create_priority_queue(){
	Priority_Queue *new_pq = (Priority_Queue*)malloc(sizeof(Priority_Queue));
	new_pq->first = NULL;
	return new_pq;
}

void enqueue_sorted(Priority_Queue *pq, Node *node){
	if(pq->first == NULL || node->frequency < pq->first->frequency){
		pq->first = node;
		node->next = pq->first;
	}
	else{
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

#endif /* PRIORITY_QUEUE_C_ */
