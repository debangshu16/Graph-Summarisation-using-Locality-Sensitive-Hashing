#include "functions.h"
extern int modv;
int h(int a,int b,int x) 
{
	int s=0;
	

	s=(a*x)+b;

	s=abs(s);
	
	return s%modv;
} 


struct que * createque()
{
	struct que* q=(struct que *)malloc(sizeof(struct que));
	q->rear=q->front=NULL;
	return q;
}
void enque(struct que *q,int k)
{
	struct node *temp=newnode1(k);
	if(q->rear==NULL)
	{
		q->rear=q->front=temp;
		return;
	}
	q->rear->next=temp;
	q->rear=temp;
}
struct node *deque(struct que *q)
{
	if(q->front==NULL)
	return NULL;
	struct node *temp=q->front;
	q->front=q->front->next;
	
	if(q->front==NULL)
	q->rear=NULL;

	return temp;
}
bool isempty(struct que *q)
{
	if(q->rear==NULL)
	return true;
	else
	return false;
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
		
		 
		
	

 

