#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXINT 1000
#define ch 30
#define NUM 100
#define N 6
#define M 2*N-1
typedef char numcode[NUM];
typedef char charcode[ch];
typedef char* HuffmanCode[N] ;
typedef struct{
    int weight;
    int parent;
    int lchild;
    int rchild; 
}HTNode,HuffmanTree[M]; 
void select(HuffmanTree ht,int pos,int *s1,int *s2)
{
    int i,j,m1,m2;
    m1=m2=MAXINT;
    for(j=0;j<=pos;j++) 
	{
        if(ht[j].weight<m1&&ht[j].parent==-1)
		{
            m2=m1;*s2=*s1;
            *s1=j;m1=ht[j].weight;
        }
        else if(ht[j].weight<m2&&ht[j].parent==-1)
		{
            m2=ht[j].weight;
            *s2=j;
        }
    }
    
}
void CrtHuffmanTree(HuffmanTree ht,int w[],int n)
{
    int i,s1,s2,m;
    m=2*n-1;
    for(i=0;i<n;i++)
	{
        ht[i].weight=w[i];ht[i].parent=-1;
        ht[i].lchild=-1;ht[i].rchild=-1;
    }
    for(i=n;i<m;i++)
	{
        ht[i].weight=0;ht[i].parent=-1;
        ht[i].lchild=-1;ht[i].rchild=-1;
	}   
    /*Ñ¡Ôñ ºÏ²¢*/
    for(i=n;i<m;i++) 
	{
        select(ht,i-1,&s1,&s2);
        ht[i].weight=ht[s1].weight+ht[s2].weight;
        ht[s1].parent=i;
        ht[s2].parent=i;
        ht[i].lchild=s1;
        ht[i].rchild=s2;
    }
}
void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc,int n)
{
    char *cd;int STA,c,p,i;
    cd=(char*)malloc(n*sizeof(char));
    cd[n-1]='\0';   
    for(i=0;i<n;i++){
        STA=n-1;c=i;
        p=ht[i].parent;
        while(p!=-1){
            --STA;
            if(ht[p].lchild==c) cd[STA]='0';
            else    cd[STA]='1';
            c=p;p=ht[p].parent;
        }
        hc[i]=(char*)malloc((n-STA)*sizeof(char));        
        
        strcpy(hc[i],&cd[STA]);

    }
    free(cd);
}

void printcode(char s[],HuffmanCode hc)
{
    for(int i=0;i<N;i++){
        printf("%c:",s[i]);
        printf("%s\n",hc[i]);

    }
}
void chartocode(charcode c,char s[],HuffmanCode hc){
    char *p=c;  
    while(*p!='\0'){    
        for(int j=0;j<N;j++){
            if(*p==s[j])
                printf("%s",hc[j]);
        }
        p++;
    }
    printf("\n");   
}
void  numtochar(numcode ns,HuffmanTree ht,char s[])
{
    char *p=ns;
	int temp;
	HTNode g;
    while(*p!='\0'){
        g=ht[M-1];              
        while(g.lchild!=-1&&g.rchild!=-1&&(*p!='\0')){
            switch(*p){              
            case '0':temp=g.lchild;g=ht[g.lchild];break;
            case '1':temp=g.rchild;g=ht[g.rchild];break;
            }
            p++;
            
        }
        printf("%c",s[temp]);


    }
}
int main()
{ 
    HuffmanTree ht;
	HuffmanCode hc;
	charcode c;
	numcode ns;
    char s[N]={'A','B','C','D','E','F'};
    int  w[N];

    for(int i=0;i<N;i++)
	{
        scanf("%d",&w[i]) ;
    } 
    scanf("%s",&c);
    scanf("%s",&ns);

    CrtHuffmanTree(ht,w,6);


    CrtHuffmanCode(ht,hc,6);
    printcode(s,hc);
    chartocode(c,s,hc); 

    numtochar(ns,ht,s);
}

