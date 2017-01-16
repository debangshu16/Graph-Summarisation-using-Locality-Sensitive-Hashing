#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
struct hash
{
	int *x;
	
		
};
 
int h(int *vec,int x,int nc)
{
	int i,s=0;
	for(i=0;i<nc;i++)
	{
		s=s+((int)pow(x,i)*vec[i]);
	}
	return s;
} 

#define h1(x) (2*x+1)
#define h2(x) (x+1)%100 
#define g1(x) x%10

struct node *merge(struct node *,struct node *);

struct node
{
	int vertex;
	struct node *next;
};
struct adjlist
{
	struct node *head;
	int degree;
	int bin_no;
	int grp_no;

	char group;
};

typedef struct graph
{
	int v,e;
	struct adjlist *arr;
}graph;


struct binlist
{
	struct node *head;
	int nn;
};
struct bin
{
	struct binlist *a;
}; 

struct adjmat
{
	int **mat;
	int *elements;
	int n;
};

struct bucketlist
{
	struct node *head;
};
struct bucket
{
	struct bucketlist *arr;
};

void lsh(int **,int *,int,graph *);

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
		g->arr[i].head=NULL;
		g->arr[i].degree=0;
	}

	for(i=0;i<g->v;i++)
	{
		g->arr[i].grp_no=0;
	}

	return g;
}
void addedge(graph *g,int src,int dest)
{
	struct node *newnode=newnode1(dest);
	
	newnode->next=g->arr[src].head;
	g->arr[src].head=newnode;
	g->arr[src].degree++;
	
	newnode=newnode1(src);	
	newnode->next=g->arr[dest].head;
	g->arr[dest].head=newnode;
	g->arr[dest].degree++;
}
void print(graph *g)
{
	int i;
	for(i=0;i<g->v;i++)
	{
		struct node *ptr=g->arr[i].head;

		/*printf(" %d -> ",i);
		while(ptr!=NULL)
		{
			printf("%d - > ",ptr->vertex);
			ptr=ptr->next;
		}*/
		printf("%d",g->arr[i].degree);
		printf("\n");
	}
}
int main()
{
	long int v=4039,e=88234;

	
	int i,src,dest,t;
	

	FILE *fp;
	fp=fopen("FB.txt","r");
	//scanf("%d%d",&v,&e);
	
	double tmp,x;
	graph *g=creategraph(v);
	
		
	
	for(i=0;i<e;i++)
	{
		fscanf(fp,"%d%d",&src,&dest);		
		addedge(g,src,dest);
	}

	
	

	//print(g);

	for(i=0;i<v;i++)
	{
		tmp=g->arr[i].degree;
		tmp=log(tmp);
		t=tmp*10;
		tmp=t/10.0;

		//printf("%lf\n",tmp);
		g->arr[i].bin_no=tmp*10;
		//printf("%d\n",g->arr[i].bin_no);
	}

	struct bin *bin=(struct bin *)malloc(sizeof(struct bin));
	bin->a=(struct binlist *)malloc(sizeof(struct binlist)*70);

	struct node *q;
		
	int cnt;
	int j=0;	
	while(j<70)
	{
		cnt=0;		
		for(i=0;i<v;i++)
		{
			if(g->arr[i].bin_no==j)
			{
				//printf("%d->",i);

				q=newnode1(i);
				q->next=bin->a[j].head;
				bin->a[j].head=q;
	
				
				cnt++;
			}
		}
		//printf("%d\n",cnt);
		//printf("\n");
		bin->a[j].nn=cnt;
		j++;
	}

	/*for(i=0;i<70;i++)
	{
		struct node *ptr=bin->a[i].head;
		while(ptr!=NULL)
		{
			printf("%d->",ptr->vertex);
			ptr=ptr->next;
		}
		printf("\n");
		
		//printf("%d\n",bin->a[i].nn);
	}
	*/

	
	int visited[v];
	int n1=0;

	for(i=0;i<v;i++)
	visited[i]=0;

	struct node *ptr,*nptr;
	for(i=60;i<70;i++)
	{
		//n1+=bin->a[i].nn;
		ptr=bin->a[i].head;
		while(ptr!=NULL)
		{
			if(visited[ptr->vertex]==0){			
			visited[ptr->vertex]=1;
			n1++;
			nptr=g->arr[ptr->vertex].head;

			while(nptr!=NULL)
			{
				if(visited[nptr->vertex]==0)
				{
					n1++;
					visited[nptr->vertex]=1;
				}
				nptr=nptr->next;
			}
			
			}
			ptr=ptr->next;
		}
		
	}

	//printf("%d",n1);
	cnt=0;
	
	struct adjmat adjmat;
	
	adjmat.mat=(int **)malloc(sizeof(int *)*n1);
	for(i=0;i<n1;i++)
	adjmat.mat[i]=(int *)malloc(sizeof(int)*n1);

	adjmat.n=n1;

	adjmat.elements=(int *)malloc(sizeof(int)*n1);

	for(i=0;i<v;i++)
	{
		if(visited[i]==1)
		{
			adjmat.elements[cnt++]=i;
		}
	}

	//for(i=0;i<adjmat.n;i++)
	//printf("%d\n",adjmat.elements[i]);

	for(i=0;i<n1;i++)
	{
		for(j=0;j<n1;j++)
		adjmat.mat[i][j]=0;
	}

	
	for(i=0;i<n1;i++)
	{
		ptr=g->arr[adjmat.elements[i]].head;
		while(ptr!=NULL)
		{
		
			for(j=0;j<n1;j++)
			{
				if(ptr->vertex==adjmat.elements[j])
				{
					adjmat.mat[i][j]=1;
					break;
				}
			}
			ptr=ptr->next;
		}
	}
	lsh(adjmat.mat,adjmat.elements,n1,g);

	/*for(i=0;i<n1;i++)
	{
		for(j=0;j<n1;j++)
		printf("%d\t",adjmat.mat[i][j]);

		printf("\n");
	}*/
}
 

void lsh(int **a,int *elements,int n1,graph *g)
{

	int i,j,r=n1,c=n1,k,temp1,temp,cntb=0;
	
	int nh=3,nc=2;
	int M[nh][n1];

	struct hash hash[nh];

	for(i=0;i<nh;i++)
	{
		hash[i].x=(int *)malloc(sizeof(int)*nc);
	}
 	srand(time(NULL));

	for(i=0;i<nh;i++)
	{
		for(j=0;j<nc;j++)
		{
			hash[i].x[j]=(rand()%10)+1;
		}
	}
	 
	 
	
	for(i=0;i<nh;i++)
	{
		for(j=0;j<c;j++)
			M[i][j]=99999;
	}

	 
	 

	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(a[i][j]==1)
			{
				for(k=0;k<nh;k++)
				{
					if(h(hash[k].x,i,nc)<M[k][j])
						M[k][j]=h(hash[k].x,i,nc);

					
					/*if(k==0){	
					if(h1(i)<M[0][j])
					M[0][j]=h1(i);}
					if(k==1)
					{
						if(h2(i)<M[1][j])
							M[1][j]=h2(i);
					}
					*/					 
				}
			}
		}
	}


	 
	
	struct bucket *bucket=(struct bucket *)malloc(sizeof(struct bucket));
	struct node *ptr;
	bucket->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*10);

	struct bucket *bucket2;
	int t;

	for(i=0;i<c;i++)
	{
		t=g1(M[0][i]);
		ptr=newnode1(elements[i]);
		ptr->next=bucket->arr[t].head;
		bucket->arr[t].head=ptr;
			
	}
	

	 
	
	 
	for(i=0;i<10;i++)
	{
		ptr=bucket->arr[i].head;
	
		if(ptr!=NULL)
			cntb++;		

		while(ptr!=NULL)
		{
			//printf("%d->",ptr->vertex);
			g->arr[ptr->vertex].grp_no++;
			g->arr[ptr->vertex].group=(char)(65+cntb-1);
			ptr=ptr->next;
		}
		//printf("\n\n");
	}
	j=1;
	
	while(j<nh){
	
	bucket2=(struct bucket *)malloc(sizeof(struct bucket));
	 
	bucket2->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*10);

	

	for(i=0;i<c;i++)
	{
		t=g1(M[j][i]);
		ptr=newnode1(elements[i]);
		ptr->next=bucket2->arr[t].head;
		bucket2->arr[t].head=ptr;
		
	}

	
	struct node *ptr2;
	for(i=0;i<10;i++)
	{
		ptr=bucket2->arr[i].head;

		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{
								
				ptr2=ptr;				
				temp1=g->arr[ptr2->vertex].group;
				temp=temp1;
				while(g->arr[ptr2->vertex].group==temp)
				{
					ptr2=ptr2->next;
					if(ptr2==NULL)
					break;
				}
				if(ptr2!=NULL)
				{
					temp=g->arr[ptr2->vertex].group;
					ptr=ptr2;
				}
				if(temp1!=temp)
				{
					bucket->arr[temp1-65].head=merge(bucket->arr[temp1-65].head,bucket->arr[temp-65].head);
					bucket->arr[temp-65].head=NULL;
				}
				ptr=ptr->next;
			}
			
		}
		
	}
	/*int distribution1[10][7];
	int cnt=0;

	

	for(i=0;i<10;i++)
	{
		for(j=0;j<7;j++)
			distribution1[i][j]=0;
	}

	for(i=0;i<10;i++)
	{
		ptr=bucket2->arr[i].head;

		if(ptr!=NULL)
		{
	
			while(ptr!=NULL)
			{
				temp=g->arr[ptr->vertex].bin_no;

				temp=temp/10;
				distribution1[cnt][temp]=distribution1[cnt][temp]+1;		

				ptr=ptr->next;

			}
			cnt++;
		}
	}
					
	for(i=0;i<10;i++)
	{
		for(j=0;j<7;j++)
		printf("%d\t",distribution1[i][j]);

		printf("\n");
	}*/
	
	j++;
	bucket2=NULL;
	}
	

	for(i=0;i<10;i++)
	{
		ptr=bucket->arr[i].head;
		while(ptr)
		{
			printf("%d->",ptr->vertex);
			ptr=ptr->next;
		}
		printf("\n\n");
	}
					


	int distribution[cntb][7];
	int cnt=0;

	

	for(i=0;i<cntb;i++)
	{
		for(j=0;j<7;j++)
			distribution[i][j]=0;
	}

	for(i=0;i<10;i++)
	{
		ptr=bucket->arr[i].head;

		if(ptr!=NULL)
		{
	
			while(ptr!=NULL)
			{
				temp=g->arr[ptr->vertex].bin_no;

				temp=temp/10;
				distribution[cnt][temp]=distribution[cnt][temp]+1;		

				ptr=ptr->next;

			}
			cnt++;
		}
	}
					
	for(i=0;i<cntb;i++)
	{
		for(j=0;j<7;j++)
		printf("%d\t",distribution[i][j]);

		printf("\n");
	}
	
	/*int s=0,count=0;

	for(i=0;i<g->v;i++)
	{
		if(g->arr[i].grp_no==1)
		{
			//printf("%d\t",i);
			count++;
		}
		printf("%d\n",g->arr[i].grp_no);

	}
	//printf("%d",count);
*/
}					
struct node * merge(struct node *head1,struct node *head2)
{
	struct node *result = NULL;
	struct node *t1 = head1, *t2 = head2;
 
   
	while (t1 != NULL)
    	{
        	push(&result, t1->vertex);
       	        t1 = t1->next;
    	}
 
     
        while (t2 != NULL)
    	{
        	if (!isPresent(result, t2->vertex))
                push(&result, t2->vertex);
        	t2 = t2->next;
    	}
 
        //head1=result;
	return result;
}
void push (struct node** head_ref, int new_data)
{
    
    struct node* new_node =
        (struct node*) malloc(sizeof(struct node));
 
    
    new_node->vertex = new_data;
 
    
    new_node->next = (*head_ref);
 
    
    (*head_ref) = new_node;
}

int isPresent (struct node *head, int data)
{
    struct node *t = head;
    while (t != NULL)
    {
        if (t->vertex == data)
            return 1;
        t = t->next;
    }
    return 0;
}
		
							 
	
			
		
	

