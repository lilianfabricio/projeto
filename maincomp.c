#include <stdio.h>
#include <stdlib.h>
#include "filaprioridade.h"
#include "filaprioridadeheap.h"

int main()
{
	FILE *pqdata, *hpdata;
	pqdata = fopen("dados.txt","r");
	hpdata = fopen("dados2.txt","r");
	PriorityQueue* pq = create_priority_queue();
	Heap* hp = create_heap();
	int sortnumber,pqcount = 0,hpcount = 0;
	int pqaux = 0;
	printf("Digite um numero:");
	scanf("%d",&sortnumber);
	/*while(!feof(pqdata))
    {

    }*/
	return 0;
}
