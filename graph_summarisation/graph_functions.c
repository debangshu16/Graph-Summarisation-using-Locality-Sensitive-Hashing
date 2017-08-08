#include <stdio.h>
#include "functions.h"
extern int no_of_supernodes;
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
	int i,k,counte=0,countg=0;
	struct node *ptr,*tmpp;
	bool flag=false;
 
	for(i=g->v;i<(g->v+no_of_supernodes);i++)
	{	
		ptr=g->arr[i].head;
		if(ptr!=NULL) //&& getno(g->arr[i].link_supernode)>2)
		{
			/*printf("\n%d:",g->arr[i].id);
			
	
			printf("Members:\t");
			tmpp=g->arr[i].link_supernode;
			while(tmpp!=NULL)
			{
				printf("%d,",tmpp->vertex);
				tmpp=tmpp->next;
			}
			printf("\t\tAdjacencies:\t"); 
			while(ptr!=NULL)
			{
				printf("->%d",ptr->vertex);
				ptr=ptr->next;
			}
			ptr=NULL;

			printf("\t ERROR =%f %%",(g->arr[i].error*100));
			if(g->arr[i].error >0)
			{
				printf("\t EDGE CORRECTION:");
				for(k=0;k<g->arr[i].no_of_missing_edges;k++)
				printf("%d-%d, ",g->arr[i].correction[k]->source,g->arr[i].correction[k]->dest);
			}*/
			if(g->arr[i].error==1)
			flag=true;
			countg++;
			if(g->arr[i].error >=0.5)
			counte++;
		}

		 
		 
			 
	}
	if(flag)
	printf("\nBad result,contains a group of error 100%%");
	printf("\n%d out of %d groups has error >= 50%%",counte,countg);

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
			if(g->arr[ptr->vertex].flag>0)
			cnt++;
			ptr=ptr->next;
		}

		g->arr[i].comp_score=(double)cnt/g->arr[i].degree;
		//printf("%lf\n",g->arr[i].score);
	}
}
