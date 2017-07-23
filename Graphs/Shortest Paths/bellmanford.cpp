#include <bits/stdc++.h>
using namespace std;
#define MAX 10001
#define INF (int)1e9

struct Edge {
    int u,v,w;
};

int V,E;
int D[MAX];
int parent[MAX];

int bellmanford(Edge edges[]) {
    for(int i=0;i<=V;i++) parent[i]=-1,D[i]=INF;
    D[1]=0;
    for(int i=1;i<=V-1;i++) {
        for(int j=0;j<E;j++) {
            if(D[edges[j].v]>D[edges[j].u]+edges[j].w) {
                D[edges[j].v]=D[edges[j].u]+edges[j].w;
                parent[edges[j].v]=edges[j].u;
            }
        }
    }
    /* if negative cycle return 0 */
    for(int i=0;i<E;i++)
        if(D[edges[i].v]>D[edges[i].u]+edges[i].w)
            return 0;
    return D[V];
}
