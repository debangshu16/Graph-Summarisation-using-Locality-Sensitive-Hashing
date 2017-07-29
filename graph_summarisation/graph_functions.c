#include <stdio.h>
#include "functions.h"
struct node *newnode1(int v)
{
	struct node *n=(struct node *)malloc(sizeof(struct node));
	n->vertex=v;
	n->next=NULL;
	return n;
}
graph* creategraph(int v)
{
	graph *g=(graph *)malloc(sizeof(graph));
	g->v=v;
	g->arr=(struct adjlist *)malloc(sizeof(struct adjlist)*v);
	int i;
	for(i=0;i<v;i++)
	{
		g->arr[i].id=i;
		g->arr[i].head=NULL;
		g->arr[i].degree=0;
		g->arr[i].grp_no=0;
		g->arr[i].flag=0;
		g->arr[i].has_superedge=0;
		g->arr[i].colour=UNCOLOURED;
	}
	g->size=v;
	g->load=v-1;
 	

	return g;
}
void addedge(graph *g,int src,int dest)
{
	struct node *newnode=newnode1(dest);
	if(dest>=g->v)
	g->arr[src].has_superedge=1;	
	newnode->next=g->arr[src].head;
	g->arr[src].head=newnode;
	g->arr[src].degree++;
	
	newnode=newnode1(src);	
	newnode->next=g->arr[dest].head;
	g->arr[dest].head=newnode;
	g->arr[dest].degree++;

	if(src>=g->v)
	g->arr[dest].has_superedge=1;
}
void print(graph *g)
{
	int i;
	struct node *ptr;
	printf("\n");
	for(i=0;i<=g->load;i++)
	{
		ptr=g->arr[i].head;
		//if(g->arr[i].has_superedge==1)
		//{
			printf("%d-> ",g->arr[i].id);
			while(ptr!=NULL)
			{
				printf("%d,",ptr->vertex);
				ptr=ptr->next;
			}
			//printf("%d",g->arr[i].degree);
			printf("\n");
		//}
	}
}
struct node* addlink(struct node *head,int key)
{
	struct node *new=newnode1(key);
	new->next=head;
	head=new;
	return head;
}
void print_graph_score(graph *g,int start,int finish)
{
	int i;
	 
	for(i=0;i<g->v;i++)
	{
		if(g->arr[i].bin_no>=start && g->arr[i].bin_no <finish)
			printf("%d\t%lf\n",i,g->arr[i].comp_score);
		 
	}
}
		
void scoring_nodes(graph *g)
{
	int i,cnt=0;
	struct node *ptr;
	for(i=0;i<g->v;i++)
	{
		ptr=g->arr[i].head;
		cnt=0;
		while(ptr!=NULL)
		{
			if(g->arr[ptr->vertex].flag!=0)
			cnt++;
			ptr=ptr->next;
		}

		g->arr[i].comp_score=(double)cnt/g->arr[i].degree;
		//printf("%lf\n",g->arr[i].score);
	}
}
