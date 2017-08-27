#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
struct node
{
	int vertex;
	struct node *next;
	double score;
};
struct bucketlist
{
	int grouplength;
	struct node *head;
};
struct bucket
{
	int size;
	struct bucketlist *arr;
};
struct unionPointer
{
	struct node *point;
};
struct node *newnode1(int v)
{
	struct node *n=(struct node *)malloc(sizeof(struct node));
	n->vertex=v;
	n->next=NULL;
	return n;
}
struct node *addlink(struct node *head,int data)
{
	struct node *ptr=(struct node *)malloc(sizeof(struct node));
	ptr->vertex=data;
	ptr->next=NULL;
	if(head==NULL)
	head=ptr;
	else
	{
		ptr->next=head;
		head=ptr;
	}
	return head;
}
struct node *addlinkToLast(struct node *head,int v)
{
	struct node *temp=newnode1(v);
	struct node *ptr=head;
	if(ptr==NULL)
	return temp;
	while(ptr->next!=NULL)
	{
		ptr=ptr->next;
	}
	ptr->next=temp;
	return head;
}
int main()
{
	int nh=4,n1=7,band_no=2,lim,noOfBands;
	int i,k,j,count=0;
	noOfBands=nh/band_no;
	//int arr[nh][n1];
	srand(time(NULL));
	clock_t start,end;
	start=clock();
	/*for(i=0;i<nh;i++)
	{
		for(j=0;j<n1;j++)
		{
			arr[i][j]=rand()%5+1;
		}
	}*/
	 
	 
	 
	
	
	 
	int arr[4][7]={{44,12,10,12,44,5,10},{20,1,3,1,20,20,3},{19,25,4,25,19,100,2},{12,16,18,16,12,16,9}};

	printf("\nSignature matrix\n");
	for(i=0;i<nh;i++)
	{
		for(j=0;j<n1;j++)
		printf("%d ",arr[i][j]);
	
		printf("\n");
	}
	char signature[noOfBands][n1][50];
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
				sprintf(buffer,"%d",arr[k][j]);
				strcat(signature[count][j],buffer);
			}
		}
		count++;
	}

	for(i=0;i<noOfBands;i++)
	{
		printf("\n SIgnatures of %d bands:\n",(i+1));
		for(j=0;j<n1;j++)
		printf("%s\n",signature[i][j]);
	}

	printf("\nResult:\n");

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
	bucket->arr[i].head=NULL;

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
						bucket->arr[count].head=addlink(bucket->arr[count].head,k);
						break;
					}
				}
				 
			}
			if(flag)
			{
				//printf("%d\n",j);
				bucket->arr[count].head=addlinkToLast(bucket->arr[count].head,j);
				count++;
			}
		}
	}

	for(i=0;i<bucket->size;i++)
	{
		struct node *ptr=bucket->arr[i].head;
		while(ptr!=NULL)
		{
			printf("%d,",ptr->vertex);
			ptr=ptr->next;
		}
		printf("\n");
	}

	end=clock();
	double time=(double)(end-start)/CLOCKS_PER_SEC;
	printf("\n%lf\n",time);
				
}
	
