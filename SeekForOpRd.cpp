#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
const int inf=0x7fffffff,maxm=500010;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct edge{
    int to,dis,nxt;
}e[maxm];
struct node{
    int dis,pos;
    bool operator <(const node &x)const{return x.dis<dis;}
};
int hd[maxm],dis[105][105],cnt,vis[105];
int info[105][105],dp[105][105],pre[105][105];
int n,m,s,points[105];
void add(int u,int v,int w)
{
    cnt++;
    e[cnt].dis=w;
    e[cnt].to=v;
    e[cnt].nxt=hd[u];
    hd[u]=cnt;
}
void dijkstra(int start)
{
    priority_queue<node> q;
    for(int i=1;i<=n;i++) dis[start][i]=inf;
    memset(vis,0,sizeof(vis));
    dis[start][start]=0;
    q.push((node){0, start});
    while(!q.empty())
    {
        node tmp=q.top(); q.pop();
        int u=tmp.pos;
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i=hd[u];i;i=e[i].nxt)
        {
            int v=e[i].to;
            if(dis[start][v]>dis[start][u]+e[i].dis)
            {
                dis[start][v]=dis[start][u]+e[i].dis;
                if(!vis[v]) q.push((node){dis[start][v], v});
            }
        }
    }
}
int main()
{
    n=read();  //读这个表格
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            info[i][j]=read();  
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            if(info[i][j]>0)
            {
                add(i,j,info[i][j]);  
                add(j,i,info[i][j]);  
            }
    m=read();  // 读取要找的m个点
    for(int i=0;i<m;i++)points[i]=read();  
    for(int i=1;i<=n;i++)dijkstra(i);  // 运行Dijkstra算法
    memset(dp,0x3f,sizeof(dp));  // 初始化dp数组
    memset(pre,-1,sizeof(pre));  // 初始化pre数组
    dp[1][0]=0;  // 只有第一个点被访问
    // DP转移
    for(int S=1;S<(1<<m);S++)
    {  // 遍历所有点集
        for(int i=0;i<m;i++)
        {  // 目标点是 points[i]
            if(S&(1<<i))
            {  // 当前状态包含点 points[i]
                for(int j=0;j<m;j++)
                {  // 遍历其他点
                    if(i!=j&&(S&(1<<j)))
                    {  // 如果状态包含点 points[j] 且不等于 i
                        if(dp[S][i]>dp[S^(1<<i)][j]+dis[points[j]][points[i]])
                        {
                            dp[S][i]=dp[S^(1<<i)][j]+dis[points[j]][points[i]];
                            pre[S][i]=j;  // 记录路径回溯信息
                        }
                    }
                }
            }
        }
    }
    // 找到最短路径
    int ans=inf,last_point=-1;
    for(int i=0;i<m;++i)
        if(dp[(1<<m)-1][i]<ans)
        {
            ans=dp[(1<<m)-1][i];
            last_point=i;
        }
    // 输出最短路径
    cout<<"最短路径长度: "<<ans<<'\n';
    // 回溯路径
    vector<int> path;
    int S=(1<<m)-1;  // 最终状态
    while(last_point!=-1)
    {
        path.push_back(points[last_point]);
        int temp=last_point;
        last_point=pre[S][last_point];
        S^=(1<<temp);  // 去掉最后一个点，继续回溯
    }
    // 输出经过的路径
    cout<<"经过的路径: ";
    for(int i=path.size()-1;i>=0;i--) 
        cout<<path[i]<<" ";
    return 0;
}
/*
4
0 2 5 3
2 0 -1 4
5 -1 0 3 
3 4 3 0
3
1 3 4
*/
