#include <stdio.h>
#include <stdlib.h>
#define max_heap_size 20000

typedef struct heap Heap;

Heap* create_heap();

void swap(int *p, int *q);

int get_parent_index(Heap *hp, int i);

int get_left_index(Heap *hp, int i);

int get_right_index(Heap *hp, int i);

int value_of(Heap *hp, int i);

void heap_enqueue(Heap *hp, int value);

void max_heapify(Heap* hp, int i);

int heap_dequeue(Heap* hp);


