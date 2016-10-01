/*
 * Hash.c
 *
 *  Created on: 26 de set de 2016
 *      Author: vitor_000
 */

#ifndef HASH_C_
#define HASH_C_

#include "hash.h"

#define MAX_HASH 256
#define MAX_CODE 148

typedef struct element
{
	unsigned char value;
	unsigned char *code;
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
	return ht->table[(key % MAX_HASH)]->code;
}

void put(HashHuff *ht, unsigned char key, unsigned char *val)
{	
	int h, i, count;
	h = key % MAX_HASH;

	for(i = 0; val[i] == '0' || val[i] == '1'; i++)
	{
		printf("%c\n", val[i]);
	}
	
	/*i = 0;
	ht->table[h]->value = key;
	while(val[i] == '1' || val[i] == '0')
	{
		i++;
	}
	
	ht->table[h]->code = malloc(i*sizeof(unsigned char));
	
	for(i = 0; val[i] == '1' || val[i] == '0'; i++)
	{
		ht->table[h]->code[i] = val[i];
	}
	ht->table[h]->code[i] = '\0';*/
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
