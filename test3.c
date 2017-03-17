#include <stdio.h>
#include <stdlib.h>
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
 
int change=0;
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

struct group
{
	int current;
	struct node *list;
};
struct adjlist
{
	struct node *head;
	int degree;
	int bin_no;

	int grp_no;

	int  group;
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
	int grplength;
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

	for(i=0;i<v;i++)
	{
		tmp=g->arr[i].degree;
		tmp=log(tmp);
		t=(int)(tmp*10);

		 
		//printf("%lf\n",tmp);
		g->arr[i].bin_no=t;
		//printf("%d\n",g->arr[i].bin_no);
	}

	max=g->arr[0].bin_no;
	for(i=0;i<v;i++)
	{
		if(g->arr[i].bin_no>max)
		max=g->arr[i].bin_no;
	}

	max=max+1;

	struct bin *bin=(struct bin *)malloc(sizeof(struct bin));
	bin->a=(struct binlist *)malloc(sizeof(struct binlist)*max);

	struct node *q;
		
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
		

	 
	
	int visited[v];
	int n1=0;

	//int elem[3];
	int pos1,pos2;

	pos1=(max-1)/10;
	for(i=0;i<v;i++)
	visited[i]=0;

	struct node *ptr,*nptr,*ptrs;
	for(i=max-10;i<max;i++)
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
				pos2=(g->arr[nptr->vertex].bin_no)/10;
				if(pos2==pos1-1){				
				if(visited[nptr->vertex]==0)
				{
					n1++;
					visited[nptr->vertex]=1;
				}
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
	modv=v;
	 
	lsh(adjmat.mat,adjmat.elements,n1,g);
	 
	// printf("\n%d",change);
	 

	/*for(i=0;i<n1;i++)
	{
		for(j=0;j<n1;j++)
		printf("%d\t",adjmat.mat[i][j]);

		printf("\n");
	}*/

	//print(g);
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



void lsh(int **a,int *elements,int n1,graph *g)
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
	/*printf("Elements:\n");
	 for(i=0;i<n1;i++)
	printf("%d\t",elements[i]);


	printf("\n\nHASH SLOTS\n\n");
	for(i=0;i<nh;i++)
	{
		for(j=0;j<n1;j++)
		printf("%d\t",M[i][j]);

		printf("\n\n");
	}*/
	

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
		/*printf("\nENtered initializing grp no\n");
		for(i=0;i<g->v;i++)
		{
			ptr=grpun[i].list;
			if(ptr!=NULL)
			{
				printf("%d:\t",i);
				while(ptr!=NULL)
				{
					printf("%d___",ptr->vertex);
					ptr=ptr->next;
				}
				printf("\n");
			}
		}*/
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

	//printf("\nBUCKET :\n");

	/*printf("GROUPING %d,%d\n",j-(band_no-1),j);

	for(i=0;i<tempb->size;i++)
	{
		ptr=tempb->arr[i].head;
		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{
				printf("%d->",ptr->vertex);
				ptr=ptr->next;
			}
			printf("\n");
		}
	}*/

	 
	 
	
	
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
				
				s1=getno(getIntersection(g->arr[ptr->vertex].head,cpybucket->arr[i].head));
				ptr->score=(double)s1/cpybucket->arr[i].grplength;
				//printf("%lf->",ptr->score);
				ptr=ptr->next;
			}
			//printf("\n");
			cnt++;

		}
	}

	struct bucket * bin=(struct bucket *)malloc(sizeof(struct bucket));
	bin->size=cnt*11;
	bin->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*bin->size);

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
				tnode->next=bin->arr[t].head;
				bin->arr[t].head=tnode;

				ptr=ptr->next;
			}
			cnt+=11;
		}
	}

	cnt=0;
	int nvsize;
	for(i=0;i<bin->size;i++)
	{
		//if(i%11==0)
		//printf("\n Group \n");
	
		cnt=0;
		ptr=bin->arr[i].head;
		while(ptr!=NULL)
		{
			cnt++;
			ptr=ptr->next;
		}

		if(cnt>100)
		{
			nptr=bin->arr[i].head;
			nvsize=cnt;
		}

		//printf("%d\t",cnt);
		
	}

	cnt=0;
	int nvarr[nvsize];
	while(nptr!=NULL)
	{
		nvarr[cnt++]=nptr->vertex;
		nptr=nptr->next;
	}

	quickSort(nvarr,0,nvsize-1);

	/*printf("\nSort of %d subelements:\n",nvsize);

	for(i=0;i<nvsize;i++)
	printf("%d\n",nvarr[i]);*/
	 
	graph *sgraph=creategraph(nvsize);
	
	for(i=0;i<nvsize;i++)
	{
		nptr=g->arr[nvarr[i]].head;
		sgraph->arr[i].head=nptr;
	}

	/*printf("\nSTep 1:\n\n");
	for(i=0;i<nvsize;i++)
	{
		ptr=sgraph->arr[i].head;

		printf("\n%d",nvarr[i]);
		while(ptr!=NULL)
		{
			printf("->%d",ptr->vertex);
			ptr=ptr->next;
		}
		printf("\n");
	}*/

	struct node *prevptr,*head;

	for(i=0;i<nvsize;i++)
	{
		ptr=sgraph->arr[i].head;
		prevptr=NULL;

		if(ptr->next==NULL ||ptr==NULL)
		{
			struct node *tnode=ptr;
			free(tnode);
			sgraph->arr[i].head=NULL;
		}
		else{
		head=ptr;
		while(ptr!=NULL)
		{
			if(search(nvarr,0,nvsize-1,ptr->vertex)==-1)
			{
				if(prevptr==NULL)
				{
					struct node *tnode=ptr;
					free(tnode);
					ptr=ptr->next;
					head=ptr;
				}
				else
				{	
					struct node *tptr=ptr;
					prevptr->next=ptr->next;
					free(tptr);
					ptr=ptr->next;
				}
				
			}
			else
		 	{
				prevptr=ptr;
				ptr=ptr->next;
			}
			
		}

		sgraph->arr[i].head=head;

		}
	}

	printf("##no of vertices=%d\n",nvsize);
	//printf("\nSubgraph\n\n");
	for(i=0;i<nvsize;i++)
	{
		ptr=sgraph->arr[i].head;

		//printf("\n%d->",nvarr[i]);

		while(ptr!=NULL)
		{
			printf("%d\t%d\n",nvarr[i],ptr->vertex);
			ptr=ptr->next;
		}
		//printf("\n");

		ptr=NULL;
	}
			


	cpy->size=bin->size;

	cpy->a=(int **)malloc(sizeof(int *)*cpy->size);
	for(i=0;i<cpy->size;i++)
	{
		cpy->a[i]=(int *)malloc(sizeof(int)*n1);
		for(k=0;k<n1;k++)
		cpy->a[i][k]=0;
	}

	//printf("\nRESULT\n");
	for(i=0;i<cpy->size;i++)
	{
		ptr=bin->arr[i].head;
		if(ptr!=NULL)
		{

			while(ptr!=NULL)
			{
			//printf("%d->",ptr->vertex);
			t=posn(elements,n1,ptr->vertex);
			cpy->a[i][t]=1;
			ptr=ptr->next;
			}
			//printf("\n");
		}
	}
	
	

	
	
	 		
 
	
		
	
	
	 

	 
		
	

	max=max/10;
	int distribution[cpy->size][max];
	 

	for(i=0;i<cpy->size;i++)
	{
		for(j=0;j<max;j++)
		distribution[i][j]=0;
	}
	int posng;
	int count[cpy->size];
	for(i=0;i<cpy->size;i++)
	count[i]=0;

	for(i=0;i<cpy->size;i++)
	{
		for(j=0;j<n1;j++)
		{
			 if(cpy->a[i][j]==1)
				count[i]++;
		}			
		 
	}

	 
	for(i=0;i<cpy->size;i++)
	{
		for(j=0;j<n1;j++)
		{
			if(cpy->a[i][j]==1)
			{
				
				t=(g->arr[elements[j]].bin_no)/10;
				if(t==max-1 && count[i] >2)
				posng=i;
				distribution[i][t]++;
			}
		}
		
	}

	
	/*for(i=0;i<cpy->size;i++)
	{
		if(count[i]>2){
		for(j=0;j<max;j++)
		{
			printf("%d\t",distribution[i][j]);
			
		}
		printf("\n");
		}
	}*/

	 
	/*for(i=0;i<cpy->size;i++)
	{
		if(count[i]>2)
		printf("%d\n",count[i]);
	}

	
	int n=getno(g->arr[elements[pos]].head);
	//printf("\n%d",n);
	
	int *elem=(int *)malloc(sizeof(int)*n);

	i=0;
	struct node *ptr=g->arr[elements[pos]].head;
	while(ptr!=NULL)
	{
		elem[i++]=ptr->vertex;
		ptr=ptr->next;
	}
	double **jsmat=(double **)malloc(sizeof(double *)*n);
			
	for(j=0;j<n;j++)
	jsmat[j]=(double *)malloc(sizeof(double)*n);

	js(jsmat,elem,n,g);
	*/

	/*ptr=NULL;
	for(i=0;i<cpy->size;i++)
	{	
		 
		if(count[i]>2 )
		//if(i==posng)
		{
		
			

			double **jsmat;

			int *elem;
			int pos=0,n=0;
			n=count[i];
			 

			jsmat=(double **)malloc(sizeof(double *)*n);
			
			for(j=0;j<n;j++)
			jsmat[j]=(double *)malloc(sizeof(double)*n);

			elem=(int *)malloc(sizeof(int)*n);

		//	printf("\n Elements:\n");
			
			for(j=0;j<n1;j++)
			{
				if(cpy->a[i][j]==1)
				{
					elem[pos++]=elements[j];
					//printf("%d\t",elements[j]);
				}
			}
			/*for(k=0;k<n;k++)
			printf("%d\n",elem[k]);

			for(k=0;k<n;k++)
			{
				ptr=g->arr[elem[k]].head;
				while(ptr!=NULL)
				{
					printf("%d->",ptr->vertex);
					ptr=ptr->next;
				}
				printf("\n\n");
			}//
			
			printf("\nn=%d\n",n);
			printf("\nJACCARD SIMILARITY MATRIX\n");
			js(jsmat,elem,n,g);
			
			//if(n!=0)
			//break; 
			 
			elem=NULL;
			jsmat=NULL;

			//for(j=0;j<n;j++)
			//printf("%d\n",elem[j]);
			
			
		}
	}*/

	 
	 
}
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
		
				
 

		
							 
	
			
		
	

