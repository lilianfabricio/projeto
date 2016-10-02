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
	int tam;
};

List* createlist()
{
	List *newlist = (List*) malloc(sizeof(List));
	newlist->first = NULL;
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
		l->first->next = NULL;
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

unsigned char removenode(List* l)
{
	NodeList* aux;
	aux = l->first;
	l->first = aux->next;
	aux->next = NULL;

	return aux->c;
}

void printlist(List* l)
{
	NodeList* aux = l->first;
	while(aux != NULL)
	{
		printf("%c\n", aux->c);
		aux = aux->next;
	}
}

#endif /* LISTA_C_ */
