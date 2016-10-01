#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int i;
int is_bit_i_set(unsigned char c, int i)
{
    //Isso verifica se o bit é 1 ou 0
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

int main () 
{

    //Criar um arquivo formato FILE que vai receber o arquivo comprimido
    FILE *compressed;
    //unsigned porque nao tem o bit do sinal
    unsigned char *buffer, aux1, aux2[2];
    //O buffer vai armazenar o arquivo temporariamente em formato de string 
    size_t result;
    char aux[14];
    int size = 0, coordenadas, trashSize, aux3, aux4, k, z, tamanho_total;

    //Cria a estrutura da arvore
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
   
    //No primeiro, vai olhar da posiçao |0|1|2|->3|4|5|6|7|8| até a posiçao 0|1|2|3|4|5|6|7|8 <-| se esta setado o bit
    for(int u = 8, h = 0; h < 5; h++, u++)
    {
        /* Primeiro a funçao verifica se o bit esta "setado", se estiver, vai somar 2^(sua posiçao), 
        como em uma conversao de binario qualquer para decimal */
        if(is_bit_i_set(aux2[0], h))
        {
            size = size + pow(2, u);
        }
    }
    // Soma o valor acumulado do looping, e o valor do segundo byte
    size = size + (aux2[1]);
    
    printf("LIXO: %d TAMANHO ARVORE: %d\n", trashSize, size);  
    char tree[size]; 
    /*Criamos a string que vai pegar a arvore e dai copiamos o arquivo a partir do segundo byte, que é onde o programa
    esta apontando agora no arquivo */
    fread(&tree, sizeof(char), size, compressed);
    printf("ARVORE: \n");

    //Aqui é onde a string é enviada para a funçao que vai adicionar os caracteres a arvore     
    i = 0;
    //Enviamos o ponteiro que aponta para a raiz da arvore e a string "tree", que contem os caracteres da arvore    
    ht = add(ht, tree);
    print_pre_order(ht);
    printf("\n");


    fseek (compressed, 0, SEEK_END);
    //A funçao ftell retorna o tamanho total em bytes do inicio do arquivo até o fim
    tamanho_total = ftell(compressed);
    //A funçao rewind faz o arquivo voltar a apontar para seu inicio
    rewind(compressed);
    //Coordenadas é o numero de bytes a partir do fim da arvore, ou seja, as "coordenadas" da descompressão
    coordenadas = tamanho_total - (2 + size);
    //String que contem as "coordenadas"
    unsigned char *array_resto;
    array_resto = (unsigned char*) malloc (sizeof(unsigned char)*coordenadas);

    //O buffer é uma estrutura que armazena temporariamente o arquivo inteiro para facil manipulaçao 
    buffer = (unsigned char*) malloc (sizeof(unsigned char)*tamanho_total);
    /*Copia todo o arquivo para o buffer, e a funçao tem como paramentro: 
    (O local onde esta alocada memoria para o buffer, o tamanho da copia por vez ou seja 1 byte, o tamanho total em bytes
    do arquivo de origem e o arquivo de origem*/
    fread (buffer, 1, tamanho_total, compressed);
    //É uma simples copia, das coordenadas que estao no buffer para uma string 
    for(int r = 0, o = (2 + size); r < coordenadas; r++, o++)
    {
        array_resto[r] = buffer[o];
    }


    for(int r = 0; r < coordenadas; r++)
    {
        printf("%c ", array_resto[r]);
    }
    printf("\n");


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
    k = (k - trashSize);
    printf("%d\n", k);

    for ( i = 0; i < k ; i++)
    {
        printf("%d", binario[i]);
    }
    printf("\n");
    
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
        else{
            auxt = auxt->right;
        }
        if(is_leaf(auxt))
        {
            printf("%c", auxt->letter);
            fprintf(arq,"%c",  auxt->letter);
            auxt = ht;
        }
    }   

    printf("\n"); 
    fclose(arq);

    //Fechamos o arquivo comprimido aqui
    fclose (compressed);
    return 0;
}