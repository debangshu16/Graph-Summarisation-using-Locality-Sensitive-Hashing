#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
 
#include <time.h>
#define RED 1
#define BLUE 0
#define UNCOLOURED -1


struct hash
{
	int a;
	int b;
	
		
};
struct node
{
	int vertex;
	double score;
	struct node *next;
};
struct edge
{
	int source;
	int dest;
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
	struct node *link_supernode;
	int no_of_members;
	int has_superedge;
	struct edge_correction *edges;
	int no_of_missing_edges;
	struct edge **correction;
	  
	
	int colour;
	float error;
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

struct que
{
	struct node *rear,*front;
};
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
	int no_of_groups;
};

struct inter
{
	int **a;
	int size;
	int index;
};

void printList(struct node *);
graph* creategraph(int v);
int posn(int *elements,int n,int key);
int h(int,int,int);
struct node* newnode1(int);
void scoring_nodes(graph *g);
int form_bipartite(struct bucket *,graph *g,int);
void addedge(graph *,int,int);
struct node *merge(struct node *,struct node *);
void push(struct node **,int);
struct inter *intersection(struct inter*,int *,int,int);
double jsv(struct node *,struct node *); 
void quickSort(int a[],int,int); 
int maxn(int,int);
struct node *getIntersection(struct node *,struct node *);
int search(int a[],int,int,int);
struct bucket* lsh(int **,int *,int,graph *,int);
struct adjmat* create_adjmat(struct bin *,graph *,int[],int);
int getno(struct node *);
int isPresent(struct node *,int);
void form_superedge_zero_bin(struct bucket*,graph*,int);
int form_supernodes(struct node*,graph *);
void form_superedge_last3(struct bucket *,graph *,int);
float calerror_bipartite(graph *,int,int);
int cal_supernode_adjacency(int vertex,graph *g);
struct node* addlink(struct node *head,int key);
struct que * createque();
void enque(struct que *q,int k);
struct node *deque(struct que *q);
bool isempty(struct que *q);
int isPresentInSortedList(struct node *,int); 
void test(graph *g);
void print(graph *g);
bool isListSorted(struct node *);
struct node * pushToLast(struct node *,int,struct node **);
void reverse(struct node **);
void nodesCompressed(struct node *,graph *);
struct node *mergeNormal(struct node *,struct node *);
struct node *getIntersectionNormal(struct node *,struct node *);
struct node *addlinkToLast(struct node *,int);
void print_graph_score(graph *);

