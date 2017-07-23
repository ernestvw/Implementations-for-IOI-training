#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define pb push_back
#define mp make_pair
#define MAX 100001
#define NIL 0
#define INF (1<<30)

vector<int> G[MAX];
int N,match[MAX],dist[MAX];
bool seen[MAX];

bool BFS()
{
    int u,v,len;
    queue<int> Q;
    for(int i=1;i<=N;i++)
    {
        if(match[i]==NIL) {
            dist[i]=0;
            Q.push(i);
        }
        else
            dist[i]=INF;
    }
    dist[NIL]=INF;
    while(!Q.empty()) {
        u=Q.front();
        Q.pop();
        if(u!=NIL) {
            len=(int)G[u].size();
            for(int i=0;i<len;i++)
            {
                v=G[u][i];
                if(dist[match[v]]==INF) {
                    dist[match[v]]=dist[u]+1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}

bool DFS(int u)
{
    int v,len;
    if(u!=NIL) {
        len=(int)G[u].size();
        for(int i=0;i<len;i++) {
            v=G[u][i];
            if(dist[match[v]]==dist[u]+1) {
                if(DFS(match[v])) {
                    match[v]=u;
                    match[u]=v;
                    return true;
                }
            }
        }
        dist[u]=INF;
        return false;
    }
    return true;
}

int HOPCROFT()
{
    int cnt=0;
    while(BFS())
        for(int i=1;i<=N;i++)
            if(match[i]==NIL && DFS(i))
                cnt++;
    return cnt;
}
