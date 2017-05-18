/* Dijkstra O(ElogV) */
#include <bits/stdc++.h>
using namespace std;
#define INF (1<<20)
#define MAX 1024

int V,E;

vector<pair<int,int> > G[MAX];
int D[MAX];
int pred[MAX];

void DIJKSTRA(int s)
{
    for(int u=0;u<V;u++)
        D[u]=INF,pred[u]=-1;
    
    int u,cost,v,w;
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;
    
    Q.push(make_pair(0,s));
    D[s]=0;
    
    while(!Q.empty())
    {
        u=Q.top().second;
        cost=Q.top().first;
        Q.pop();
        
        if(D[u]<cost)
            continue;
        
        for(int i=0;i<G[u].size();i++)
        {
            v=G[u][i].first;
            w=G[u][i].second;
            if(D[v]>D[u]+w)
            {
                D[v]=D[u]+w;
                pred[v]=u;
                Q.push(make_pair(D[v],v));
            }
        }
    }
}

int main()
{
    scanf("%d%d",&V,&E);
    
    for(int i=0;i<E;i++)
    {
        int s,d,w;
        scanf("%d%d%d",&s,&d,&w);
        G[s].push_back(make_pair(d,w));
    }
    
    int s;
    printf("Enter starting node: ");
    scanf("%d",&s);
    
    DIJKSTRA(s);
    
    for(int i=0;i<V;i++)
    {
        printf("Distance from %d to %d is %d and path is ",s,i,D[i]);
        vector<int> path;
        path.push_back(i);
        while(path[path.size()-1]!=s)
            path.push_back(pred[path[path.size()-1]]);
        for(int j=path.size()-1;j>=0;j--)
            printf("%d ",path[j]);
        printf("\n");
    }
    
    return 0;    
}
