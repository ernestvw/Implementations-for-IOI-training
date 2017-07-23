#include <bits/stdc++.h>
using namespace std;

const int MAX_V = (int)1e3+5;
const int MAX_E = (int)1e6+5;

int V,E;
bool couple[MAX_V];
bool utilise[MAX_V][MAX_V];
bool vu[MAX_V];
vector<int> adj[MAX_V];

bool coupler(int u,bool t) {
    if(!couple[u] && t) return true;
    if(!vu[u]) {
        vu[u]=true;
        for(int i=0;i<(int)adj[u].size();i++) {
            int v=adj[u][i];
            if(utilise[u][v]==t && coupler(v,!t)) {
                couple[u]=true;
                couple[v]=true;
                utilise[u][v]=!t;
                return true;
            }
        }
    }
    return false;
}

int matching() {
    bool maximal=false;
    while(!maximal) {
        maximal=true;
        for(int i=0;i<V;i++) vu[i]=false;
        for(int u=0;u<V;u++)
            if(!couple[u] && coupler(u,false))
                maximal=false;
    }
    int nbMatch=0;
    for(int i=0;i<V;i++)
        if(couple[i])
            nbMatch++;
    return nbMatch;
}

int main()
{
    scanf("%d%d",&V,&E);
    for(int i=0;i<V;i++) {
        couple[i]=false;
        vu[i]=false;
        for(int j=0;j<V;j++) utilise[i][j]=false;
    }
    for(int i=0;i<E;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
    }
    cout<<matching()<<endl;
    
    return 0;
}
