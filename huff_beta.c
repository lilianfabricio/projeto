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

    FILE *compressed;
    long lSize;
    char *buffer;
    size_t result;
    char aux[14];
    int garbage, tree_size;
    int j;
    Huffman_tree *ht = create_empty();

    // Here the file is open
    compressed = fopen ("compressed.huff", "rb");

    if (compressed == NULL)
    {
        printf("Não tem arquivo pra ser extraido!\n");
        exit (1);
    }

    //Analizar essa parte e ver o q faz
    // obtain file size:
    fseek (compressed, 0, SEEK_END);
    lSize = ftell(compressed);
    rewind(compressed);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL)
    {
        printf("Memory error\n");
        exit (2);
    }

    // copy the file into the buffer:
    result = fread (buffer, 1, lSize, compressed);
    if (result != lSize)
    {
        fputs ("Reading error",stderr);
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
    for( i = 3, j = 0; i < 16; i++, j++)
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
