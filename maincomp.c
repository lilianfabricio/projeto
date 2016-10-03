#include <stdio.h>
#include <stdlib.h>
#include "filaprioridade.h"
#include "filaprioridadeheap.h"

int search_queue(PriorityQueue *pq, int v)
{
    int pqcount = 0;
    Node *aux = pq->first;
    if(v > 20000)
    {
        return -1;
    }
    if(pq->first->value == v)
    {
        return pqcount;
    }
    else
    {
        while(v != aux->value)
        {
            pqcount++;
            aux = aux->nextNode;
        }
    }
    return pqcount;
}

int search_heap(Heap *hp, int k)
{
    int hpcount = 0, i = 0;
    int vlr = value_of(hp,i);
    if(k > 20000)
    {
        return -1;
    }
    if( vlr == k)
    {
        return hpcount;
    }
    else
    {
        i++;
        vlr = value_of(hp,i);
        while(vlr != k)
        {
            hpcount++;
            i++;
            vlr = value_of(hp,i);
        }
        hpcount++;
    }
    return hpcount;
}

int main()
{
	FILE *pqdata, *hpdata;
	pqdata = fopen("dados.txt","r");
	hpdata = fopen("dados2.txt","r");

	PriorityQueue* pq = create_priority_queue();
	Heap* hp = create_heap();

	int sortnumber,pqcount = 0,hpcount = 0;
	int val,pri;
	int var;

    if(pqdata == NULL || hpdata == NULL)
    {
        printf("ERRO ABERTURA DOS ARQUIVOS!\n");
        system("PAUSE");
        exit(0);
    }


	while(!feof(pqdata))
    {
        fscanf(pqdata,"%d%d",&val,&pri);
        enqueue(pq,val,pri);
    }

    while(!feof(hpdata))
    {
        fscanf(hpdata,"%d",&var);
        heap_enqueue(hp,var);
    }
    printf("[0 ENCERRA] Digite um valor: ");
    scanf("%d",&sortnumber);
    while(sortnumber != 0)
    {
        pqcount = search_queue(pq,sortnumber);
        hpcount = search_heap(hp,sortnumber);
        printf("Numero de comparacoes na fila: %d\n", pqcount);
        printf("Numero de comparacoes na heap: %d\n", hpcount);
        printf("Digite um novo valor ou 0 para encerrar: ");
        scanf("%d",&sortnumber);
    }
    fclose(pqdata);
    fclose(hpdata);
	return 0;
}
