#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 20
#define INFINITY 10000
int visited[MAXVEX]={0};
typedef struct Arcnode
{
	int arcnode[MAXVEX][MAXVEX];
	int vexnum1;	//顶点数 
	int arcnum2;	//弧数 
	char vex[MAXVEX];
}AdjMatrix;
typedef struct Queue 
{
		char Array[MAXVEX];
		int rear;
		int front;
}Queue;
int Locate(AdjMatrix *G,char v)
{
	int i;
	for(i=1;i<=G->vexnum1;i++)
	{
		if(G->vex[i] == v)
		{
			return i;
		}
			
	}	
		return 0;
}
void Create(AdjMatrix *G)
{
	int i,j,k;
	char num1;
	char num2;
	scanf("%d %d",&G->vexnum1,&G->arcnum2);
	getchar();
	for(i=1;i<= G->vexnum1;i++)
	{
			for(i=1;i<= G->vexnum1;i++)
		{
			G->arcnode[i][j]=0;
		}
	}
	for(i=1;i<=G->vexnum1;i++)
	{
		scanf("%c",&G->vex[i]);
	}
	for(k=1;k<=G->arcnum2;k++)
	{
		getchar();
		scanf("%c",&num1);
		i=Locate(G,num1);
		scanf("%c",&num2);
		j=Locate(G,num2);
		G->arcnode[i][j]=1;
		//scanf("%d",&weight);
		//G->arcnode[i][j]=weight;
	}
}

void Init(Queue *p)
{
	p->front=p->rear=MAXVEX;
 } 
 void IN(Queue *p,char v1)
 {
 	p->rear=(p->rear+1)%MAXVEX;
 	p->Array[p->rear]=v1;
 }
 
 int Empty(Queue p)
 {
 	if(p.rear==p.front)
 		return 1;
 	else
 		return 0;
 }
 void Delete(Queue *p,char *v2)
 {
 	p->front=(p->front+1)%MAXVEX;
 	 *v2=p->Array[p->front];
 }
 void Output(AdjMatrix *G)
 {
 	int i;
 	int temp1,temp2;
 	
 	for(i=1;i<=G->vexnum1;i++)
 	{
 		temp1=temp2=0;
 		printf("%c ",G->vex[i]);
 		for(int j=1;j<=G->vexnum1;j++)
 		{
			 	if(G->arcnode[i][j]==1)
 			{
 				temp1++;	
			 }
		}
		for(int k=1;k<=G->arcnum2;k++)
	 	{
	 		if(G->arcnode[k][i]==1)
	 		{
	 			temp2++;
		 	}
	 	}
 		printf("%d %d %d\n",temp1,temp2,temp1+temp2);

	 }	
  } 
  char FirstAdjMatrix(AdjMatrix *G,char v)
  {
  	int i;
  	for(i=1;i<=G->vexnum1;i++)
  	{
  		if(G->vex[i]==v)
  			break;
	  }
	  for(int j=1;j<=G->vexnum1;j++)
	  {
	  	if(G->arcnode[i][j]==1&& visited[G->vex[j]]==0)
	  	{
	  		return G->vex[j];
		  }
	  }
	  return -1;
  }
  int NextAdjMatrix(AdjMatrix *G,char v,char v0)
  {
  	int i;
  	for (i = 1; i <= G->vexnum1; i++) 
	  {
        if (G->vex[i] == v) 
		{
            break;
        }
    }
    for (int j = 1; j <= G->vexnum1; j++) 
	{
        if (G->arcnode[i][j] == 1 && G->vex[j] != v0  && visited[G->vex[j]] == 0) 
		{
            return G->vex[j];
        }
    }
    return -1;
  }
  void DFS(AdjMatrix *G,char v0)		//深搜 
  {
  	printf("%c",v0);
  	visited[v0]=1;
  	int Temp;
	Temp= FirstAdjMatrix(G, v0);
    while (Temp != -1) 
	{
        if (!visited[Temp]) 
		{
            DFS(G, Temp);
			
            Temp = NextAdjMatrix(G, v0, Temp);
        }
    }

  }
  void Traverse(AdjMatrix *G)
  {
  	for (int i = 1; i <= G->vexnum1; i++) 
	  {
        if (!visited[G->vex[i]]) 
		{
            DFS(G, G->vex[i]);
        }
    }
  }
  void BFS(AdjMatrix *G,char v0)		//广搜 
  {
  	printf("%c", v0);
    visited[v0] = 1;
    Queue q;
    Init(&q);
    IN(&q, v0);
    int temp;
    while (!Empty(q)) 
	{
        char v;
        Delete(&q, &v);
        temp = FirstAdjMatrix(G, v);
        while (temp != -1)
		 {
            if (!visited[temp]) 
			{
                printf("%c",temp);
                visited[temp] = 1;
                IN(&q, temp);
            }
            temp = NextAdjMatrix(G, v, temp);
        }
    }

  }
  void ReTraverse(AdjMatrix *G)
  {
	for(int i=1;i<=G->vexnum1;i++)
  		visited[G->vex[i]]=0;
  	for(int i=1;i<=G->vexnum1;i++)
  	{
  		if(!visited[G->vex[i]])
  		{
  			BFS(G,G->vex[i]);
		  }
	  }
  }
  int main()
  {
  	AdjMatrix *G;
  	G = (AdjMatrix *)malloc(sizeof(AdjMatrix));
    Create(G);
    Output(G);
    Traverse(G);
    for (int i = 0; i < MAXVEX; i++) 
	{
        visited[i] = 0;
    }
    printf("\n");
    ReTraverse(G);
    printf("\n");
    return 0;

  }
  
