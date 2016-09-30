/*
 * Hash.h
 *
 *  Created on: 26 de set de 2016
 *      Author: vitor_000
 */

#ifndef HASH_H_
#define HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASH 256
#define MAX_CODE 148

typedef struct element Element;

typedef struct hash HashHuff;

HashHuff* create_hash();

unsigned char* get(HashHuff *ht, unsigned char key);

void put(HashHuff *ht, unsigned char key, unsigned char *val);

#endif /* HASH_H_ */
