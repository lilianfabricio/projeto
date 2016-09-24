#include <stdio.h>
#include <stdlib.h>
#include <math.h>
char tree[20];
int i;

int binary_decimal(long int binary)
{
    int decimal = 0, i = 0, aux;
    while (binary != 0)
    {
        aux = (binary % 10);
        binary /= 10;
        decimal += aux * (i*i);
        i++;
    }
    return decimal;
}
int is_bit_i_set(unsigned char c, int i)
{

	unsigned char mask = 1 << i;
	return mask & c;
}

struct tree
{
    char letter;
    struct tree *left;
    struct tree *right;
};

typedef struct tree Huffman_tree;

Huffman_tree* create_empty()
{
    return NULL;
}
int is_empty(Huffman_tree *ht)
{
    return(ht == NULL);
}

Huffman_tree* create_tree(char value, Huffman_tree *left, Huffman_tree *right)
{
    Huffman_tree *ht = (Huffman_tree*)malloc(sizeof(Huffman_tree));
    ht -> letter = value;
    ht -> left = left;
    ht -> right = right;
    return ht;
}

void print_pre_order(Huffman_tree *ht)
{
    if (!is_empty(ht))
    {
        printf("%c ", ht->letter);
        print_pre_order(ht->left);
        print_pre_order(ht->right);
    }
}

Huffman_tree* add(Huffman_tree *ht)
{

    if(tree[i] == '*')
    {
        ht = create_tree(tree[i], NULL, NULL);
        i++;
        ht -> left = add(ht -> left);
        ht -> right = add(ht -> right);
    }
    else
    {
        ht = create_tree(tree[i], NULL, NULL);
        i++;
        return ht;
    }
    return ht;
}

int main () 
{

	//Criar um arquivo formato FILE que vai receber o arquivo comprimido
	FILE *compressed;
	long lSize;
	unsigned char *buffer, aux1, aux2[2], aux5, aux6 = 255, aux7, auxx[14];
	//O buffer vai armazenar o arquivo temporariamente em formato de string 
	size_t result;
	char aux[14];
	int garbage, tree_size, size = 0;
	int trashSize, treeSize, aux3, aux4, j;
	Huffman_tree *ht = create_empty();

	// Abre o arquivo 'compressed.huff' em forma de binario (rb)
	compressed = fopen ("compressed.huff", "rb");

	//Se o arquivo apontar para nulo, então ele estara vazio.
	if (compressed == NULL) 
	{
		printf("Não tem arquivo pra ser extraido!\n");
		exit (1);
	}

	//Aqui irá copiar o primeiro byte de "compressed" para o aux1
	/*(O ponteiro para o bloco de memoria com o tamanho do item, o tamanho de cada elemento, 
	o numero de elementos neste caso 1 byte, o arquivo de origem)*/
	fread (&aux1, sizeof(unsigned char), 1, compressed);	
	aux1 = aux1 >> 5;
	// shift bit para a direita: Aqui pegamos o tamanho do lixo
	trashSize = aux1;
	//O arquivo agora aponta para deu inicio
	rewind (compressed);

	//Aqui vai copiar os dois primeiros bytes para o aux2
	/*(O ponteiro para o bloco de memoria onde ficara, o tamanho de cada elemento, 
	o numero de elementos neste caso 2 bytes, o arquivo de origem)*/
	fread (&aux2, sizeof(unsigned char), 2, compressed);
	//Aqui é o tamanho da arvore
	aux2[0] = aux2[0];
	for(int k = 8, h = 0; h < 5; h++, k++)
	{


		if(is_bit_i_set(aux2[0], h))
		{
			size = size + pow(2, k);
		}
	}
	size = size + (aux2[1]);
	
	printf("LIXO: %d TAMANHO ARvORE: %d\n", trashSize, size);
	//Isso faz com que "tire" os tres primeiros bits do byte que contem o tamanho do lixo

	aux3 = aux2[0];
	aux4 = aux2[1];
	printf("AUX4: %d\n", aux4);
	//Esse pega o resto do tamanho da arvore, ou seja, o proximo byte	
	

	char tree[11];
	fread(&tree, sizeof(char), 11, compressed);
	printf("%s\n", tree);


	// Obtem o tamanho do arquivo indo do byte do inicio do arquivo até o ultimo
	fseek (compressed , 0 , SEEK_END);
	//ftell: Retorna o numero de bytes a partir do inicio do arquivo em arquivos binarios
	lSize = ftell(compressed);
	// Define o arquivo para o inicio do arquivo
	rewind(compressed);

	// Aloca memoria do tamanho do arquivo para criar o buffer
	buffer = (char*) malloc (sizeof(unsigned char)*lSize);
	if (buffer == NULL)
	{
		printf("Erro de memoria\n"); 
		exit (2);
	}

	//Copia o arquivo para o buffer
	/*(O ponteiro para o bloco de memoria com o tamanho do arquivo, o tamanho em binario de cada elemento, 
	o numero de elementos, o arquivo de origem)*/
	result = fread (buffer, 1, lSize, compressed);
	/*Result é o tamanho de arquivos lidos com sucesso. Se o numero de arquivos lidos com sucesso for diferente 
	do tamanho da string, ocorreu um erro na leitura */
	if (result != lSize) 
	{
		fputs ("Erro de leitura\n",stderr); 
		exit (3);
	}

	//Here we catch the garbage size:
	for(i = 0; i < 3; i++)
	{
		aux[i] = buffer[i];
	}
	aux[3] = '\0';
	garbage = atoi(aux);
	garbage = binary_decimal(garbage);
	printf("%d\n", garbage);


	//Here we find the tree size
	for(i = 3, j = 0; i < 16; i++, j++)
	{
		aux[j] = buffer[i];
	}

	aux[16] = '\0';
	tree_size = atoi(aux);
	tree_size = binary_decimal(tree_size);
	printf("%d\n", tree_size);
	
	//Here we find the tree itself
	for(i = 16, j = 0; i < (16 + tree_size); i++, j++)
	{
		tree[j] = buffer[i];
	}
	tree[j] = '\0';
    printf("%s\n", tree);
    i = 0;
    ht = add(ht);
    print_pre_order(ht);

    fclose (compressed);
    free (buffer);
    return 0;
}