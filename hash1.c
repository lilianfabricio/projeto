#include <stdio.h>
#include <stdlib.h>

#define HASH 11
/* Nossa hash só terá 10 keys */ 

struct elemento
{
	int key;
	int value;
	struct elemento *prox;
};

typedef struct elemento Elemento;

struct hashtable 
{
	/* É um array de ponteiros para Elementos */ 
	Elemento *table[HASH];
};

typedef struct hashtable Hashtable;

Hashtable* createHashtable()
{
  Hashtable *ht = (Hashtable*)malloc(sizeof(Hashtable));
  int i;
  for(i = 0; i < HASH; i++)
  {
    ht -> table[i] = NULL;
  }
  return ht;
}
 

void put(Hashtable *ht, int key, int value)
{
	/* Coloca um novo elemento na determinada key */
	int h = key % HASH;
	Elemento *new_element = (Elemento*)malloc(sizeof(Elemento));
	new_element -> key = h;
	new_element -> value = value;
	new_element -> prox = ht -> table[h];
	ht -> table[h] = new_element;
}

void print_key(Hashtable *ht, int key)
{
	int h = key % HASH;
	if(ht -> table[h] == NULL)
	{
		return;
	}
	else 
	{
		Elemento *current = (Elemento*)malloc(sizeof(Elemento));
		current = ht -> table[h];
		printf("Printing key number %d\n", h);
		while(current != NULL)
		{
			printf("%d ", current -> value);
			current = current -> prox;
		}
		printf("\n");
	}

}

void print_full_hash(Hashtable *ht)
{
	int h = 1;
	while(h < HASH)
	{
		print_key(ht, h);
		h++;
	}	
}

Elemento* remove_element(Elemento *first, int item)
{
	/* Essa parte é pra remover o nó da lista formada, ainda não sei fazer sem isso */ 
	Elemento *previous = NULL;
	Elemento *current = first;
	while(current != NULL && current->value != item)
	{
		previous = current;
		current = current -> prox;
	}
	if (current == NULL)
	{
		return first;
	}
	if (previous == NULL)
	{
		first = current -> prox;
	}
	/* O anterior passa a apontar para onde o atual estava apontando */ 
	else
	{
		previous -> prox = current -> prox;
	}
	/* "Free" limpa o espaço de memoria ocupado pela "capsula" */
	free(current);
	return first;
}

void remove_key(Hashtable *ht, int key, int value)
{
	Elemento* current, ant;
 	int h = key % HASH;
 	if (ht -> table[h] == NULL) 
 	{
 		printf("Não encontrado\n");
 		/*Se a chave dada estiver vazia, aborta o programa */
 	}
 	else
 	{
 		ht -> table[h] = remove_element(ht -> table[h], value);
 	} 	
}
