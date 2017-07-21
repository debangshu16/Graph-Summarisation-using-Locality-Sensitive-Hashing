#include "functions.h"
void test(graph *g)
{
	int i;
	struct node *tmpp;
	int list[]={2416,2362,2318,2209,2325,1944,1964,2031,2272,2425,2525,2637};
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
