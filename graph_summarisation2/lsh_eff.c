#include <stdio.h>
#include "functions.h"
extern int max;
struct bucket* lsh(int **a,int *elements,int n1,graph *g,int bin_index)
{

	int i,j,k,count=0,t;

	struct node *ptr;
	struct node *nptr=NULL,*ptr2=NULL;
	srand(time(NULL));

	double time,tot_time=0;
	
	int nh=30,band_no=6,noOfBands,lim;
	noOfBands=(nh/band_no);
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
		for(j=0;j<n1;j++)
			M[i][j]=g->v;
	}

	  

	for(i=0;i<n1;i++)
	{
		for(k=0;k<nh;k++)
		hashValue[k]=h(hash[k].a,hash[k].b,i);
		for(j=0;j<n1;j++)
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
	
	char signature[noOfBands][n1][band_no * 4];
	for(i=0;i<noOfBands;i++)
	{
		for(j=0;j<n1;j++)
		strcpy(signature[i][j],"");
	}

	for(i=0;i<nh;i+=band_no)
	{
		lim=i+band_no;
		for(j=0;j<n1;j++)
		{
			for(k=i;k<lim;k++)
			{
				char buffer[10];
				sprintf(buffer,"%d",M[k][j]);
				strcat(signature[count][j],buffer);
			}
		}
		count++;
	}

	/*for(i=0;i<noOfBands;i++)
	{
		printf("\n SIgnatures of %d bands:\n",(i+1));
		for(j=0;j<n1;j++)
		printf("%s\n",signature[i][j]);
	}

	printf("\nResult:\n");*/

	struct bucket *bucket =(struct bucket *)malloc(sizeof(struct bucket));
	count=0;
	bool inGroup[n1];


	for(i=0;i<n1;i++)
	inGroup[i]=false;

 	for(j=0;j<n1;j++)
	{
		bool flag=false;
		if(!inGroup[j])
		{	
			for(k=j+1;k<n1;k++)
			{
				int simCount=0;
				for(i=0;i<noOfBands;i++)
				{
					if(strcmp(signature[i][k],signature[i][j])==0)
					simCount++;
					if(simCount==(noOfBands/2))
					{
						flag=true;
						inGroup[k]=true;

						break;
					}
				}
			}
			if(flag)
			{
				//printf("%d\n",j);
				count++;
			}
		}
	}

	bucket->size=count;
	bucket->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*count);
	
	for(i=0;i<bucket->size;i++)
	{
		bucket->arr[i].head=NULL;
		bucket->arr[i].grplength=0;
	}

	for(i=0;i<n1;i++)
	inGroup[i]=false;

	count=0;
 	for(j=0;j<n1;j++)
	{
		bool flag=false;
		if(!inGroup[j])
		{	
			for(k=j+1;k<n1;k++)
			{
				int simCount=0;
				for(i=0;i<noOfBands;i++)
				{
					if(strcmp(signature[i][k],signature[i][j])==0)
					simCount++;
					if(simCount==(noOfBands/2))
					{
						flag=true;
						inGroup[k]=true;
						bucket->arr[count].head=addlink(bucket->arr[count].head,elements[k]);
						bucket->arr[count].grplength++;
						break;
					}
				}
				
			}
			if(flag)
			{
				//printf("%d\n",j);
				//bucket->arr[count].head=addlink(bucket->arr[count].head,elements[j]);
				bucket->arr[count].head=addlinkToLast(bucket->arr[count].head,elements[j]);
				bucket->arr[count].grplength++;
				count++;
			}
		}
	}

	for(i=0;i<bucket->size;i++)
	{
		if(bucket->arr[i].grplength<=2)
			bucket->arr[i].head=NULL;
		
	}

	/*for(i=0;i<bucket->size;i++)
	{
		ptr=bucket->arr[i].head;
		while(ptr!=NULL)
		{
			printf("%d,",ptr->vertex);
			ptr=ptr->next;
		}
		printf("\n");
	}*/
			 
 
	 
	int countg=0,s1; 
	for(i=0;i<bucket->size;i++)
	{
		ptr=bucket->arr[i].head;
		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{ 
				s1=getno(getIntersectionNormal(g->arr[ptr->vertex].head,bucket->arr[i].head));
				ptr->score=(double)s1/(bucket->arr[i].grplength-1);
				 
				ptr=ptr->next;
			}
			countg++;
		}
			//printf("\n");
			 
		
	}

	 
	 
	 

	struct bucket *bin=(struct bucket *)malloc(sizeof(struct bucket));
	bin->size=countg*11;
	bin->no_of_groups=countg;
	bin->arr=(struct bucketlist *)malloc(sizeof(struct bucketlist)*bin->size);

	for(i=0;i<bin->size;i++)
	bin->arr[i].grplength=0;

	struct node *tnode;
	int cnt=0;

	 
	for(i=0;i<bucket->size;i++)
	{
		ptr=bucket->arr[i].head;
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
