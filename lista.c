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
};

NodeList* createlist()
{
	List *newlist = (List*) malloc(sizeof(List));
	newlist->first = NULL;
	newlist->last = NULL;

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
}

void freelist(List* l)
{
	NodeList *current, *aux = list->first;
	while(aux != list->last)
	{
		current = aux->next;
		free(aux);
		aux = current;
	}
	free(aux);
}

#endif /* LISTA_C_ */