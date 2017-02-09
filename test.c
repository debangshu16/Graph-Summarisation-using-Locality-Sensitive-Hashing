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
	
	return s%modv;
} 

#define h1(x) (2*x+1)
#define h2(x) (x+1)%100 
//#define g1(x) x%2096
int change=0;
struct node *merge(struct node *,struct node *);
struct inter *intersection(struct inter*,int *,int,int);
double jsv(struct node *,struct node *);

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
};
struct bucket
{
	struct bucketlist *arr;
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

	for(i=0;i<v;i++)
	visited[i]=0;

	struct node *ptr,*nptr;
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
	modv=n1;
	//printf("%d\t",n1);
	lsh(adjmat.mat,adjmat.elements,n1,g);

	// printf("\n%d",change);
	 

	/*for(i=0;i<n1;i++)
	{
		for(j=0;j<n1;j++)
		printf("%d\t",adjmat.mat[i][j]);

		printf("\n");
	}*/
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

	int i,j,r=n1,c=n1,k,temp1,temp,cntb=0;

	struct node *ptr;

	int grouping[g->v];

	for(i=0;i<n1;i++)
	grouping[i]=-1;

	struct inter *cpy=NULL,*cpy2=NULL;

	 
	srand(time(NULL));

	
	int nh=34;
	int M[nh][n1];

	struct hash hash[nh];

	for(i=0;i<nh;i++)
	{
		hash[i].a= (rand()%nh)*2+1;
		hash[i].b=(rand()%100)+1;
	}

	 
	 	 
	 
	 
	
	for(i=0;i<nh;i++)
	{
		for(j=0;j<c;j++)
			M[i][j]=9999;
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

	 

	int s1,s2 ;
	
	j=0;
	
	
	struct inter *mat2=(struct inter *)malloc(sizeof(struct inter));

	 
	

	struct bucket *bucket=(struct bucket *)malloc(sizeof(struct bucket));
	
	bucket->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*n1);

	struct bucket *bucket2;
	int t;

	for(i=0;i<n1;i++)
	{
		t=(M[j][i]);
		ptr=newnode1(elements[i]);
		ptr->next=bucket->arr[t].head;
		bucket->arr[t].head=ptr;
			
	}
	
	
	 
	
	 
	for(i=0;i<n1;i++)
	{
		ptr=bucket->arr[i].head;
	
		if(ptr!=NULL)
		{
			cntb++;		

			while(ptr!=NULL)
			{
			
			 
				g->arr[ptr->vertex].group=cntb-1;
				g->arr[ptr->vertex].grp_no=i;
				ptr=ptr->next;
			}
		}
		
	}

	
	 
	
	
	bucket2=(struct bucket *)malloc(sizeof(struct bucket));
	 
	bucket2->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*n1);

	//cntb=0;

	for(i=0;i<n1;i++)
	{
		t=(M[j+1][i]);
		ptr=newnode1(elements[i]);
		ptr->next=bucket2->arr[t].head;
		bucket2->arr[t].head=ptr;
		
	}

	
	struct node *ptr2;
	for(i=0;i<n1;i++)
	{
		ptr=bucket2->arr[i].head;

		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{
								
				ptr2=ptr;				
				s1=g->arr[ptr2->vertex].group;
				temp1=g->arr[ptr->vertex].grp_no;
				
				while(g->arr[ptr2->vertex].group==s1)
				{
					
						
					ptr2=ptr2->next;
					

					
					if(ptr2==NULL)
					break;
				}
				if(ptr2!=NULL){
				temp=g->arr[ptr2->vertex].grp_no;
					
				if(temp1!=temp )
				{
					 
					bucket->arr[temp1].head=merge(bucket->arr[temp1].head,bucket->arr[temp].head);
					bucket->arr[temp].head=NULL;
					
					
				}
				

				}

				ptr=ptr->next;
				
				
				
			}
			
		}
		
	}

	
	
	cntb=0;
	for(i=0;i<n1;i++)
	{
		ptr=bucket->arr[i].head;
		if(ptr!=NULL)
		{
			cntb++;
			 
		}
	}
	
	int t1=0;
	
	mat2->size=cntb;
	mat2->a=(int **)malloc(sizeof(int*)*mat2->size);

	for(i=0;i<cntb;i++)
	mat2->a[i]=(int *)malloc(sizeof(int)*n1);

	for(i=0;i<n1;i++)
	{
		for(k=0;k<mat2->size;k++)
		mat2->a[k][i]=0;
	}

	 	 				
	

	for(i=0;i<n1;i++)
	{
		ptr=bucket->arr[i].head;
		if(ptr!=NULL)
		{
			
					
			while(ptr!=NULL)
			{
				t=posn(elements,n1,ptr->vertex);
				mat2->a[t1][t]=1;
				grouping[ptr->vertex]=t1;
				ptr=ptr->next;
			}
			t1++;
		}
	}

	bucket=NULL;
	bucket2=NULL;
	
	free(bucket);
	free(bucket2);

	for(j=2;j<nh;j+=2)
	{

	cntb=0;
		
	struct bucket *bucket1=(struct bucket *)malloc(sizeof(struct bucket));
	
	bucket1->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*n1);
 
	 

	 
	for(i=0;i<n1;i++)
	{
		t=(M[j][i]);
		ptr=newnode1(elements[i]);
		ptr->next=bucket1->arr[t].head;
		bucket1->arr[t].head=ptr;
			
	}
	
	
	 
	
	 
	for(i=0;i<n1;i++)
	{
		ptr=bucket1->arr[i].head;
	
		if(ptr!=NULL)
		{
			cntb++;		

			while(ptr!=NULL)
			{
			
			 
				g->arr[ptr->vertex].group=cntb-1;
				g->arr[ptr->vertex].grp_no=i;
				ptr=ptr->next;
			}
		}
		
	}

	
	struct bucket *bucket12=(struct bucket *)malloc(sizeof(struct bucket));
	
	bucket12->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*n1);
 
	
	
	 
	 
	 
	 

	for(i=0;i<n1;i++)
	{
		t=(M[j+1][i]);
		ptr=newnode1(elements[i]);
		ptr->next=bucket12->arr[t].head;
		bucket12->arr[t].head=ptr;
		
	}

	
	 
	for(i=0;i<n1;i++)
	{
		ptr=bucket12->arr[i].head;

		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{
								
				ptr2=ptr;				
				s1=g->arr[ptr2->vertex].group;
				temp1=g->arr[ptr->vertex].grp_no;
				
				while(g->arr[ptr2->vertex].group==s1)
				{
					
						
					ptr2=ptr2->next;
					

					
					if(ptr2==NULL)
					break;
				}
				if(ptr2!=NULL){
				temp=g->arr[ptr2->vertex].grp_no;
					
				if(temp1!=temp )
				{
					 
					bucket1->arr[temp1].head=merge(bucket1->arr[temp1].head,bucket1->arr[temp].head);
					bucket1->arr[temp].head=NULL;
					
					
				}

				}

				
				
				ptr=ptr->next;
				
			}
			
		}
		
	}

	cntb=0;
	for(i=0;i<n1;i++)
	{
		ptr=bucket1->arr[i].head;
		if(ptr!=NULL)
			cntb++;
	}

	struct inter *mat1=(struct inter *)malloc(sizeof(struct inter));

	mat1->size=cntb;
	
	mat1->a=(int **)malloc(sizeof(int*)*mat1->size);

	for(i=0;i<mat1->size;i++)
	{
		mat1->a[i]=(int *)malloc(sizeof(int)*n1);
		for(k=0;k<n1;k++)
		mat1->a[i][k]=0;
	}
	 
	t1=0;
	for(i=0;i<n1;i++)
	{
		ptr=bucket1->arr[i].head;
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

	t1=0;

	 

	for(i=0;i<mat1->size;i++)
	{
		for(k=0;k<n1;k++)
		{
			if(mat1->a[i][k]==1)
			{
				t1=grouping[elements[k]];
				mat2=intersection(mat2,mat1->a[i],t1,n1);
			}
		}
	}

	for(i=0;i<mat2->size;i++)
	{
		for(k=0;k<n1;k++)
		{
			if(mat2->a[i][k]==1)
			{
				grouping[elements[k]]=i;
			}
		}
	}
	 
	ptr=NULL;

	}
		
	cpy=mat2;			

	/*for(i=0;i<mat2->size;i++)
	{
		for(j=0;j<n1;j++)
		{
			if(mat2->a[i][j]==1)
			{
				printf("%d->",elements[j]);
			}
		}
		printf("\n");
	} */
	
		
	
	
	 

	 
		
	

	max=max/10;
	int distribution[cpy->size][max];
	 

	for(i=0;i<cpy->size;i++)
	{
		for(j=0;j<max;j++)
		distribution[i][j]=0;
	}
	int posng;

	for(i=0;i<cpy->size;i++)
	{
		for(j=0;j<n1;j++)
		{
			if(cpy->a[i][j]==1)
			{
				t=(g->arr[elements[j]].bin_no)/10;
				
				if(t==max-1)
				posng=i;
					 
				
				distribution[i][t]++;
			}
		}
	}

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
		if(count[i]>2){
		for(j=0;j<max;j++)
		{
			printf("%d\t",distribution[i][j]);
		}
		printf("\n");
		}
	}

	 
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

	for(i=0;i<cpy->size;i++)
	{	
		 
		if(count[i]>2 &&count[i]<=10 )
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
			
			for(j=0;j<n1;j++)
			{
				if(cpy->a[i][j]==1)
				elem[pos++]=elements[j];
			}
			
			printf("\nn=%d\n",n);
			printf("\nJACCARD SIMILARITY MATRIX\n");
			js(jsmat,elem,n,g);
			
			if(n!=0)
			break; 
			 
			elem=NULL;
			jsmat=NULL;

			//for(j=0;j<n;j++)
			//printf("%d\n",elem[j]);
			
			
		}
	}

	printf("\nFinal no of groups%d",cpy->size);
	 
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
	
 

		
							 
	
			
		
	

