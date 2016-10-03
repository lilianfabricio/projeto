
void decompress() 
{

    FILE *compressed;
    unsigned char *buffer, aux1, aux2[3];
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
    char tree[size+1]; 
    tree[size+1] = '\0';
    fread(&tree, sizeof(char), size+1, compressed);
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
   
    k = k - trashSize - 1;
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