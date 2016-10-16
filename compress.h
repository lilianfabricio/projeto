/*
 * compress.h
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */

#ifndef COMPRESS_H_
#define COMPRESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "huffnode.h"
#include "lista.h"

int is_bit_i_set(unsigned char c, int i);

unsigned char set_bit(unsigned char c, int i);

void compress();

#endif /* COMPRESS_H_ */
