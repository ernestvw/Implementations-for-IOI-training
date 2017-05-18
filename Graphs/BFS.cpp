#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

/*
* V is the number of vertices
* s is the source vertex
* adj is the adjacency list
* E is the number of edges
* this is an iterative implementation of BFS for a directed graph
*/

void BFS(int s, vector<int> adj[], int V)
{
    bool visited[V]={0};
    visited[s]=1;
    
    queue<int> Q;
    Q.push(s);
    printf("%d ",s);
    
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        for(int v=0;v<adj[u].size();++v)
        {
            if(!visited[adj[u][v]])
            {
                Q.push(adj[u][v]);
                printf("%d ",adj[u][v]);
                visited[adj[u][v]]=1;
            }
        }
    }
}

int main()
{
    int V;
    scanf("%d",&V);
    vector<int> adj[V];
    
    int E;
    scanf("%d",&E);
    for(int i=0;i<E;++i)
    {
        int v1,v2;
        scanf("%d%d",&v1,&v2);
        adj[v1].push_back(v2);
    }
    
    int s;
    scanf("%d",&s);
    BFS(s,adj,V);
    printf("\n");
    
    return 0;
}
