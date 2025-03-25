//UPD3.25
//可以跑出整个图的最小生成树的所有边，用于制作导览图
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
int hd[maxn],dis[maxn],vis[maxm],cnt,n,m,tot,ans=0,now=1;
pair<int, int> parent[maxn];
//链式前向星存图
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
    // 遍历第一个节点的所有邻接边，更新距离和父节点
    for(int i=hd[1];i;i=e[i].nxt)
    {
        dis[e[i].to]=min(dis[e[i].to],e[i].dis);
        parent[e[i].to]={1,e[i].dis};
    }
    while(tot<n-1)
    {
        int mini=0x7fffffff,rec=now;
        tot++;
        vis[now]=1;
        // 遍历所有节点，找到距离最小的节点
        for(int i=1;i<=n;i++)
        if(!vis[i]&&mini>dis[i])mini=dis[i],now=i;
        // 如果没有找到距离最小的节点，说明图不连通，退出循环
        if(rec==now)tot=n+1;
        ans+=mini;
        // 输出当前节点和父节点
        cout<<parent[now].first<<" "<<now<<" "<<parent[now].second<<'\n';
        // 遍历当前节点的所有邻接边，更新距离和父节点
        for(int i=hd[now];i;i=e[i].nxt)
        if(e[i].dis<dis[e[i].to]&&!vis[e[i].to])
        {
            dis[e[i].to]=e[i].dis;
            parent[e[i].to]={now, e[i].dis};
        }
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
    for(int i=2;i<=n;i++) dis[i]=0x7fffffff;
    prim();
    if(tot==n-1) cout<<"Total Weight: "<<ans<<'\n';
    else cout<<"此图不联通";
    
    return 0;
}
/*
4
0 2 2 3
2 0 5 1
2 5 0 3
3 1 3 0
*/
