/*
 * priority_queue.h
 *
 *  Created on: 24 de set de 2016
 *      Author: leony
 */

#ifndef HUFFNODE_H_
#define HUFFNODE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

typedef struct priority_queue Priority_Queue;

Node *create_node(char carac, int freq);

Priority_Queue *create_priority_queue();

int is_empty(Priority_Queue *pq);

int is_unique(Priority_Queue *pq);

void enqueue_sorted (Priority_Queue *pq, Node *node);

void print_queue(Priority_Queue *pq);

Node *dequeue (Priority_Queue *pq);

Node *build_tree (Priority_Queue *pq);

void print_tree_pre_order(Node *root);

#endif /* HUFFNODE_H_ */
