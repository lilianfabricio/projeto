#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int i;
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

int is_leaf(Huffman_tree *ht)
{
    return (ht->left == NULL && ht->right == NULL);
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
        printf("%c", ht->letter);
        print_pre_order(ht->left);
        print_pre_order(ht->right);
    }
}
void print_post_order(Huffman_tree *ht)
{
    if (!is_empty(ht)) 
    {
        print_post_order(ht->left);
        print_post_order(ht->right);
        printf("%c", ht->letter);
    }
}

Huffman_tree* add(Huffman_tree *ht, char *string)
{
    if(string[i] == '*')
    {
        ht = create_tree(string[i], NULL, NULL);
        i++;
        ht -> left = add(ht -> left, string);
        ht -> right = add(ht -> right, string);

    }
    else
    {
        ht = create_tree(string[i], NULL, NULL);
        i++;
 
        return ht;
    }
    return ht;
}

void decompress() 
{

    FILE *compressed;
    unsigned char *buffer, aux1, aux2[2];
    size_t result;
    char aux[14];
    int size = 0, coordenadas, trashSize, aux3, aux4, k, z, tamanho_total;
    Huffman_tree *ht = create_empty();
    compressed = fopen ("compressed.huff", "rb");
    if (compressed == NULL) 
    {
        printf("Não tem arquivo pra ser extraido!\n");
        exit (1);
    }
    fread (&aux1, sizeof(unsigned char), 1, compressed);    
    aux1 = aux1 >> 5;
    trashSize = aux1;
    rewind (compressed);

    fread (&aux2, sizeof(unsigned char), 2, compressed);
    for(int u = 8, h = 0; h < 5; h++, u++)
    {
        if(is_bit_i_set(aux2[0], h))
        {
            size = size + pow(2, u);
        }
    }
    size = size + (aux2[1]);
    
    printf("LIXO: %d TAMANHO ARVORE: %d\n", trashSize, size);  
    char tree[size]; 
    fread(&tree, sizeof(char), size, compressed);
    i = 0;
    ht = add(ht, tree);
    fseek (compressed, 0, SEEK_END);
    tamanho_total = ftell(compressed);
    rewind(compressed);
    coordenadas = tamanho_total - (2 + size);
    unsigned char *array_resto;
    array_resto = (unsigned char*) malloc (sizeof(unsigned char)*coordenadas);
    buffer = (unsigned char*) malloc (sizeof(unsigned char)*tamanho_total);
    fread (buffer, 1, tamanho_total, compressed);
    for(int r = 0, o = (2 + size); r < coordenadas; r++, o++)
    {
        array_resto[r] = buffer[o];
    }

    int binario[coordenadas * 8];
    unsigned char a;
    k = 0;

    for(i = 0; i < coordenadas; i++)
    {
        a = array_resto[i];
        for (z = 0; z < 8; z++, k++) 
        {
            binario[k] = !!((a << z) & 0x80);
        }
    }
   
    k = k - trashSize;
    free(buffer);
    free(array_resto);

    Huffman_tree *auxt = ht;
    FILE *arq = fopen("decompressed.txt", "wt");

    for(i = 0; i < k ; i++)
    {
        if(binario[i] == 0)
        {
            auxt = auxt->left;
        }
        else
        {
            auxt = auxt->right;
        }
        if(is_leaf(auxt))
        {
            fprintf(arq,"%c",  auxt->letter);
            auxt = ht;
        }
    }   
    printf("Done\n");
    fclose(arq);
    fclose (compressed);
    
}
int main()
{
    /*int opcao;
    printf("\aSeja bem-vindo ao GJVL2 D-Compress!\nEscolha a opcao desejada:\n1. Compactacao\n2. Descompactacao\n");
    scanf("%d", opcao);*/
    decompress();
    /*switch (opcao)
    {
        case 1:
            compress();
            break;
        case 2:
            decompress();
            break;
        default:
            printf("Opção Inválida\n");
    }*/
    return 0;
}