#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"
#include "huffnode.h"
#include "lista.h"

#define MAX 256
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

int isleaf(Huffman_tree *ht)
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

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}

void compress()
{
    FILE *arqE, *arqS;
    char aux;
    unsigned char aux2, nula;
    int lixo;
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
        fscanf(arqE, "%c", &aux);
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

    arqS = fopen("compressed.huff", "w+");
    root = build_tree(pq);
    print_tree_pre_order(root, arqS);

    rewind(arqS);

    int size = tree_size(root);
    unsigned char tree[size];
    List* listacod = createlist();

    for(i = 0; i < size; i++)
    {
        fscanf(arqS, "%c", &tree[i]);
    }
    tree[i] = '\0';
    getcode(hash, tree, listacod, '0');

    rewind(arqS);
    if(size < 255)
    {
        fprintf(arqS, "%c%c", 0, size);
    }
    else
    {
        fprintf(arqS, "%c%c", (size - 255), 255);
    }
    print_tree_pre_order(root, arqS);

    rewind(arqE);
    nula = 0;
    j = 7;
    while((aux = fgetc(arqE)) != EOF)
    {
        code = get(hash, aux);
        for(i = 0; code[i] == '1' || code[i] == '0'; i++, j--)
        {
            if(j == -1)
            {
                fprintf(arqS, "%c", nula);
                nula = 0;
                j = 8;
                i--;
            }
            else if(code[i] == '1')
            {
                nula = set_bit(nula, j);
            }
        }
    }
    fprintf(arqS, "%c", nula);

    lixo = j;
    printf("%d\n", lixo);
    fclose(arqS);
    if(lixo == 0 || lixo == -1)
    {
        fclose(arqS);
    }
    else
    {
        arqS = fopen("compressed.huff", "r+");
        fscanf(arqS, "%c", &aux2);
        fclose(arqS);
        if(lixo >= 4)
        {
            aux2 = set_bit(aux2, 7);
            if((lixo % 2) != 0)
            {
                aux2 = set_bit(aux2, 5);
            }
            if(lixo  == 6 || lixo == 7)
            {
                aux2 = set_bit(aux2, 6);
            }
        }
        else
        {
            if(lixo == 1 || lixo == 3)
            {
                aux2 = set_bit(aux2, 5);
            }
            if(lixo == 3 || lixo == 2)
            {
                aux2 = set_bit(aux2, 6);
            }
        }
        printf("%c\n", aux2);
        arqS = fopen("compressed.huff", "w+");
        fprintf(arqS, "%c", aux2);

        fclose(arqS);
    }

    fclose(arqS);
    fclose(arqE);
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
    
    //printf("LIXO: %d TAMANHO ARVORE: %d\n", trashSize, size);  
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
        if(isleaf(auxt))
        {
            fprintf(arq,"%c",  auxt->letter);
            auxt = ht;
        }
    }   
    printf("Descompactado com sucesso!\n");
    fclose(arq);
    fclose (compressed);
    
}
int main()
{
    int opcao;
    printf("\aSeja bem-vindo ao GJVL2 D-Compress!\nEscolha a opcao desejada:\n1. Compactacao\n2. Descompactacao\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
        case 1:
            compress();
            break;
        case 2:
            decompress();
            break;
        default:
            printf("Opção Inválida\n");
    }
    return 0;
}