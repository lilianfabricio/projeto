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
    printf("\aBem-vindo ao GJVL2 D-Compress! :D\nEscolha a op��o desejada:\n1. Compacta��o\n2. Descompacta��o\n");
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
            printf("Op��o Inv�lida! Tente novamente\n");
    }
    return 0;
}
