/*
 * main.c
 *
 *  Created on: 24 de set de 2016
 *      Author: leony
 */

#include "huffnode.h"

int main()
{
	int items[256], i;
	for (i = 0; i < 256; i++){
		items[i] = 0;
	}
	items[65] = 7;
	items[69] = 3;
	items[78] = 5;
	items[83] = 1;
	items[70] = 2;
	items[74] = 6;
	items[80] = 4;
	Priority_Queue *pq = create_priority_queue();
	for (i = 0; i < 256; i++){
		if (items[i] > 0){
			Node *new_node = create_node((char)i, items[i]);
			enqueue_sorted(pq, new_node);
		}
	}
	print_queue(pq);
	Node *root = build_tree(pq);
	print_tree_pre_order(root);
	printf("\n");
	print_queue(pq);
	return 0;
}
