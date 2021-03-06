/*
 * hash.c
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */

#ifndef HASH_C_
#define HASH_C_

#include "hash.h"
#include "lista.h"

#define MAX_HASH 256
#define MAX_CODE 148

typedef struct element
{
	unsigned char value;
	unsigned char* code;
}Element;

typedef struct hash
{
	Element* table[MAX_HASH];
}HashHuff;

HashHuff* create_hash()
{
	HashHuff *ht = (HashHuff*) malloc(sizeof(HashHuff));
	int i;

	for(i = 0; i < MAX_HASH; i++)
	{
		ht->table[i] = NULL;
	}

	return ht;
}

unsigned char* get(HashHuff *ht, unsigned char key)
{
	return ht->table[key]->code;
}

void put(HashHuff *ht, unsigned char key, List* l)
{
	int tam, h;
	Element* new_e = (Element*) malloc(sizeof(Element));

	h = key % MAX_HASH;
	new_e->value = key;

	tam = listsize(l);

	new_e->code = getstring(l);

	ht->table[h] = new_e;
}

void print_hash(HashHuff *h)
{
	int i;
	for(i = 0; i < MAX_HASH; i++)
	{
		if(h->table[i] != NULL)
		{
			printf("%c\n", h->table[i]->value);
			printf("%s\n", h->table[i]->code);
		}
	}
}

#endif /* HASH_C_ */
