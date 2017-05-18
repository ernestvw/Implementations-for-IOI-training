#include <bits/stdc++.h>
using namespace std;
#define MAXW 2001
#define MAXP 20001
#define INF (int)1e9
#define pii pair<int,int>

int adj[MAXW][MAXW];
int W,P;
int edgesMST[MAXW];
vector<int> pre(MAXW);
pii edges[MAXP];

int prim(int s)
{
    bool visited[W]={0};
    vector<int> key(W,INF);
    priority_queue<pii,vector<pii>,greater<pii> > Q;
    
    int cost=0;
    int u,w;
    key[s]=0;
    Q.push(make_pair(0,s));
    
    while(!Q.empty())
    {
        u=Q.top().second;
        w=Q.top().first;
        Q.pop();
        if(visited[u])
            continue;
        cost+=w;
        visited[u]=1;
        for(int v=0;v<W;v++)
        {
            if(adj[u][v] && !visited[v] && adj[u][v]<key[v])
            {
                Q.push(make_pair(adj[u][v],v));
                key[v]=adj[u][v];
                edgesMST[v]=u;
            }
        }
    }
    
    return cost;
}
