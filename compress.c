/*
 * compress.c
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */

#ifndef COMPRESS_C_
#define COMPRESS_C_

#include "compress.h"

#define MAX 256
#define MAX_FILE 20
#define MAX_EXT 6

// Retorna um inteiro indicando se o bit está setado ou não
int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

//Retorna o inteiro recebido como parâmetro com o bit i setado
unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}

void compress()
{
	//Declaração das variáveis
    unsigned char *code, aux, aux2, nula;
    int lixo, tabela[MAX], i, j, k, count;
    char nomeArquivo[MAX_FILE], nomeExtensao[MAX_EXT];
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

    //SENHAAAAAAAAAAAAA!!!!!!!!!

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
        fclose(arqS);
    }
    else
    {
        rewind(arqS);
        fscanf(arqS, "%c", &aux2);
        lixo = lixo << 5;
        aux2 = aux2 | lixo;
        rewind(arqS);
        fprintf(arqS, "%c", aux2);

        fclose(arqS);
    }

    printf("Compactado com sucesso\n");

    fclose(arqE);
}

#endif /* COMPRESS_C_ */
