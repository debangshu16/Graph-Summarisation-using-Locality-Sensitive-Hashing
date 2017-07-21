#include <stdio.h>
#include "functions.h"
extern int max;
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

	//create random hash function
	/*for(i=0;i<nh;i++)
	{
		hash[i].a= (rand()%nh)*2+1;
		hash[i].b=(rand()%100)-(rand()%100) +1;
	}*/

	//specific hash functions
	FILE *fp=fopen("hash_function.txt","r");
	for(i=0;i<nh;i++)
	{
		fscanf(fp,"%d,%d",&hash[i].a,&hash[i].b);
	}

	fclose(fp);

	 
	 	 
	 
	 
	
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
				//if(g->arr[ptr->vertex].flag==0)
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
				else if(ptr->score==1)
				t=cnt+10;
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

	 
	
	/*FILE *fp1;

	
	
	for(i=0;i<countg;i++)
	{
		 
		
		for(j=i*11;j<(i*11+11);j++)
		{
			char filename[20];
			sprintf(filename,"score%d.txt",(j%11));
			fp1=fopen(filename,"a+");
			
			ptr=bin->arr[j].head;
			while(ptr!=NULL)
			{
				fprintf(fp1,"%lf\n",ptr->score);
				ptr=ptr->next;
			}
			fclose(fp1);
		}
	}*/
		 
	cnt=0; 
	int gd=0,sgd=0,gcount=0;
	//printf("\n Distribution for degree bin %d",bin_index);
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

	 

	/*printf("\n SCORE A ON GROUPS:\n"); 
	for(i=0;i<countg;i++)
	printf("%lf\n",bin->arr[(i*11)].grp_score);*/

	ptr=NULL;	
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
					if(g->arr[ptr->vertex].bin_no == bin_index)
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

	/*printf("\nFOr degree bin index %d\n",bin_index);
	for(i=0;i<countg;i++)
	{
		for(j=i*11;j<(i*11)+11;j++)
		{
			printf("%d\t",getno(bin->arr[j].head));
		}
		printf("\t Score=%lf\n",bin->arr[i*11].grp_score);
	}*/

	ptr=NULL;
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

	 
	fflush(stdin); 
	//form_superedge_zero_bin(bin,g,countg); 
	form_superedge_last3(bin,g,countg);
	
	 
	/*for(i=0;i<countg;i++)
	{
		 
		cnt=form_bipartite(bin,g,i);
		if(cnt!=-1)
		{
			if(!isPresent(g->arr[g->load].head,g->load-1))
			{	
				addedge(g,(g->load)-1,g->load);
				g->arr[(g->load)-1].error=g->arr[g->load].error=calerror_bipartite(g,g->load,(g->arr[g->load].head)->vertex);
			}
		}
		 
		for(j=0;j<g->v;j++)
		g->arr[j].colour=UNCOLOURED;
	}*/
							
  
  
}
