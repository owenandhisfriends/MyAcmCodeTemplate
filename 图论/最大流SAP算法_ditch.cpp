#include<cstdio>
#include<cstring>
#include<vector>
#define maxn 1010
#define inf 1000000000
using namespace std;

struct edge{
	int v,c,next;
};
vector<edge> e;
int beg[maxn];
//
int last[maxn];
int d[maxn],cnt_d[maxn];
//
int n,m,st,ed,tot;
void add(int x,int y,int c)
{
	int nE=e.size();
	e.push_back(edge());
	e[nE].v=y;
	e[nE].c=c;
	e[nE].next=beg[x];
    beg[x] = nE;
}
void input()
{
	int x,y,c;
	e.resize(0);
	memset(beg,255,sizeof(beg));
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&x,&y,&c);
		add(x,y,c);
		add(y,x,0);
	}
	st=1; ed=n;
    
    tot=n+1;  //tot赋初始值
    for(int i=0;i<=tot;i++) last[i]=beg[i];  //注意last 要给初始值，而且不能放在add中，否则当无边时会出错。
}
int Min(int x,int y)
{
	return x<y?x:y;
}
int sap(int x,int now)
{	
	if(x==ed) return now;
	int i=last[x],minD=tot;
	int ext;	
	if(i!=-1)
	do{		
		if(e[i].c){		
			if(d[x]==d[e[i].v]+1){
				if((ext=sap(e[i].v,Min(now,e[i].c))))
				{
					e[i].c-=ext;
					e[i^1].c+=ext;
					last[x]=i;
					return ext;
				}
				if(d[st]>tot) return 0;
			}
			minD=Min(minD,d[e[i].v]);
		}
		i=e[i].next==-1?beg[x]:e[i].next;
	}while(i!=last[x]);
	if(--cnt_d[d[x]]==0) d[st]=tot+1;
	d[x]=minD+1;
	cnt_d[d[x]]++;
	return 0;
}
void max_flow()
{
	int ans=0;
	memset(d,0,sizeof(d));	
	memset(cnt_d,0,sizeof(cnt_d));
	while(d[st]<=tot)  //tot 表示流量图的最大点数
		ans+=sap(st,inf);
	printf("%d\n",ans);
}
int main()
{
	while(scanf("%d%d",&m,&n)!=EOF)
	{
		input();
		max_flow();		
	}
	return 0;
}

