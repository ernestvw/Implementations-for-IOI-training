/* O(V+E) */
/* for undirected graphs */
#include <bits/stdc++.h>
using namespace std;
#define NIL -1
#define MAX 1001
#define pb push_back

int V,E;
vector<int> adj[MAX];

void APUtil(int u,bool visited[],int disc[],int low[],int parent[],bool ap[]) {
    static int time=0;
    int children=0;
    visited[u]=1;
    disc[u]=low[u]=++time;
    for(int i=0;i<(int)adj[u].size();i++) {
        int v=adj[u][i];
        if(!visited[v]) {
            children++;
            parent[v]=u;
            APUtil(v,visited,disc,low,parent,ap);
            low[u]=min(low[u],low[v]);
            if(parent[u]==NIL && children>1)
                ap[u]=1;
            if(parent[u]!=NIL && low[v]>=disc[u])
                ap[u]=1;
        }
        else if(v!=parent[u])
            low[u]=min(low[u],disc[v]);
    }
}

void AP() {
    bool visited[V];
    int disc[V];
    int low[V];
    int parent[V];
    bool ap[V];
    
    for(int i=0;i<V;i++)
        visited[i]=0,ap[i]=0,parent[i]=NIL;
    
    for(int i=0;i<V;i++)
        if(!visited[i])
            APUtil(i,visited,disc,low,parent,ap);
    
    int cnt=0;
    for(int i=0;i<V;i++)
        if(ap[i])
            cnt++,printf("%d\n",i+1);
    
    printf("%d\n",cnt);
}

int main()
{
    scanf("%d%d",&V,&E);
    for(int i=0;i<E;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        u--,v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    AP();
    
    return 0;
}
