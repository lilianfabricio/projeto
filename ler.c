/*
 * ler.c
 *
 *  Created on: 17 de set de 2016
 *      Author: Lilian
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

main()
{
	FILE *arqE, *arqS;
	unsigned char aux;
	int tabela[256], i=0;
	arqE = fopen("entrada.txt", "r");
	for (i=0; i < 256; i++)
	{
		tabela[i] = 0;
	}

	while (arqE != EOF)
	{
		fscanf(arqE,"%c", &aux);
		tabela[aux]++;
	}

    if(arqE == NULL)
    {
        printf("Erro na abertura.\n");
        system("PAUSE");
        exit(0);
    }
    /*
    else
    {
    	printf("Aberto com sucesso!\n");
    }*/
    //contador(tabela, arqE);

    fclose(arqE);
}

