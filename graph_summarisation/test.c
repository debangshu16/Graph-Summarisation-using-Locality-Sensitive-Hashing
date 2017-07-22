#include "functions.h"
void test(graph *g)
{
	int i;
	struct node *tmpp;
	int list[]={2597,2101,2002,2394,1994,2516};
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
