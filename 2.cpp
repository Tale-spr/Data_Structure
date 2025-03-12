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
const int maxm=4e5+5,maxn=5005;
struct edge{
    int to,nxt,dis;
}e[maxm];
int hd[maxn],dis[maxn],vis[maxm],cnt,n,tot,ans=0,now=1;
// 添加一条边，链式前向星
// 添加一条边，u为起点，v为终点，w为权重
void add(int u,int v,int w)
{
    cnt++;
    e[cnt].to=v;
    e[cnt].dis=w;
    e[cnt].nxt=hd[u];
    hd[u]=cnt;
}
void prim()
{
    // 遍历第一个节点的所有邻接边，更新dis数组
    for(int i=hd[1];i;i=e[i].nxt)
    dis[e[i].to]=min(dis[e[i].to],e[i].dis);
    // 当tot小于n-1时，继续循环
    while(tot<n-1)
    {
        // 初始化mini为最大值，rec为当前节点
        int mini=0x7fffffff,rec=now;
        // tot加1
        tot++;
        // 标记当前节点为已访问
        vis[now]=1;
        // 遍历所有节点，找到未访问的节点中dis最小的节点
        for(int i=1;i<=n;i++)
        if(!vis[i]&&mini>dis[i])mini=dis[i],now=i;
        // 如果rec等于now，说明已经无法找到未访问的节点，退出循环
        if(rec==now)tot=n+1;
        // 将mini加到ans中
        ans+=mini;
        for(int i=hd[now];i;i=e[i].nxt)
        if(e[i].dis<dis[e[i].to]&&!vis[e[i].to])dis[e[i].to]=e[i].dis;
    }
}
int u,v,w;
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>w;
            if(w>0)
            add(i,j,w),add(j,i,w);
        }
    for(int i=2;i<=n;i++)dis[i]=0x7fffffff;
    prim();
    // cout<<tot<<'\n';
    if(tot==n-1)return cout<<ans,0;
    cout<<"此图不联通";
    return 0;
}