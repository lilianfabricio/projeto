/*
 * lista.c
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */
#ifndef LISTA_C_
#define LISTA_C_

#include "lista.h"

typedef struct node_list
{
	unsigned char c;
	NodeList* next;
}NodeList;

typedef struct list
{
	NodeList* first;
	int tam;
}List;

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

unsigned char* getstring(List* l)
{
	int i, tam;
	NodeList* aux = l->first;

	tam = listsize(l);
	unsigned char* string = (unsigned char*) malloc((tam+1)*sizeof(unsigned char));
	for(i = (tam-1); aux != NULL; i--)
	{
		string[i] = aux->c;
		aux = aux->next;
	}
	string[tam] = '\0';

	return string;
}

void removenode(List* l)
{
	if(l->first != NULL)
	{
		NodeList* aux;

		aux = l->first;
		l->first = aux->next;
		aux->next = NULL;
		l->tam--;

		free(aux);
	}
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
