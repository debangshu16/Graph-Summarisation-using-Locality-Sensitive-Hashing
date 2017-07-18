#include "functions.h"
void test(graph *g)
{
	int i;
	struct node *tmpp;
	int list[]={1940,2273};
	for(i=0;i<(sizeof(list)/sizeof(list[0]));i++)
	{
		tmpp=g->arr[list[i]].head;
		printf("\n%d\t",list[i]);
		while(tmpp!=NULL)
		{
			printf(",%d",tmpp->vertex);
			tmpp=tmpp->next;
		}
	}
}
