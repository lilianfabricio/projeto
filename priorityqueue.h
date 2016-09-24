/*
 * priority_queue.h
 *
 *  Created on: 24 de set de 2016
 *      Author: leony
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

typedef struct priority_queue Priority_Queue;

Node *create_node(char carac, int freq);

Priority_Queue *create_priority_queue();

void enqueue_sorted (Priority_Queue *pq, Node *node);

void print_queue(Priority_Queue *pq);

#endif /* PRIORITYQUEUE_H_ */
