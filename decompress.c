/*
 * decompress.c
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */

#ifndef DECOMPRESS_C_
#define DECOMPRESS_C_

#include "compress.h"
#include "decompress.h"

int i;

typedef struct tree
{
    unsigned char letter;
    struct tree *left;
    struct tree *right;
}Huffman_tree;

// Função is_empty: Retorna V se a árvore estiver vazia e F se não estiver
int is_empty(Huffman_tree *ht)
{
    return(ht == NULL);
}

// Funcão isleaf: Retorna V se o nó passado for uma folha e F se não for
int isleaf(Huffman_tree *ht)
{
    return (ht->left == NULL && ht->right == NULL);
}

// Função create_empty: Cria uma árvore nula
Huffman_tree* create_empty()
{
    return NULL;
}

/* Função create_tree: Cria um nó raiz. Recebe o valor a ser armazenado na raiz e
 * os ponteiros para as árvores da direita e da esquerda */
Huffman_tree* create_tree(unsigned char value, Huffman_tree *left, Huffman_tree *right)
{
    Huffman_tree *ht = (Huffman_tree*)malloc(sizeof(Huffman_tree));
    ht -> letter = value;
    ht -> left = left;
    ht -> right = right;
    return ht;
}

// Função print_pre_order: Imprime a árvore em pre-ordem (função recursiva)
void print_pre_order(Huffman_tree *ht)
{
    if (!is_empty(ht))
    {
        printf("%c", ht->letter);
        print_pre_order(ht->left);
        print_pre_order(ht->right);
    }
}

// Função print_post_order: Imprime a árvore em pos-ordem (função recursiva)
void print_post_order(Huffman_tree *ht)
{
    if (!is_empty(ht))
    {
        print_post_order(ht->left);
        print_post_order(ht->right);
        printf("%c", ht->letter);
    }
}

/* Função add: Recebe um nó raiz e uma string e adiciona
 * os elementos da string na árvore (função recursiva) */
Huffman_tree* add(Huffman_tree *ht, unsigned char *string)
{
	/* o IF verifica se o caracter da posição atual é contrabarra,
	* se for passa para o próximo e verifica se é contrabarra novamente ou asterisco */
    if(string[i] == '\\' && (string[i+1] == '*' || string[i+1] == '\\'))
    {
    	i++;
        ht = create_tree(string[i], NULL, NULL);
        printf("%c", string[i]);
        i++;
    }
    else if(string[i] == '*') // caso não seja contrabarra e seja asterisco, é um nó raiz
    {
        ht = create_tree(string[i], NULL, NULL);
        i++;
        ht -> left = add(ht -> left, string);
        ht -> right = add(ht -> right, string);
    }
    else // caso seja uma letra
    {
        ht = create_tree(string[i], NULL, NULL);
        i++;
    }

    return ht;
}

void decompress()
{
	FILE *compressed;
    unsigned char *buffer, aux1, aux2[3];
    size_t result;
    char aux[14];
    int size = 0, coordenadas, trashSize, aux3, aux4, k, z, tamanho_total, tam_nome_ext, tamanho_senha, r, y, p;
    //Criamos uma arvore huffman vazia
    Huffman_tree *ht = create_empty();

    compressed = fopen ("compressed.huff", "rb");
    if (compressed == NULL) 
    {
        printf("Não tem arquivo pra ser extraido!\n");
        exit (1);
    }

    //Aqui foi lido o primeiro byte
    fread (&aux1, sizeof(unsigned char), 1, compressed);

    aux1 = aux1 >> 5;
    //Pegamos o tamanho do lixo, "setando" 5 bits para a direita
    trashSize = aux1;
    //O arquivo volta para o início
    rewind (compressed);
    //Lemos os dois proximos bytes, pra pegarmos o tamanho da arvore
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

    char tree[size+1]; 
    tree[size+1] = '\0';
    fread(&tree, sizeof(char), size+1, compressed);
    i = 0;
    ht = add(ht, tree);
    printf("TREE: %s\n", tree);


    fseek (compressed, 0, SEEK_END);
    tamanho_total = ftell(compressed);
    rewind(compressed);
    buffer = (unsigned char*) malloc (sizeof(unsigned char)*tamanho_total);
    fread (buffer, 1, tamanho_total, compressed);

    aux1 = buffer[2 + size];

    tam_nome_ext = aux1 >> 5;
    //Essa parte deve aparecer na interface grafica
    if(tam_nome_ext > 6)
    {
        printf("Não é possivel decompactar o arquivo informado.\n");
        exit(2);
    }


    //*******************************************************************
    tamanho_senha = 32;
    //*******************************************************************
    //SENHAAAAAAAAAAAAAAAA!!!!!!!
    

    char extensao[tam_nome_ext], senha[33];

    //Aqui pegamos qual é a extensão do arquivo
    for(r = 0, y = (3 + size); r < tam_nome_ext; r++, y++)
    {
        extensao[r] = buffer[y];
    }
    extensao[r] = '\0';
    printf("EXTENSAO: %s\n", extensao);

    //Pegando a senha:

    for(r = 0, y = (3 + size + tam_nome_ext); r < 32; r++, y++)
    {
        
        senha[r] = buffer[y];
    }
    senha[r] = '\0';
    printf("SENHA: %s\n", senha);
    
    //Y é onde esta localizado o byte (no buffer) que possui o tamanho do nome do arquivo.
    y = 35 + size + tam_nome_ext;
    int tam_nome_arq = buffer[y];    
    printf("TAMANHO DO NOME: %d\n", tam_nome_arq);
    y++;

    //Aqui pegamos o nome do arquivo original
    char nome_arquivo[tam_nome_arq];
    for(r = y, p = 0; p < tam_nome_arq; r++, y++, p++)
    {
        nome_arquivo[p] = buffer[y];
    }
    nome_arquivo[p] = '\0';
    printf("NOME ARQUIVO: %s\n", nome_arquivo);

    //Aqui pegamos as coordenadas da descompressao.
    //36 = 2 bytes (lixo + tamanho arvore) + arvore + tamanho do nome da ext + tamanho do nome.    
    coordenadas = tamanho_total - (36 + size + tam_nome_ext + tam_nome_arq);

    unsigned char *array_resto;

    array_resto = (unsigned char*) malloc (sizeof(unsigned char)*coordenadas); 

    for(int r = 0, o = (4 + size + tam_nome_ext + tamanho_senha + tam_nome_arq); r < coordenadas; r++, o++)
    {
        array_resto[r] = buffer[o];
    }
    printf("TAMANHO EXTENSAO: %d, TAMANHO TOTAL: %d, COORDENADAS: %d, TAMANHO SENHA: %d\n", tam_nome_ext, tamanho_total, coordenadas, tamanho_senha);
    
    //Aqui é o mesmo de antes 
    int binario[coordenadas * 8];
    unsigned char a;
    k = 0;

    //MUDAR ISSOOOOOOOO
    for(i = 0; i < coordenadas; i++)
    {
        a = array_resto[i];
        for (z = 0; z < 8; z++, k++) 
        {
            binario[k] = !!((a << z) & 0x80);
        }
    }
    k = k - trashSize - 1;
    free(buffer);
    free(array_resto);
    //Aqui juntamos o nome do arquivo original + a extensao original
    char nome_final[tam_nome_arq + tam_nome_ext];
    //Primeiro é o nome do arquivo original
    for(y = 0, p = 0; y < tam_nome_arq; y++, p++)
    {
        nome_final[y] = nome_arquivo[p];
    }
    nome_final[y] = '.';
    y++;
    //Agora é a extensao original
    for(y, p = 0; p < tam_nome_ext; y++, p++)
    {
        nome_final[y] = extensao[p];
    }
    nome_final[y] = '\0';
    printf("NOME FINAL: %s\n", nome_final);


    Huffman_tree *auxt = ht;

    //Nesse fopen, o nome_final é o nome do arquivo antigo, como ele era antes de ser compactado
    FILE *arq = fopen(nome_final, "wt");

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

#endif /* DECOMPRESS_C_ */
