#include <stdio.h>
#include <stdlib.h>
#define max_heap_size 200

struct heap
{
	int size;
	int data[max_heap_size];
};

typedef struct heap Heap;

Heap* create_heap()
{
	Heap* newheap = (Heap*) malloc(sizeof(Heap));
	newheap->size = 0;

}

void swap(int *p, int *q)
{
	int k = *p;
	*p = *q;
	*q = k;
}


int get_parent_index(Heap *hp, int i)
{
	return i/2;
}

int get_left_index(Heap *hp, int i)
{
	return 2*i;
}

int get_right_index(Heap *hp, int i)
{
	return 2*i + 1;
}

int value_of(Heap *hp, int i)
{
	return hp->data[i];
}

void heap_enqueue(Heap *hp, int value)
{
	if(hp->size >= max_heap_size)
	{
		printf("Heap is full, %d,%d",hp->size,value);
	}
	else
	{
		hp->data[++hp->size] = value;
		int key_index = hp->size;
		int parent_index = get_parent_index(hp,hp->size);
		while(parent_index >= 1 && hp->data[key_index] > hp->data[parent_index])
		{
			swap(&hp->data[key_index], &hp->data[parent_index]);
			key_index = parent_index;
			parent_index = get_parent_index(hp,key_index);
		}
	}
}

void max_heapify(Heap* hp, int i)
{
	int largest;
	int left_index = get_left_index(hp,i);
	int right_index = get_right_index(hp, i);
	if(left_index <= hp->size && hp->data[left_index > hp->data[i]])
	{
		largest = left_index;
	}
	else
	{
		largest = i;
	}
	if(right_index <= hp->size && hp->data[right_index] > hp->data[largest])
	{
		largest = right_index;
	}
	if(hp->data[i] != hp->data[largest])
	{
		swap(&hp->data[i], &hp->data[largest]);
		max_heapify(hp,largest);
	}
}

int heap_dequeue(Heap* hp)
{
	int value = hp->data[1];
	hp->data[1] = hp->data[hp->size];
	hp->size--;
	max_heapify(hp, 1);
	return value;
}


