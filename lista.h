/*
 * lista.h
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */

#ifndef LISTA_H_
#define LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_list NodeList;

typedef struct list List;

List* createlist();

void insertnode(List* l, unsigned char c);

int listsize(List* list);

unsigned char* getstring(List* l);

void removenode(List* l);

void printlist(List* l);

#endif /* LISTA_H_ */
