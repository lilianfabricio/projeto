/*
 * decompress.h
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */

#ifndef DECOMPRESS_H_
#define DECOMPRESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"
#include "huffnode.h"
#include "lista.h"
#include "compress.h"

typedef struct tree Huffman_tree;

int is_empty(Huffman_tree *ht);

int isleaf(Huffman_tree *ht);

Huffman_tree* create_empty();

Huffman_tree* create_tree(unsigned char value, Huffman_tree *left, Huffman_tree *right);

void print_pre_order(Huffman_tree *ht);

void print_post_order(Huffman_tree *ht);

Huffman_tree* add(Huffman_tree *ht, unsigned char *string);

void decompress();

#endif /* DECOMPRESS_H_ */
