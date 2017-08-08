#include "functions.h"
extern int no_of_supernodes;
void form_superedge_zero_bin(struct bucket *bin,graph *g,int countg)
{

	int i,j,temp;	
	struct node *bptr,*lptr;
	struct node *ptr; 
	for(i=0;i<countg;i++)
	{	
				
		j=i*11;
		ptr=bin->arr[j].head;
		if(form_supernodes(ptr,g)!=-1)
		{
			lptr=g->arr[g->load].link_supernode;
			while(lptr!=NULL)
			{
				bptr=g->arr[lptr->vertex].head;
				while(bptr!=NULL)
				{
					temp=cal_supernode_adjacency(bptr->vertex,g);
					if(temp==g->arr[g->load].no_of_members)
					{
						if(!isPresent(g->arr[g->load].head,bptr->vertex))			// && g->arr[bptr->vertex].has_superedge==0)
							addedge(g,g->load,bptr->vertex);
					}
					bptr=bptr->next;
				}
				lptr=lptr->next;
			}

			reverse(&g->arr[g->load].head);
			nodesCompressed(g->arr[g->load].link_supernode,g);
			
		}
		/*else
		{
			while(ptr!=NULL)
			{
				g->arr[ptr->vertex].flag-=1;
				ptr=ptr->next;
			}
		}*/
		 
		 
	}
}
void form_superedge_last3(struct bucket *bin,graph* g,int countg)
{
	struct node *ptr,*nptr,*group;
	int i,j,k;
	float m=0,n=0;
	float M,N;
	int index;
	
	for(i=0;i<countg;i++)
	{
		j=(i*11)+10;
		ptr=merge(bin->arr[j].head,bin->arr[j-1].head);
		ptr=merge(ptr,bin->arr[j-2].head);
		group=ptr;
		if(form_supernodes(ptr,g)!= -1)
		{
		
			if(!isPresentInSortedList(g->arr[g->load].head,g->load))
				addedge(g,g->load,g->load);

			ptr=g->arr[g->load].link_supernode;
			n=(float)g->arr[g->load].no_of_members;

			N=n*(n-1)/2.0;

			while(ptr!=NULL)
			{
				//nptr=g->arr[g->load].link_supernode;
				nptr=ptr;
				while(nptr!=NULL)
				{
					if(isPresentInSortedList(g->arr[ptr->vertex].head,nptr->vertex))
					m++;

					nptr=nptr->next;
				}
				ptr=ptr->next;
			}

			M=m;
			g->arr[g->load].error=(N-M)/N;
			index=0;
			g->arr[g->load].no_of_missing_edges=(N-M);
			ptr=g->arr[g->load].link_supernode;

			g->arr[g->load].correction=(struct edge **)malloc(sizeof(struct edge *)*(N-M));
		
			for(k=0;k<(N-M);k++)
			g->arr[g->load].correction[k]=(struct edge *)malloc(sizeof(struct edge));

			while(ptr!=NULL)
			{
				//nptr=g->arr[g->load].link_supernode;
				nptr=ptr; 
				while(nptr!=NULL)
				{
					if(!isPresentInSortedList(g->arr[ptr->vertex].head,nptr->vertex) && ptr->vertex!=nptr->vertex)
					{
						g->arr[g->load].correction[index]->source=ptr->vertex;
						g->arr[g->load].correction[index]->dest=nptr->vertex;
						index++;
					}
				

					nptr=nptr->next;
				}
				ptr=ptr->next;
			}
			m=0;
			n=0;
			nodesCompressed(g->arr[g->load].link_supernode,g);
		}
		/*else
		{
			ptr=group;
			while(ptr!=NULL)
			{
				g->arr[ptr->vertex].flag-=1;
				ptr=ptr->next;
			}
		}*/
		
	}
}
int form_supernodes(struct node *head,graph *g)
{
	struct node *ptr=head;
	int cnt=0;
	
	struct link *q=(struct link *)malloc(sizeof(struct link));
	q->link=NULL;
	while(ptr!=NULL)
	{
		cnt++;
		q->link=addlink(q->link,ptr->vertex);
		 
		ptr=ptr->next;
	}
	 
	if(cnt>2)
	{
		if(g->load==g->size-1)
		{
			g->size=g->size*2;
			g->arr=(struct adjlist *)realloc(g->arr,(sizeof(struct adjlist)*g->size));
		}
		g->load++;
		g->arr[g->load].id=g->load;
		g->arr[g->load].is_supernode=1;
		g->arr[g->load].comp_score=0.0;
		g->arr[g->load].link_supernode=q->link;
		g->arr[g->load].no_of_members=cnt;
		no_of_supernodes++;
	}
	else 
	return -1;
 	

}
float calerror_bipartite(graph *g,int a,int b)
{
	int count=0,i;
	int index=0;
	struct node *ptr=g->arr[a].link_supernode;
	struct node *nptr=g->arr[b].link_supernode;

	int m=g->arr[a].no_of_members;
	int n=g->arr[b].no_of_members;
	
	while(ptr!=NULL)
	{
		nptr=g->arr[b].link_supernode;
		while(nptr!=NULL)
		{
			if(!isPresentInSortedList(g->arr[ptr->vertex].head,nptr->vertex))
				count++;
			nptr=nptr->next;
		}
		ptr=ptr->next;
	}

	g->arr[a].no_of_missing_edges=g->arr[b].no_of_missing_edges=count;
	g->arr[a].correction=(struct edge **)malloc(sizeof(struct edge *)*count);
	g->arr[b].correction=(struct edge **)malloc(sizeof(struct edge *)*count);

	for(i=0;i<count;i++)
	{
		g->arr[a].correction[i]=(struct edge *)malloc(sizeof(struct edge));	
		g->arr[b].correction[i]=(struct edge *)malloc(sizeof(struct edge));
	}
	
	ptr=g->arr[a].link_supernode;
	while(ptr!=NULL)
	{
		nptr=g->arr[b].link_supernode;
		while(nptr!=NULL)
		{
			if(!isPresentInSortedList(g->arr[ptr->vertex].head,nptr->vertex))
			{
				g->arr[a].correction[index]->source=ptr->vertex;
				g->arr[a].correction[index]->dest=nptr->vertex;

				
				g->arr[b].correction[index]->source=ptr->vertex;
				g->arr[b].correction[index]->dest=nptr->vertex;

				index++;
			}

				
			nptr=nptr->next;
		}
		ptr=ptr->next;
	}
		
	return (float)count/(m*n);
}
bool bfscolor(struct node *group,graph *g,int source)
{
	struct node *ptr,*nptr; 
	g->arr[source].colour=RED;
	struct que *q=createque();
	enque(q,source);

	while(!isempty(q))
	{
		ptr=deque(q);
		nptr=g->arr[ptr->vertex].head;

		while(nptr!=NULL)
		{
			
			if(isPresentInSortedList(group,nptr->vertex))
			{
				if(g->arr[nptr->vertex].colour == UNCOLOURED)
				{
					enque(q,nptr->vertex);
					if(g->arr[ptr->vertex].colour==RED)
						g->arr[nptr->vertex].colour=BLUE;
					else
						g->arr[nptr->vertex].colour=RED;
				}
				else if(g->arr[ptr->vertex].colour == g->arr[nptr->vertex].colour)
					return false;
			}
			nptr=nptr->next;

		}

	}
	
	return true;
}
int form_bipartite(struct bucket *bin,graph *g,int group_no)
{
	int i=group_no,j;
	bool status=true;
	
	struct node *ptr,*group=NULL,*nptr;
	struct node *snode1=NULL,*snode2=NULL;
	j=(i*11)+1;
	while(j<(i*11+8))
	{
		ptr=bin->arr[j].head;
		if(ptr!=NULL)
			group=merge(group,ptr);
		j++;
	}
		
	 
	ptr=group;
	 
	 
	
	if(group!=NULL && bfscolor(group,g,group->vertex))
	{
	
	
		while(ptr!=NULL)
		{
			if(g->arr[ptr->vertex].colour==RED)
			snode1=addlink(snode1,ptr->vertex);
			else if(g->arr[ptr->vertex].colour==BLUE)
			snode2=addlink(snode2,ptr->vertex);

			ptr=ptr->next;
		}
	
		 
	
		struct link *q=(struct link *)malloc(sizeof(struct link));
		struct link *q2=(struct link *)malloc(sizeof(struct link));
		q->link=NULL;
		q2->link=NULL;

		ptr=snode1;

		int cnt=0;

		while(ptr!=NULL)
		{
			cnt++;
			q->link=addlink(q->link,ptr->vertex);
					
			
			ptr=ptr->next;
		}

		if(cnt>1)
		{
		
			if(g->load==g->size-1)
			{
				g->size=g->size*2;
				g->arr=(struct adjlist *)realloc(g->arr,(sizeof(struct adjlist)*g->size));
			}
			g->load++;
			g->arr[g->load].id=g->load;
			g->arr[g->load].is_supernode=1;
			g->arr[g->load].comp_score=0.0;
			g->arr[g->load].link_supernode=q->link;
			g->arr[g->load].no_of_members=cnt;
			no_of_supernodes++;
			nodesCompressed(g->arr[g->load].link_supernode,g);
		
		}
		else
		{
			//if(snode1!=NULL)
			//g->arr[snode1->vertex].flag-=1;
			status=false;
		}
		 

		cnt=0;
		ptr=snode2;
		while(ptr!=NULL)
		{
			cnt++;
			q2->link=addlink(q2->link,ptr->vertex);
					
			
			ptr=ptr->next;
		}
		if(cnt>1)
		{
		
			if(g->load==g->size-1)
			{
				g->size=g->size*2;
				g->arr=(struct adjlist *)realloc(g->arr,(sizeof(struct adjlist)*g->size));
			}
			g->load++;
			g->arr[g->load].id=g->load;
			g->arr[g->load].is_supernode=1;
			g->arr[g->load].comp_score=0.0;
			g->arr[g->load].link_supernode=q2->link;
			g->arr[g->load].no_of_members=cnt;
			no_of_supernodes++;
			nodesCompressed(g->arr[g->load].link_supernode,g);
		}
		else 
		{
			//if(snode2!=NULL)
			//g->arr[snode2->vertex].flag-=1;
			status=false;
		}


		/*ptr=group;
		while(ptr!=NULL)
		{
			if(g->arr[ptr->vertex].colour==UNCOLOURED)
			g->arr[ptr->vertex].flag--;
			ptr=ptr->next;
		}*/

		 
	
		//if(getno(q->link)<=1 || getno(q2->link)<=1)
		//return -1;

	}
	else
	{
		/*if(group!=NULL)
		{
			ptr=group;
			while(ptr!=NULL)
			{
				g->arr[ptr->vertex].flag--;
				ptr=ptr->next;
			}
		}*/
		status=false;
	}
	if(!status)
	return -1;
	
}
int cal_supernode_adjacency(int vertex,graph *g)
{
	int count=0;
	struct node *ptr=g->arr[g->load].link_supernode;
	while(ptr!=NULL)
	{
		if(isPresentInSortedList(g->arr[ptr->vertex].head,vertex))
		count++;
		ptr=ptr->next;
	}

	return count;
}
	
