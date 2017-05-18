#include <bits/stdc++.h>
using namespace std;
#define MAXV 501
#define MAXE 2501
#define INF (int)1e9

struct Edge {
    int v,c,i,sens;
};

int V,E,s,t;
vector<Edge> adj[MAXV];
int flow[MAXE];
bool seen[MAXV];

int augmenter(int u, int Flow) {
    if(u==t)
        return Flow;
    
    else if (!seen[u] && Flow>0)
    {
        seen[u]=true;
        for(int i=0;i<(int)adj[u].size();i++)
        {
            Edge a=adj[u][i];
            int newFlow=min(Flow, a.c-a.sens*flow[a.i]);
            newFlow=augmenter(a.v,newFlow);
            if(newFlow>0)
            {
                flow[a.i]+=a.sens*newFlow;
                return newFlow;
            }
        }
    }
    return 0;
}

int MAXFLOW() {
    int maxflow=0;
    int maximal=false;
    while(!maximal)
    {
        for(int u=1;u<=V;u++)
            seen[u]=false;
    
        int Flow=augmenter(s,INF);
        maxflow+=Flow;
        if(Flow==0)
            maximal=true;
    }
    return maxflow;
}

int main()
{
    scanf("%d%d",&V,&E);
    s=1;
    t=V;
    for(int i=0;i<E;i++)
    {
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        adj[u].push_back({v,c,i,1});
        adj[v].push_back({u,0,i,-1});
        flow[i]=0;
    }
    
    int maxflow=MAXFLOW();
    printf("%d\n",maxflow);
    
    return 0;
}
