#include <bits/stdc++.h>
using namespace std;
#define INF (int)1e9
#define pii pair<int,int>
#define mp make_pair
#define pb push_back

int V,E;
vector<pii> used;

int BFS(vector<int> rG[],int s,int t,int parent[]) {
    bool visited[V]={0};
    queue<int> Q;
    Q.push(s);
    visited[s]=true;
    parent[s]=-1;
    while(!Q.empty()) {
        int u=Q.front();
        Q.pop();
        for(int v=0;v<V;v++) {
            if(!visited[v] && rG[u][v]>0) {
                Q.push(v);
                parent[v]=u;
                visited[v]=true;
            }
        }
    }
    return visited[t];
}

void DFS(vector<int> rG[],int s,bool visited[]) {
    visited[s]=true;
    for(int i=0;i<V;i++)
        if(rG[s][i] && !visited[i])
            DFS(rG,i,visited);
}

void minCut(vector<int> G[],int s,int t) {
    int u,v;
    vector<int> rG[V];
    for(int i=0;i<V;i++) rG[i]=G[i];
    int parent[V];
    while(BFS(rG,s,t,parent)) {
        int pathflow=INF;
        for(v=t;v!=s;v=parent[v]) {
            u=parent[v];
            pathflow=min(pathflow,rG[u][v]);
        }
        for(v=t;v!=s;v=parent[v]) {
            u=parent[v];
            rG[u][v]-=pathflow;
            rG[v][u]+=pathflow;
        }
    }
    bool visited[V]={0};
    DFS(rG,s,visited);
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            if(visited[i] && !visited[j] && G[i][j])
                used.pb(mp(i+1,j+1));
    return;
}

int main()
{
    scanf("%d%d",&V,&E);
    
    vector<int> temp(V,0);
    vector<int> G[V];
    for(int i=0;i<V;i++) G[i]=temp;
    
    for(int i=0;i<E;i++) {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        G[u-1][v-1]=w;
    }
    
    minCut(G,0,V-1);
    printf("%d\n",(int)used.size());
    for(int i=0;i<(int)used.size();i++)
        printf("%d %d\n",used[i].first,used[i].second);
    
    return 0;
}
