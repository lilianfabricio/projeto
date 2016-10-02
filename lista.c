#ifndef LISTA_C_
#define LISTA_C_

#include "lista.h"

typedef struct node_list NodeList;
struct node_list
{
	unsigned char c;
	NodeList* next;
};

typedef struct list List;
struct list
{
	NodeList* first;
	NodeList* last;
	int tam;
};

List* createlist()
{
	List *newlist = (List*) malloc(sizeof(List));
	newlist->first = NULL;
	newlist->last = NULL;
	newlist->tam = 0;

	return newlist;
}

void insertnode(List* l, unsigned char c)
{
	NodeList* aux = (NodeList*) malloc(sizeof(NodeList));
	aux->c = c;
	if(l->first == NULL)
	{
		l->first = aux;
		l->last = aux;
	}
	else
	{
		aux->next = l->first;
		l->first = aux;
	}
	l->tam++;
}

int listsize(List* list)
{
	return list->tam;
}

NodeList* removenode(List* l)
{
	NodeList* aux;
	aux = l->first;
	l->first = aux->next;
	aux->next = NULL;

	return aux;
}

#endif /* LISTA_C_ */
