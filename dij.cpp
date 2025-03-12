#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>

using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int inf=0x7fffffff,maxm=500010;
struct edge{
    int to,dis,nxt;
}e[maxm];
struct node{
    int dis,pos;
    bool operator <(const node &x)const{return x.dis<dis;}
};
int hd[maxm],dis[maxm],cnt,vis[maxm];
int info[105][105];
int n,m,s;
void add(int u,int v,int w)
{
    cnt++;
    e[cnt].dis=w;
    e[cnt].to=v;
    e[cnt].nxt=hd[u];
    hd[u]=cnt;
}
priority_queue<node> q;
void dij()
{
    dis[s]=0;
    q.push((node){0,s});
    while(!q.empty())
    {
        node tmp=q.top();
        q.pop();
        int u=tmp.pos,d=tmp.dis;
        if(vis[u])continue;
        vis[u]=1;
        for(int i=hd[u];i;i=e[i].nxt)
        {
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].dis)
            {
                dis[v]=dis[u]+e[i].dis;
                if(!vis[v])q.push((node){dis[v],v});
            }
        }
    }
}
int main()
{
    //n个点
    n=read();
    for(int i=1;i<=n;i++)dis[i]=inf;
    //读入表格中数据
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            info[i][j]=read();
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
        {
            if(info[i][j]>0)
            {
                add(i,j,info[i][j]);
                add(j,i,info[i][j]);
            }
        }
    //s为起点
    cin>>s;
    dij();
    for(int i=1;i<=n;i++)cout<<dis[i]<<' ';
    return 0;
}
/*

*/
