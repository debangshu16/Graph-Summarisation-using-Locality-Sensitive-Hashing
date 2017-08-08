//...........................INPUT FORMAT............
// 1.file name	2.No of vertices in graph 3.No of edges in graph
#include "functions.h"
int no_of_supernodes=0;
int max; 
int modv;

int main(int argc,char* argv[])
{
	int v=4039,e=88234;
	//long long int v=1965206,e=5533214;
	double tot_time=0;
	int i,src,dest,t;
	//char filename[100];
	//sprintf(filename,"%s",argv[1]);

	clock_t start,end;
	
	FILE *fp;
	fp=fopen("FB.txt","r");
	//fp=fopen(filename,"r");
	//fp=fopen("temporaryFile.txt","r");
	if(fp==NULL)
		perror("error:");
	
	 
	//long int v=atoi(argv[2]);
	//long int e=atoi(argv[3]);	

	double tmp,x;
	graph *g=creategraph(v);
	
	struct node *tmpp;	
	
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
		 
	for(i=0;i<max;i++)
	{
		dist[i]=bin->a[i].nn;
	}	
	
	 
	
	int visited[v];

	
	
	int pos1,pos2;

	pos1=(max-1);
	for(i=0;i<v;i++)
	visited[i]=0;

	struct node *ptr,*nptr,*ptrs;
	 
	int k=0;
	int **adjmat;
	int *elements;
	modv=v;

	double lsh_time; 
	while(k<max)
	{
		fflush(stdin);
		start=clock();
		struct adjmat * adjmat1=create_adjmat(bin,g,visited,k);

		
			 
		//printf("\nLSH ON %d nodes\n",adjmat1->n1);

		 
			
	 
		struct bucket *lsh_bin=lsh(adjmat1->mat,adjmat1->elements,adjmat1->n1,g,k);
		
		int countg=lsh_bin->no_of_groups;
		for(i=0;i<lsh_bin->size;i++)
		{
			if(lsh_bin->arr[i].head!=NULL)
				reverse(&lsh_bin->arr[i].head);
		} 
		 
		form_superedge_zero_bin(lsh_bin,g,countg); 
		form_superedge_last3(lsh_bin,g,countg);
	
		struct node *group=NULL; 
		for(i=0;i<countg;i++)
		{
		
			 
			cnt=form_bipartite(lsh_bin,g,i);
			if(cnt!=-1)
			{
				if(!isPresentInSortedList(g->arr[g->load].head,g->load-1))
				{	
					addedge(g,(g->load)-1,g->load);
					g->arr[(g->load)-1].error=g->arr[g->load].error=calerror_bipartite(g,g->load,(g->arr[g->load].head)->vertex);
				}
			}
					 
			for(j=0;j<g->v;j++)
			g->arr[j].colour=UNCOLOURED;

			 
		}
		scoring_nodes(g);
							
			 
		  
		 
		memset(visited,0,g->v*sizeof(visited[0]));

		 
		k++;
		end=clock();
		lsh_time=(double)(end-start)/CLOCKS_PER_SEC;
		printf("\nTime taken on lsh of degree bin no.%d of %d elements=%lf",k,adjmat1->n1,lsh_time);
		tot_time+=lsh_time;
		 	 
	}
	
	
	/*int choice=atoi(argv[4]);
	if(choice==1)
		test(g);
	else
		print(g);
	*/

	print(g);
		 
	double countcomp=0;
	for(i=0;i<g->v;i++)
	{
		countcomp+=(1-g->arr[i].comp_score)*g->arr[i].degree;
	}
	 

	printf("\n%lf out of %d edges not compressed\n",(countcomp/2),e);
	printf("\nTime taken=%lf\n",tot_time);
	 
}
 


		
				
 

		
							 
	
			
		
	

