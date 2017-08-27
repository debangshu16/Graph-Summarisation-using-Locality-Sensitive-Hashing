#include <stdio.h>
#include "functions.h"
extern int max;
struct bucket* lsh(int **a,int *elements,int n1,graph *g,int bin_index)
{

	int i,j,r=n1,c=n1,k,temp1,temp,cntb=0,t,t2,s1;

	struct node *ptr,*q ;
	struct node *nptr=NULL,*ptr2=NULL;
	srand(time(NULL));

	double time,tot_time=0;
	
	int nh=30,band_no=6,band,lim;
	int M[nh][n1];
	int hashValue[nh];

	struct hash hash[nh];

	//create random hash function
	for(i=0;i<nh;i++)
	{
		hash[i].a= (rand()%nh)*2+1;
		hash[i].b=(rand()%100)-(rand()%100) +1;
	}
	 
	
	//specific hash functions
	/*FILE *fp=fopen("hash_function.txt","r");
	for(i=0;i<nh;i++)
	{
		fscanf(fp,"%d,%d",&hash[i].a,&hash[i].b);
	}

	fclose(fp);
	*/
	 
	 	 
	for(i=0;i<nh;i++)
	{
		for(j=0;j<c;j++)
			M[i][j]=g->v;
	}

	  

	for(i=0;i<r;i++)
	{
		for(k=0;k<nh;k++)
		hashValue[k]=h(hash[k].a,hash[k].b,i);
		for(j=0;j<c;j++)
		{
			if(a[i][j]==1)
			{
				for(k=0;k<nh;k++)
				{
					if(hashValue[k] < M[k][j])
						M[k][j]=hashValue[k];

					 			 
				}
			}
		}
	}
	struct bucket *cpybucket=(struct bucket *)malloc(sizeof(struct bucket));
	cpybucket->size=0;
	k=0;
	while(k<nh)
	{
		lim=k+band_no;
		char signature[n1][band_no * 4];
		for(i=0;i<n1;i++)
		strcpy(signature[i],"");

		for(i=0;i<n1;i++)
		{
			for(j=k;j<lim;j++)
			{
				char buffer[100];
				sprintf(buffer,"%d",M[j][i]);
				strcat(signature[i],buffer);
			}
		}

		//for(i=0;i<n1;i++)
		//printf("\n%s",signature[i]);
		
		 
		bool flag[n1];
		for(i=0;i<n1;i++)
		flag[i]=false;

		int count=0;
		for(i=0;i<n1;i++)
		{
			if(!flag[i])
			{
				bool flag1=false;
				for(j=i+1;j<n1;j++)
				{
			
					if(strcmp(signature[i],signature[j])==0)
					{
						//printf("%d,",k);
						flag[j]=true;
						flag1=true;
						count++;
					}
			
				}
			 
			}
		}
		struct bucket *tempb=(struct bucket *)malloc(sizeof(struct bucket));
		tempb->size=count;
		tempb->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*count);
		for(i=0;i<count;i++)
		tempb->arr[i].grplength=0;

		for(i=0;i<n1;i++)
		flag[i]=false;
		count=0;
		for(i=0;i<n1;i++)
		{
			bool tflag=false; 
			if(!flag[i])
			{
				for(j=i+1;j<n1;j++)
				{
					if(strcmp(signature[i],signature[j])==0)
					{
						tflag=true;
						flag[j]=true;
						tempb->arr[count].head=addlink(tempb->arr[count].head,elements[j]);
						tempb->arr[count].grplength++;
						 
					}
				}
				if(tflag)
				{
					tempb->arr[count].head=addlink(tempb->arr[count].head,elements[i]);
					tempb->arr[count].grplength++;
					 
					count++;
				}
			}
		}
		if(cpybucket->size==0)
		{
			cpybucket->size=tempb->size;
			cpybucket->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*tempb->size);
			for(i=0;i<tempb->size;i++)
			{
				cpybucket->arr[i].head=tempb->arr[i].head;
				cpybucket->arr[i].grplength=tempb->arr[i].grplength;
				/*while(ptr!=NULL)
				{
					cpybucket->arr[i].head=addlink(cpybucket->arr[i].head,ptr->vertex);
					ptr=ptr->next;
				}*/
			}
		}
		k+=band_no;
	}
	
	
	 
	for(i=0;i<cpybucket->size;i++)
	{
		if(cpybucket->arr[i].grplength<=2)
			cpybucket->arr[i].head=NULL;
		
	}
	for(i=0;i<cpybucket->size;i++)
	{
		ptr=cpybucket->arr[i].head;
		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{
				printf("%d,",ptr->vertex);
				ptr=ptr->next;
			}
			printf("\n");
		}
	} 

	/*for(i=0;i<cpybucket->size;i++)
	{
		ptr=cpybucket->arr[i].head;
		while(ptr!=NULL)
		{
			printf("%d,",ptr->vertex);
			ptr=ptr->next;
		}
		printf("\n");
	}*/
			 
 
	 
	int countg=0; 
	for(i=0;i<cpybucket->size;i++)
	{
		ptr=cpybucket->arr[i].head;
		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{ 
				s1=getno(getIntersection(g->arr[ptr->vertex].head,cpybucket->arr[i].head));
				ptr->score=(double)s1/(cpybucket->arr[i].grplength-1);
				 
				ptr=ptr->next;
			}
			countg++;
		}
			//printf("\n");
			 
		
	}

	 
	 
	 

	struct bucket *bin=(struct bucket *)malloc(sizeof(struct bucket));
	bin->size=cpybucket->size*11;
	bin->no_of_groups=countg;
	bin->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*bin->size);

	for(i=0;i<bin->size;i++)
	bin->arr[i].grplength=0;

	struct node *tnode;
	int cnt=0;

	 
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

	return bin;
  
}
