#ifndef LISTA_C_
#define LISTA_C_

#include "lista.h"

typedef struct node_list NodeList;
struct node_list
{
	char c;
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

void insertnode(List* l, char c)
{
	NodeList* aux = (NodeList*) malloc(sizeof(NodeList));
	aux->c = c;
	if(l->first == NULL)
	{
		l->first = aux;
		aux->next = NULL;
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

char* getstring(List* l)
{
	int i, tam;
	NodeList* aux = l->first;

	tam = listsize(l);
	char* string = (char*) malloc((tam+1)*sizeof(char));
	for(i = (tam-1); aux != NULL; i--)
	{
		string[i] = aux->c;
		aux = aux->next;
	}
	string[tam] = '\0';

	return string;
}

char removenode(List* l)
{
	char c;
	if(l->first != NULL)
	{
		NodeList* aux;

		aux = l->first;
		l->first = aux->next;
		aux->next = NULL;
		c = aux->c;
		l->tam--;

		free(aux);
	}
	else
	{
		c = 'e';
	}

	return c;
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
