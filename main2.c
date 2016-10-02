#include <stdio.h>
#include <stdlib.h>
#include "filaprioridadeheap.h"

int main()
{
    int a,b = 0;
    FILE *arq;
    arq = fopen("dados2.txt","r");
    Heap *hp = create_heap();
    while(!feof(arq))
    {
        fscanf(arq,"%d",&a);
        printf("a%d: %d\n",b,a);
        heap_enqueue(hp,a);
        b++;
    }

    return 0;
}
