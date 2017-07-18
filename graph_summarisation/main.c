//...........................INPUT FORMAT............
// 1.file name	2.No of vertices in graph 3.No of edges in graph
#include "functions.h"
int no_of_supernodes=0;
int max; 
int modv;

int main(int argc,char* argv[])
{
	//long int v=4039,e=88234;
	//int v=62,e=318;
	
	int i,src,dest,t;
	char filename[100];
	sprintf(filename,"%s",argv[1]);
	FILE *fp;
	//fp=fopen("FB.txt","r");
	fp=fopen(filename,"r");
	//fp=fopen("dolph.txt","r");
	if(fp==NULL)
		perror("error:");
	
	 
	long int v=atoi(argv[2]);
	long int e=atoi(argv[3]);	

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
		 
	for(i=0;i<max;i++)
	{
		dist[i]=getno(bin->a[i].head);
	}	
	
	 
	
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
		 
		  
		fflush(stdin);
		for(i=0;i<g->v;i++)
		{
			 
			visited[i]=0;
			 
		}

		 
		k++;
		 	 
	}
	
	/*int choice=atoi(argv[4]);
	if(choice==1)
		test(g);
	else
	{
	 */	 
		double counta,countb; 
		for(i=g->v;i<(g->v+no_of_supernodes);i++)
		{	
			ptr=g->arr[i].head;
			if(ptr!=NULL) //&& getno(g->arr[i].link_supernode)>2)
			{
				printf("\n\n%d \t",g->arr[i].id);
		
		
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
			}

			//if(ptr!=NULL &&getno(g->arr[i].link_supernode)>2)
			//{
				if(g->arr[i].error >=0.50)
				counta++;

				countb++;
			//}
			 
				 
		}

		printf("\n\n\n\n ERROR =%lf %%\n%lfout of %lf groups",(counta/countb)*100,counta,countb);
	 
		//print(g); 

	//}

	 
	   
	 
}
 


		
				
 

		
							 
	
			
		
	

