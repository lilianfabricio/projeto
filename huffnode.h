#ifndef HUFFNODE_H_
#define HUFFNODE_H_

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "lista.h"

typedef struct node Node;

typedef struct pqueue Priority_Queue;

Node* create_node(unsigned char carac, int freq);

Priority_Queue *create_priority_queue();

int is_unique(Priority_Queue *pq);

void enqueue_sorted(Priority_Queue *pq, Node *node);

void print_queue(Priority_Queue *pq);

Node* dequeue(Priority_Queue *pq);

Node* build_tree(Priority_Queue *pq);

void print_tree_pre_order(Node *root, FILE *arq);

int tree_size(Node *root);

int is_leaf(Node *node);

void funcao(HashHuff *h, unsigned char *tree, List *l, unsigned char lado);

#endif /* HUFFNODE_H_ */
