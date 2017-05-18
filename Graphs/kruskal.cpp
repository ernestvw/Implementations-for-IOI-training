#include <bits/stdc++.h>
using namespace std;
#define MAX 10001

int V,E;
int parent[MAX];

struct Edge {
    int u,v,w;
};

bool cmp(Edge a,Edge b) {
    return a.w<b.w;
}

int find(int x) {
    return parent[x]==x ? x : (parent[x]=find(parent[x]));
}

void merge(int x,int y) {
    parent[find(x)]=find(y);
}

int kruskal(Edge edges[]) {
    int u,v,w;
    int cost=0;
    for(int i=0;i<E;i++) {
        u=edges[i].u;
        v=edges[i].v;
        w=edges[i].w;
        if(find(u)!=find(v)) {
            cost+=w;
            merge(u,v);
        }
    }
    return cost;
}

int main()
{
    scanf("%d%d",&V,&E);
    Edge edges[E];
    for(int i=0;i<E;i++) {
        Edge e;
        scanf("%d%d%d",&e.u,&e.v,&e.w);
        edges[i]=e;
    }
    
    for(int i=0;i<=V;i++) parent[i]=i;
    sort(edges,edges+E,cmp);
    
    printf("%d\n",kruskal(edges));
    
    return 0;
}
