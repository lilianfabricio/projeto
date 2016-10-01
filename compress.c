/*
 * main.c
 *
 *  Created on: 30 de set de 2016
 *      Author: vitor_000
 */

#include "hash.h"
#include "huffnode.h"

#define MAX 256

int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}

int set_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask | c;
}

int main()
{
	FILE *arqE, *arqS, *arq;
	unsigned char aux, nula, lixo;
	unsigned char *code;
	int tabela[MAX], i = 0, j;
	Node *root = NULL;
	HashHuff *hash = create_hash();

	arqE = fopen("entrada.txt", "r");
	for (i = 0; i < MAX; i++)
	{
		tabela[i] = 0;
	}

	if(arqE == NULL)
	{
        printf("Erro na abertura do arquivo.\n");
        system("PAUSE");
        exit(0);
    	}
	while(!feof(arqE))
	{
		fscanf(arqE,"%c", &aux);
		tabela[aux]++;
	}
	tabela[aux]--;

	Priority_Queue *pq = create_priority_queue();
	for( i = 0; i < MAX; i++)
	{
		if(tabela[i] > 0)
		{
			Node *new_node = create_node((char)i, tabela[i]);
			enqueue_sorted(pq, new_node);
		}
	}

	arq = fopen("compressed.huff", "w+");
	root = build_tree(pq);
	print_tree_pre_order(root, arq);

	int size = tree_size(root);
	unsigned char code1[size/2], tree[size];
	fscanf(arq, "%s", tree);
	puts(tree);
	
	/*funcao(hash, tree, code1);

	print_hash(hash);

	rewind(arqE);
	arqS = fopen("compressed.huff", "w+");
	if(size < 255)
	{
		fprintf(arqS, "%c%c", 0, 255);
	}
	else
	{
		fprintf(arqS, "%c%c", (size - 255), 255);
	}
	print_tree_pre_order(root, arqS);

	while(feof(arqE))
	{
		fscanf(arqE, "%c", &aux);
		code = get(hash, aux);
		for(nula = 0, i = 0, j = 8; code[i] == '1' || code[i] == '0'; i++, j--)
		{
			if(j == 0)
			{
				fprintf(arqS, "%c", nula);
				nula = 0;
				j = 9;
				i--;
			}
			else
			{
				nula = set_bit(nula, j);
			}
		}
	}
	if(j == 8 || j == 9)
	{
		fclose(arqS);
	}
	else
	{
		rewind(arqS);
		fscanf(arqS, "%c", &aux);

		lixo = 8 - j;
		for(i = 0, j = 6; i <= 2; i++, j++)
		{
			if(is_bit_i_set(lixo, i))
			{
				set_bit(aux, j);
			}
		}

		fclose(arqS);
	}*/

    fclose(arqE);

	return 0;
}
