#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
struct hash
{
	int a;
	int b;
	
		
};
int max; 
int modv;
int h(int a,int b,int x) 
{
	int s=0;
	

	s=(a*x)+b;

	s=abs(s);
	
	return s%modv;
} 

#define h1(x) (2*x+1)
#define h2(x) (x+1)%100 
 
int no_of_supernodes=0;
struct node *merge(struct node *,struct node *);
struct inter *intersection(struct inter*,int *,int,int);
double jsv(struct node *,struct node *);
void quickSort(int a[],int,int); 
int maxn(int,int);
struct node *getIntersection(struct node *,struct node *);
int search(int a[],int,int,int);


struct node
{
	int vertex;
	double score;
	struct node *next;
};
struct link
{
	struct node *link;
};  
struct group
{
	int current;
	struct node *list;
};
struct adjlist
{
	int id;
	struct node *head;
	int degree;
	int bin_no;

	int grp_no;

	int  group;
	
	int flag;

	double comp_score;

	int is_supernode;
	int lsh_group;
	struct node *link_supernode;
};
struct adjmat
{
	int **mat;
	int *elements;
	int n1;
};


typedef struct graph
{
	int v,e;
	int size;
	int load;
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

 

struct bucketlist
{
	struct node *head;
	int grplength;
	char grptype[20];
	double grp_score;
};
struct bucket
{
	struct bucketlist *arr;
	int size;
};

struct inter
{
	int **a;
	int size;
};

void lsh(int **,int *,int,graph *,int);
struct adjmat* create_adjmat(struct bin *,graph *,int[],int);
int getno(struct node *);
int isPresent(struct node *,int);
void form_superedge_zero_bin(struct bucket*,graph*,int);
void form_supernodes(struct node*,graph *);
 

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
	}
	g->size=v;
	g->load=v-1;
 	

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
struct node* addlink(struct node *head,int key)
{
	struct node *new=newnode1(key);
	new->next=head;
	head=new;
	return head;
}
void print(graph *g)
{
	int i;
	for(i=0;i<g->v;i++)
	{
		struct node *ptr=g->arr[i].head;

		printf(" %d -> ",i);
		while(ptr!=NULL)
		{
			printf("%d - > ",ptr->vertex);
			ptr=ptr->next;
		}
		//printf("%d",g->arr[i].degree);
		printf("\n");
	}
}
int main()
{
	long int v=4039,e=88234;
	//int v=62,e=318;
	
	int i,src,dest,t;
	

	FILE *fp;
	fp=fopen("FB.txt","r");

	//fp=fopen("dolph.txt","r");
	 
	 
	double tmp,x;
	graph *g=creategraph(v);
	
		
	
	for(i=0;i<e;i++)
	{
		fscanf(fp,"%d%d",&src,&dest);		
		addedge(g,src,dest);
	}

	
	int maxdeg=0;
	for(i=0;i<v;i++)
	{
		if(g->arr[i].degree>maxdeg)
		maxdeg=g->arr[i].degree;
	}

	//print(g);
	max=0;
	for(i=0;i<v;i++)
	{
		tmp=g->arr[i].degree;
		tmp=log(tmp);
		t=(int)(tmp*10);

		if(t>max)
		max=t;
 
		//printf("%lf\n",tmp);
		if(t==0)
		g->arr[i].bin_no=t;
		else
		g->arr[i].bin_no=(t/10)+1;
		//printf("%d\n",g->arr[i].bin_no);
	}

	 

	max=(max/10)+2;

	struct bin *bin=(struct bin *)malloc(sizeof(struct bin));
	bin->a=(struct binlist *)malloc(sizeof(struct binlist)*max);

	struct node *q;

	int dist[max];
	 
	int cnt;
	int j=0;	
	while(j<max)
	{
		cnt=0;		
		for(i=0;i<v;i++)
		{
			if(g->arr[i].bin_no==j)
			{
				//printf("%d->",i);
				//j=g->arr[i].bin_no;

				q=newnode1(i);
				q->next=bin->a[j].head;
				bin->a[j].head=q;
				
				
				
				cnt++;
			}
		}
		bin->a[j].nn=cnt;
		j++;
	}
		//printf("%d\n",cnt);
		//printf("\n");
		
	for(i=0;i<max;i++)
	{
		dist[i]=getno(bin->a[i].head);
	}	
	
	
	/*for(i=0;i<max;i++)
	{	
		if(i!=0)
		printf("%d-%d\t%d\n",i*10-10,i*10,dist[i]);
		else 
		printf("%d\t%d\n",i,dist[i]);
	}*/

	//printf("\n No of nodes in 0 bin=%d\n",getno(bin->a[0].head));	 
	
	int visited[v];

	

	//int elem[3];
	int pos1,pos2;

	pos1=(max-1);
	for(i=0;i<v;i++)
	visited[i]=0;

	struct node *ptr,*nptr,*ptrs;
	 
	
	int k=0;
	int **adjmat;
	int *elements;
	modv=v;

	while(k<max)
	{
		 
		struct adjmat * adjmat1=create_adjmat(bin,g,visited,k);

		
			 
		//printf("\nLSH ON %d nodes\n",adjmat1->n1);

		 
			
	 
		lsh(adjmat1->mat,adjmat1->elements,adjmat1->n1,g,k);
		 
		  

		for(i=0;i<g->v;i++)
		{
			 
			visited[i]=0;
			 
		}

		 
		k++;
		 	 
	}
	 
	 
	 
	//print_graph_score(g,0,max);
	cnt=0;
	for(i=0;i<g->v;i++)
	{
		if(g->arr[i].comp_score==1)
		cnt++;
	}
	 
	 
	/*for(i=g->v;i<(g->v+no_of_supernodes);i++)
	{	
		printf("\n\n%d \t",g->arr[i].id);
		ptr=g->arr[i].head;
		 
		while(ptr!=NULL)
		{
			printf("->%d",ptr->vertex);
			ptr=ptr->next;
		}
		ptr=NULL;
		 
	}*/

	 
	 
	 
}
 

struct adjmat * create_adjmat(struct bin *bin,graph *g,int visited[],int k)
{
		int n1=0,i,j;
		
		struct node *ptr,*nptr;
		ptr=bin->a[k].head;
		while(ptr!=NULL)
		{
			if(visited[ptr->vertex]==0 &&g->arr[ptr->vertex].comp_score!=1)
			{
				visited[ptr->vertex]=1;
				n1++;
				nptr=g->arr[ptr->vertex].head;
				while(nptr!=NULL)
				{
					if(!visited[nptr->vertex] && g->arr[nptr->vertex].comp_score!=1)
					{
						n1++;
						visited[nptr->vertex]=1;
					}
					nptr=nptr->next;
				}
			
			}
			ptr=ptr->next;
		}
		struct adjmat *adjmat=(struct adjmat *)malloc(sizeof(struct adjmat));
		adjmat->n1=n1;
		adjmat->mat=(int **)malloc(sizeof(int *)*n1);

		for(i=0;i<n1;i++)
		adjmat->mat[i]=(int *)malloc(sizeof(int)*n1);

		 

		adjmat->elements=(int *)malloc(sizeof(int)*n1);
		int cnt=0;
		 
		for(i=0;i<g->v;i++)
		{
			if(visited[i]==1)
			{
				 adjmat->elements[cnt++]=i;
			}
		}

		 

	 

		for(i=0;i<n1;i++)
		{
			for(j=0;j<n1;j++)
			adjmat->mat[i][j]=0;
		}

	
		for(i=0;i<n1;i++)
		{
			ptr=g->arr[adjmat->elements[i]].head;
			while(ptr!=NULL)
			{
		
				for(j=0;j<n1;j++)
				{
					if(ptr->vertex==adjmat->elements[j])
					{
						adjmat->mat[i][j]=1;
						break;
					}
				}
				ptr=ptr->next;
			}
		}

		return adjmat;
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
int posn(int *elements,int n,int key)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(elements[i]==key)
		return i;
	}
	return -1;
}



void lsh(int **a,int *elements,int n1,graph *g,int bin_index)
{

	int i,j,r=n1,c=n1,k,temp1,temp,cntb=0,t,t2;

	struct node *ptr,*q ;

	struct node *nptr=NULL,*ptr2=NULL;

	int grouping[g->v];

 	struct group grpun[g->v];

	int grpcount=0;

	for(i=0;i<g->v;i++)
	{
		grouping[i]=-1;
		grpun[i].current=-1;
		grpun[i].list=NULL;
		 
	}

	struct bucket *cpybucket=(struct bucket *)malloc(sizeof(struct bucket));
	cpybucket->size=0;
	struct inter *cpy=(struct inter *)malloc(sizeof(struct inter));

	 
	srand(time(NULL));

	
	int nh=30,band_no=6;
	int M[nh][n1];

	struct hash hash[nh];

	for(i=0;i<nh;i++)
	{
		hash[i].a= (rand()%nh)*2+1;
		hash[i].b=(rand()%100)-(rand()%100) +1;
	}

	 
	 	 
	 
	 
	
	for(i=0;i<nh;i++)
	{
		for(j=0;j<c;j++)
			M[i][j]=g->v;
	}

	 
	 

	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(a[i][j]==1)
			{
				for(k=0;k<nh;k++)
				{
					if(h(hash[k].a,hash[k].b,i)<M[k][j])
						M[k][j]=h(hash[k].a,hash[k].b,i);

					 			 
				}
			}
		}
	}
	 

	int s1,s2,t1=0,band ;
	float sim;
	int flag=0;
	 
	
	j=0;
	while(j<nh)
	{
	
		
	//	struct inter *mat2=(struct inter *)malloc(sizeof(struct inter));
	struct inter *final=(struct inter *)malloc(sizeof(struct inter));

	if(j==band_no)
	{
		for(i=0;i<cpybucket->size;i++)
		{
			ptr=cpybucket->arr[i].head;
			if(ptr!=NULL)
			{
				q=newnode1(i);
				while(ptr!=NULL)
				{
									
					grpun[ptr->vertex].current=i;
					q->next=grpun[ptr->vertex].list;
					grpun[ptr->vertex].list=q;

					ptr=ptr->next;
				}
				 
			}
		}
		 
	}
			
	
	 

	 
	

	for(band=1;band<=band_no;band++){

	struct inter *mat1=(struct inter *)malloc(sizeof(struct inter));

	struct bucket *bucket=(struct bucket *)malloc(sizeof(struct bucket));
	
	bucket->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*g->v);

	int tpos;
	for(i=0;i<n1;i++)
	{
		tpos=M[j][i];
		ptr=newnode1(elements[i]);
		ptr->next=bucket->arr[tpos].head;
		bucket->arr[tpos].head=ptr;
			
	}
	
	
	 
	
	cntb=0; 
	for(i=0;i<g->v;i++)
	{
		ptr=bucket->arr[i].head;
	
		if(ptr!=NULL)
		{
			cntb++;		

			while(ptr!=NULL)
			{
			
			 				 
				ptr=ptr->next;
			}
		}
		
	}
	
	 
	 

	mat1->size=cntb;

	mat1->a=(int **)malloc(sizeof(int *)*mat1->size);
	for(i=0;i<mat1->size;i++)
	{
		mat1->a[i]=(int *)malloc(sizeof(int)*n1);
		for(k=0;k<n1;k++)
		mat1->a[i][k]=0;
	}

	t1=0;
	for(i=0;i<g->v;i++)
	{
		ptr=bucket->arr[i].head;
		if(ptr!=NULL)
		{
			
					
			while(ptr!=NULL)
			{
				t=posn(elements,n1,ptr->vertex);
				mat1->a[t1][t]=1;
				
				ptr=ptr->next;
			}
			t1++;
		}
	}
	

	if(band==1)
	{
		final->size=mat1->size;
		final->a=(int **)malloc(sizeof(int *)*mat1->size);
		for(i=0;i<final->size;i++)
		final->a[i]=(int *)malloc(sizeof(int)*n1);

		for(i=0;i<mat1->size;i++)
		{
			for(k=0;k<n1;k++)
			{
				final->a[i][k]=mat1->a[i][k];
				if(mat1->a[i][k]==1)
				grouping[elements[k]]=i;
			}
		}
	}
	else
	{
		t1=0;
		for(i=0;i<mat1->size;i++)
		{
			for(k=0;k<n1;k++)
			{
				if(mat1->a[i][k]==1)
				{
					t1=grouping[elements[k]];
					final=intersection(final,mat1->a[i],t1,n1);
				}	
			}
		}

		for(i=0;i<final->size;i++)
		{
			for(k=0;k<n1;k++)
			{
				if(final->a[i][k]==1)
				{
					grouping[elements[k]]=i;
				}
			}
		}

	}
 


	j++;

	 
	bucket->arr=NULL;
	bucket=NULL;

	mat1->a=NULL;
	mat1=NULL;

	}
		
 
	
	 
	 
	 
	

	

	 
	 

	struct bucket *tempb=(struct bucket *)malloc(sizeof(struct bucket));
	 
	tempb->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*final->size);
	tempb->size=final->size;

	for(i=0;i<tempb->size;i++)
	{
		//q=newnode1(grpcount);
		for(k=0;k<n1;k++)
		{
			if(final->a[i][k]==1)
			{
				
				ptr=newnode1(elements[k]);
				ptr->next=tempb->arr[i].head;
				tempb->arr[i].head=ptr;

				
								 
							
			}
		}
		//grpcount++;
	}

	 

	 
	 
	
	
	if(cpybucket->size!=0)
	{
		//printf("Entered merging state");
		for(i=0;i<tempb->size;i++)
		{
			ptr=tempb->arr[i].head;
			if(ptr!=NULL)
			{	
				flag=0;
				while(ptr!=NULL)
				{
					t=ptr->vertex;
					ptr2=grpun[t].list;
					while(ptr2!=NULL)
					{
						t2=ptr2->vertex;
						s1=getno(getIntersection(tempb->arr[i].head,cpybucket->arr[t2].head));
						
						s2=maxn(getno(tempb->arr[i].head),getno(cpybucket->arr[t2].head));

						sim=(float)s1/s2;
						if(sim>=0.5)
						{
							cpybucket->arr[t2].head=merge(tempb->arr[i].head,cpybucket->arr[t2].head);
							q=cpybucket->arr[t2].head;
							while(q!=NULL)
							{
								if(!isPresent(grpun[q->vertex].list,t2))
								{
									struct node *tnode=newnode1(t2);
									tnode->next=grpun[q->vertex].list;
									grpun[q->vertex].list=tnode;
								}
								q=q->next;
							}
							flag=1;
									
						}
						ptr2=ptr2->next;
					}
					ptr=ptr->next;
				}
				if(flag!=1)
				{
					cpybucket->size=cpybucket->size+1;
					cpybucket->arr=(struct bucketlist *)realloc(cpybucket->arr,(sizeof(struct bucketlist)*cpybucket->size));
					cpybucket->arr[cpybucket->size-1].head=tempb->arr[i].head;
					nptr=tempb->arr[i].head;
					q=newnode1(cpybucket->size-1);
					while(nptr!=NULL)
					{
						q->next=grpun[nptr->vertex].list;
						grpun[nptr->vertex].list=q;
						nptr=nptr->next;
					}
				}
			}
		}
	} 
	else
	{
		 		
		cpybucket->size=tempb->size;
		cpybucket->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*cpybucket->size);

		for(i=0;i<cpybucket->size;i++)
		{
			 cpybucket->arr[i].head=tempb->arr[i].head;
		}

	}
				
		
	ptr=nptr=ptr2=NULL;
	tempb->arr=NULL;
	tempb=NULL;

	final->a=NULL;
	final=NULL;

	
	 
	
	 

	}
	
	int countg;
	for(i=0;i<cpybucket->size;i++)
	{
		ptr=cpybucket->arr[i].head;
		if(ptr!=NULL)
		{
			countg=0;
			while(ptr!=NULL)
			{
				countg++;
				ptr=ptr->next;
			}
			cpybucket->arr[i].grplength=countg;
			if(countg<=2)
			cpybucket->arr[i].head=NULL;
		}
	}

	int cnt=0;
	 
	for(i=0;i<cpybucket->size;i++)
	{
		ptr=cpybucket->arr[i].head;
		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{
				if(g->arr[ptr->vertex].flag==0)
				//g->arr[ptr->vertex].flag=1;
				s1=getno(getIntersection(g->arr[ptr->vertex].head,cpybucket->arr[i].head));
				ptr->score=(double)s1/(cpybucket->arr[i].grplength-1);
				//printf("%lf  ",ptr->score);
				ptr=ptr->next;
			}
			//printf("\n");
			cnt++;

		}
	}

	 
	countg=cnt;
	 
	 

	struct bucket * bin=(struct bucket *)malloc(sizeof(struct bucket));
	bin->size=cnt*11;
	bin->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*bin->size);

	for(i=0;i<bin->size;i++)
	bin->arr[i].grplength=0;

	struct node *tnode;
	cnt=0;

	 
	for(i=0;i<cpybucket->size;i++)
	{
		ptr=cpybucket->arr[i].head;
		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{
				if(ptr->score==0)
				t=cnt;
				else if(ptr->score < 0.1)
				t=cnt+1;
				else
				t=(int)(ptr->score*10)+1+cnt;

				tnode=newnode1(ptr->vertex);
				tnode->score=ptr->score;
				tnode->next=bin->arr[t].head;
				bin->arr[t].head=tnode;
				bin->arr[t].grplength++;
				ptr=ptr->next;

				 
				 
			}
			cnt+=11;
		}
	}
	
	cnt=0; 
	int gd=0,sgd=0,gcount=0;

	for(i=0;i<bin->size;i++)
	{
		if(i%11==0)
		{
			 
			//printf("\n");
			
			if(i!=0)
			{
				sgd++;
				if(cnt!=0)
				bin->arr[i-11].grp_score=((double)1/cnt)/sgd;
				gd=sgd=gcount=0;
			}

			cnt=0;
		}
		//printf("%d\t",getno(bin->arr[i].head));
		if(bin->arr[i].head!=NULL)
		{
			cnt++;
			 
			if(i%11!=0)
			{
				if(gcount!=0)
					sgd+=(i%11)-gd-1;
				gd=i%11;
				gcount++;
				 
			}
			else
			gcount++;
						
		}
	}
	//printf("\n");
	sgd++;
	bin->arr[i-11].grp_score=((double)1/cnt)/sgd;

	 

	//printf("\n SCORE A ON GROUPS:\n"); 
	//for(i=0;i<countg;i++)
	//printf("%lf\n",bin->arr[(i*11)].grp_score);

	
	for(i=0;i<countg;i++)
	{
		if(bin->arr[(i*11)].grp_score >=0.5)
		{
			j=i*11;
			while(j<((i*11)+11))
			{
				ptr=bin->arr[j].head;
				cnt=0;
				while(ptr!=NULL)
				{
					if(g->arr[ptr->vertex].bin_no==bin_index)
					cnt++;
					ptr=ptr->next;
				}
				if(cnt==0)
				{					//discard this group 
					
					bin->arr[j].head=NULL;
				}
				j++;
			}
		}
	}

	for(i=0;i<countg;i++)					    //setting compression flag to 1 for the nodes in a group
	{
		j=i*11;
		while(j<((i*11)+11))
		{
			ptr=bin->arr[j].head;
			while(ptr!=NULL)
			{
				g->arr[ptr->vertex].flag=1;
				 
				ptr=ptr->next;
			}
			j++;
		} 
	}
	
	scoring_nodes(g);	//compute compression scores	 

	form_superedge_zero_bin(bin,g,countg); 
	
	 
	 
										

	/*double score_a,nscore;							//RESCORING NODES FROM 2ND TO 6TH BIN IF GROUP SCORE IS LOW
	for(i=0;i<countg;i++)
	{
		//printf("%lf\n",bin->arr[(i*11)].grp_score);
		score_a=bin->arr[(i*11)].grp_score;
		if(score_a <=0.1)
		{
			j=i*11+1;
			while(j<(i*11+6))
			{
				ptr=bin->arr[j].head;
				 
				printf("\n Bin %d\n",(j%11)+1);
				while(ptr!=NULL)
				{
					 s1=getno(getIntersection(g->arr[ptr->vertex].head,bin->arr[j].head));
					 nscore=(double)s1/getno(bin->arr[j].head);
					 ptr->score=nscore;
					 printf("%lf\t",nscore);
					 ptr=ptr->next;
				}
				
				j++;
			}

			printf("\n\n\n");
		}
	}*/
			
	int dist[countg][max];
	for(i=0;i<countg;i++)
	{
		for(j=0;j<max;j++)
		dist[i][j]=0;
	}
	k=0;
	for(i=0;i<bin->size;i++)
	{
		
		if(i%11==0 && i!=0)
		{
			k++;
		}
		
			ptr=bin->arr[i].head;
			while(ptr!=NULL)
			{
				t=g->arr[ptr->vertex].bin_no;
				dist[k][t]++;
				ptr=ptr->next;
			}
		
	}
	 
	/*printf("\nDistribution\n");	 
	for(i=0;i<countg;i++)
	{
		for(j=0;j<max;j++)
		printf("%d\t",dist[i][j]);

		printf("\n");
	}*/			
	 
	 
  
}
void form_superedge_zero_bin(struct bucket *bin,graph *g,int countg)
{

	int i,j;	
	struct node *bptr,*lptr;
	struct node *ptr; 
	for(i=0;i<countg;i++)
	{	
				
		j=i*11;
		ptr=bin->arr[j].head;
		form_supernodes(ptr,g);
		lptr=g->arr[g->load].link_supernode;
		while(lptr!=NULL)
		{
			bptr=g->arr[lptr->vertex].head;
			while(bptr!=NULL)
			{
				if(!isPresent(g->arr[g->load].head,bptr->vertex))
				addedge(g,g->load,bptr->vertex);
				bptr=bptr->next;
			}
			lptr=lptr->next;
		}
		 
		 
	}
}

void form_supernodes(struct node *head,graph *g)
{
	struct node *ptr=head;
	int cnt=0;
	struct link *q=(struct link *)malloc(sizeof(struct link));
	while(ptr!=NULL)
	{
		if(g->arr[ptr->vertex].comp_score==1)
		{
			cnt++;
			q->link=addlink(q->link,ptr->vertex);
					
		}
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
		no_of_supernodes++;
	}

	q->link=NULL;
	

}

/*void form_supernodes(struct bucket *bin,graph *g,int countg)
{
	int i,j,cnt;
	struct link *q=(struct link *)malloc(sizeof(struct link));
	struct node *ptr;
	for(i=0;i<countg;i++)
	{
		j=i*11;
		cnt=0;
		
		q->link=NULL; 
		while(j<(i*11+11))
		{
			ptr=bin->arr[j].head;
			while(ptr!=NULL)
			{
				if(g->arr[ptr->vertex].comp_score==1)
				{
					cnt++;
					q->link=addlink(q->link,ptr->vertex);
					
				}
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
				no_of_supernodes++;
			
			}
			q->link=NULL;
			j++;
		}
		
	}
}*/
struct inter *intersection(struct inter *mat,int *a,int pos,int n1)
{
	int i,k,xor1,flaga=0,p1;
	int visited[n1];
	for(i=0;i<n1;i++)
	visited[i]=0;

	for(i=0;i<n1;i++)
	{
		xor1= mat->a[pos][i] ^ a[i];
		if(xor1==1)
		{
			if(mat->a[pos][i]==1)
			{
				visited[i]=1;
				flaga=1;
				mat->a[pos][i]=0;
			}
		}
	}
	
	if(flaga==1)
	{
		mat->size=mat->size+1;
		mat->a=(int **)realloc(mat->a,(sizeof(int *)*mat->size));
		p1=mat->size-1;
		mat->a[p1]=(int *)malloc(sizeof(int)*n1);
		
		for(i=0;i<n1;i++)
		mat->a[p1][i]=visited[i];

	}

	return mat;
}
		
		 
		
	
void js(double **mat,int *elem,int n,graph *g)
{
	int j,k;
	for(k=0;k<n;k++)
	{
		for(j=0;j<n;j++)
		{
			mat[k][j]=jsv(g->arr[elem[k]].head,g->arr[elem[j]].head);
		}
	}

	for(k=0;k<n;k++)
	{
		for(j=0;j<n;j++)
		printf("%lf\t",mat[k][j]);

		printf("\n");
	}
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
void push(struct node** head_ref, int new_data)
{
    
    struct node* new_node =
        (struct node*) malloc(sizeof(struct node));
 
    
    new_node->vertex = new_data;
 
    
    new_node->next = (*head_ref);
 
    
    (*head_ref) = new_node;
}

int isPresent(struct node *head, int data)
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
 
struct node *getIntersection(struct node *head1, 
                              struct node *head2)
{
    struct node *result = NULL;
    struct node *t1 = head1;
 
     
    while (t1 != NULL)
    {
        if (isPresent(head2, t1->vertex))
            push (&result, t1->vertex);
        t1 = t1->next;
    }
 
    return result;
}
int getno(struct node *head)
{
	int cnt=0;
	struct node *ptr=head;
	while(ptr!=NULL)
	{
		cnt++;
		ptr=ptr->next;
	}

	return cnt;
}
double jsv(struct node *head1,struct node *head2)
{
	struct node *temp;
	int t1,t2;
	double res;

	temp=getIntersection(head1,head2);
	t1=getno(temp);

	temp=merge(head1,head2);
	t2=getno(temp);

	res=(double)t1/t2;

	return res;

}
int maxn(int a,int b)
{
	if(a>b)
	return a;
	else
	return b;
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];  
    int i = (low - 1);  
 
    for (int j = low; j <= high- 1; j++)
    {
        
        
        if (arr[j] <= pivot)
        {
            i++;    
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
 
void quickSort(int arr[],int low,int high)
{
    if (low < high)
    {
         
        int pi = partition(arr, low, high);
 
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int search(int arr[],int l,int r,int key)
{
	if(l<=r)
	{
		int mid=l+(r-l)/2;
		if(arr[mid]==key)
		return mid;
		else if(arr[mid]<key)
		return search(arr,mid+1,r,key);
		else
		return search(arr,l,mid-1,key);
	}
	return -1;
}
 
		
				
 

		
							 
	
			
		
	

