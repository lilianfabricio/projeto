/*
 * main.c
 *
 *  Created on: 13 de out de 2016
 *      Author: vitor_000
 */

#include <stdio.h>
#include "compress.h"
#include "decompress.h"

int main()
{
    int opcao;
    printf("\aBem-vindo ao GJVL2 D-Compress! :D\nEscolha a opção desejada:\n1. Compactação\n2. Descompactação\n");
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
            printf("Opção Inválida! Tente novamente\n");
    }
    return 0;
}
