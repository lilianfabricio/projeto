#include <stdio.h>
#include <stdlib.h>
#include "filaprioridade.h"

int main()
{
    FILE *arq;
    arq = fopen("dados.txt", "r");
    PriorityQueue* pq= create_priority_queue();
    int a,b,c= 0;
    while(!feof(arq))
    {
        fscanf(arq,"%d%d",&a,&b);
        enqueue(pq,a,b);
    }
    print_queue(pq);
    fclose(arq);
    return 0;
}
