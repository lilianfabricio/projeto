#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"
#include "huffnode.h"
#include "lista.h"
#include <string.h>
#include <openssl/md5.h>


#define MAX 256
#define MAX_FILE 20
#define MAX_EXT 6
#define MAX_KEY 20

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
void md5(const unsigned char *senha)
{
   //supondo que a senha seja huffman
   const char tentativa[100];
   printf("Digite a senha para descompactar o arquivo: ");
   scanf("%s", tentativa);
   int i;
   /*MD5_DIGEST_LENGTH é 16, no caso 16 bytes em decimal. No entanto, como geralmente 
   a hash md5 é salva em 32 bits hexa, no arquivo são salvos os 32 bytes*/
   unsigned char result[MD5_DIGEST_LENGTH];

   //A funçao cria o MD5 a partir da string e salva em result

   MD5(tentativa, strlen(tentativa), result);

  
   sprintf(tentativa, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", result[0],result[1],result[2],result[3],result[4],result[5],result[6],result[7],result[8],result[9],result[10],result[11],result[12],result[13],result[14],result[15]);
   //printf("TENTATIVA: %s\n", tentativa);

   if(strcmp(tentativa, senha) == 0)
   {
      printf("Senha correta!\n");
   }  
   else
   {  
      printf("Senha incorreta.\n");
      exit(1);
   }
}

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

Huffman_tree* create_tree(unsigned char value, Huffman_tree *left, Huffman_tree *right)
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

Huffman_tree* add(Huffman_tree *ht, unsigned char *string)
{
     if(string[i] == '\\' && string[i+1] == '*')
     {
        i++;
        ht = create_tree(string[i], NULL, NULL);
        printf("%c", string[i]);
        i++;
        return ht;
     }
    else if(string[i] == '*')
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

FILE* compress()
{
    //Declaração das variáveis
    unsigned char *code, aux, aux2, nula;
    int lixo, tabela[MAX], i, j, k, count, key_size = 32;
    unsigned char nomeArquivo[MAX_FILE], nomeExtensao[MAX_EXT];
    FILE *arqE, *arqS;
    Node *raiz = NULL;
    HashHuff *hash = create_hash();

    //Zera todos os valores da tabela de frequência
    for (i = 0; i < MAX; i++)
    {
        tabela[i] = 0;
    }

    //Lê o nome do arquivo com a extensão
    printf("Nome do arquivo:\n");
    scanf("%s", nomeArquivo);

    /*Verifica se foi inserido uma entrada valida (menos de 19 caracteres)
     * Se sim salva a posição do ponto e verifica se a extensao tem menos do que 6 caracteres
     */
    for(i = 0; nomeArquivo[i] != '.' && nomeArquivo[i] != '\0';)
    {
        i++;
    }
    if(nomeArquivo[i] == '\0') //Chegou ao fnal sem achar ponto
    {
        printf("\aEntrada inválida!\n");
        system("PAUSE");
        exit(0);
    }
    else
    {
        j = i; //salva a posição do ponto
        i++; // pula o ponto
        for(k = 0; nomeArquivo[i] != '\0' && nomeArquivo[i] != '\n'; i++, k++)
        {
            nomeExtensao[k] = nomeArquivo[i];
        }
        nomeExtensao[k] = '\0';
        if(k > 6) // extensão maior q a permitida
        {
            printf("\aExtensao inválida!\n");
            system("PAUSE");
            exit(0);
        }
    }

    //Abre o arquivo para leitura; se não for possível uma mensagem de erro é acionada e o programa para
    arqE = fopen(nomeArquivo, "rb");
    if(arqE == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        system("PAUSE");
        exit(0);
    }

    /*Lê caracter por caracter e incrementa sua frequencia na tabela também conta
     * quantos unsigneds chars tem no arquivo
     */
    count = 0;
    while(!feof(arqE))
    {
        aux = fgetc(arqE);
        tabela[aux]++;
        count++;
    }
    tabela[aux]--; //Corrige a interferência do EOF

    //Cria a fila de prioridade e insere os caracteres com suas respectivas frequências
    Priority_Queue *pq = create_priority_queue();
    for( i = 0; i < MAX; i++)
    {
        if(tabela[i] > 0)
        {
            Node *new_node = create_node((unsigned char)i, tabela[i]);
            enqueue_sorted(pq, new_node);
        }
    }

    //Cria a árvore
    raiz = build_tree(pq);

    //Declara e inicializa uma variável com o tamanho da árvore e uma lista q irá ser usada na hash
    int tamArvore = tree_size(raiz);
    List* listacod = createlist();

    getcode(hash, raiz, listacod);

    //Cria o arquivo de saída
    arqS = fopen("compressed.huff", "w+");

    //Verifica o tamanho da árvore: se ela for maior que 255, o primeiro byte também será usado
    if(tamArvore <= 255)
    {
        fprintf(arqS, "%c%c", 0, tamArvore);
    }
    else
    {
        fprintf(arqS, "%c%c", (tamArvore - 255), 255);
        printf("%c%c\n", (tamArvore - 255), 255);
    }
    print_tree_pre_order(raiz, arqS); //Imprime a árvore no arquivo

    //Escreve o tamanho da extensão no arquivo
    aux = k << 5;
    fprintf(arqS, "%c", aux);
    fputs(nomeExtensao, arqS);

    //Coloca o \0 do final do nome do arquivo no lugar certo
    nomeArquivo[j] = '\0';
    fprintf(arqS, "%c", j); // Escrevendo o char correspondente ao tamanho do nome do arquivo
    fputs(nomeArquivo, arqS);

    //Volta o ponteiro para reler o arquivo e seta os bits de nula para 0 e reseta j
    rewind(arqE);
    nula = 0;
    j = 7;
    while(count != 1) //contador de caracteres só vai até 1 devido ao EOF que é somado
    {
        aux = fgetc(arqE);
        code = get(hash, aux); //pega os novos bits da hash
        for(i = 0; code[i] == '1' || code[i] == '0'; i++, j--)
        {
            if(j == -1) // quando a variável nula está "cheia" printa e reseta nula e j
            {
                fprintf(arqS, "%c", nula);
                nula = 0;
                j = 8;
                i--;
            }
            else if(code[i] == '1') // só seta se for 1, se não for só continua
            {
                nula = set_bit(nula, j);
            }
        }
        count--;
    }
    fprintf(arqS, "%c", nula);

    lixo = j;
    if(lixo == 0 || lixo == -1) // não tem lixo
    {
        printf("Compactado com sucesso\n");

        fclose(arqE);
        return arqS;
    }
    else
    {
        rewind(arqS);
        fscanf(arqS, "%c", &aux2);
        lixo = lixo << 5;
        aux2 = aux2 | lixo;
        rewind(arqS);
        fprintf(arqS, "%c", aux2);

        printf("Compactado com sucesso\n");

        fclose(arqE);
        return arqS;
    }
}

void decompress() 
{

    FILE *compressed;
    unsigned char *buffer, aux1, aux2[3];
    size_t result;
    unsigned aux[14];
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
    
    //printf("LIXO: %d TAMANHO ARVORE: %d\n", trashSize, size);  

    unsigned char tree[size+1]; 
    tree[size+1] = '\0';
    fread(&tree, sizeof(char), size, compressed);
    i = 0;
    ht = add(ht, tree);
    //printf("TREE: %s\n", tree);


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

    tamanho_senha = 32;   

    char extensao[tam_nome_ext], senha[33];

    //Aqui pegamos qual é a extensão do arquivo
    for(r = 0, y = (3 + size); r < tam_nome_ext; r++, y++)
    {
        extensao[r] = buffer[y];
    }
    extensao[r] = '\0';
    //printf("EXTENSAO: %s\n", extensao);

    //Pegando a senha:

    for(r = 0, y = (3 + size + tam_nome_ext); r < 32; r++, y++)
    {
        
        senha[r] = buffer[y];
    }
    senha[r] = '\0';
    //printf("SENHA: %s\n", senha);
    md5(senha);
    
    //Y é onde esta localizado o byte (no buffer) que possui o tamanho do nome do arquivo.
    y = 35 + size + tam_nome_ext;
    int tam_nome_arq = buffer[y];    
    //printf("TAMANHO DO NOME: %d\n", tam_nome_arq);
    y++;

    //Aqui pegamos o nome do arquivo original
    unsigned char nome_arquivo[tam_nome_arq];
    for(r = y, p = 0; p < tam_nome_arq; r++, y++, p++)
    {
        nome_arquivo[p] = buffer[y];
    }
    nome_arquivo[p] = '\0';
    //printf("NOME ARQUIVO: %s\n", nome_arquivo);

    //Aqui pegamos as coordenadas da descompressao.
    //36 = 2 bytes (lixo + tamanho arvore) + arvore + tamanho do nome da ext + tamanho do nome.    
    coordenadas = tamanho_total - (36 + size + tam_nome_ext + tam_nome_arq);

    unsigned char *array_resto;

    array_resto = (unsigned char*) malloc (sizeof(unsigned char)*coordenadas); 

    for(int r = 0, o = (4 + size + tam_nome_ext + tamanho_senha + tam_nome_arq); r < coordenadas; r++, o++)
    {
        array_resto[r] = buffer[o];
    }
    //printf("TAMANHO EXTENSAO: %d, TAMANHO TOTAL: %d, COORDENADAS: %d\n", tam_nome_ext, tamanho_total, coordenadas);
    
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
    unsigned char nome_final[tam_nome_arq + tam_nome_ext];
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
    //printf("NOME FINAL: %s\n", nome_final);


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
int main()
{
    int opcao;
    printf("\aSeja bem-vindo ao GJVL2 D-Compress!\nEscolha a opcao desejada:\n1. Compactacao\n2. Descompactacao\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
        case 1:
            FILE *arquivo, *temporario;
            unsigned char senha[MAX_KEY], byte;
            int contador, tamArvore;
            
            for(contador = 0; contador < 3; contador++)
            {
                arquivo = compress();
            }
            temporario = tmpfile();
            
            //Lê a senha para compactar o arquivo
            printf("Por favor, digite uma senha para compactar o arquivo\n");
            scanf("%s", senha);
            
            // Imprime a senha no formato md5, no arquivo comprimido
            unsigned char result[MD5_DIGEST_LENGTH];
            MD5(senha, strlen(senha), result);
            for(i = 0; i < MD5_DIGEST_LENGTH; i++)
            {
                fprintf(temporario, "%02x", result[i]);
            }
            
            rewind(arquivo);
            byte =
            
            break;
        case 2:
            decompress();
            break;
        default:
            printf("Opcao Invalida\n");
    }
    return 0;
}
