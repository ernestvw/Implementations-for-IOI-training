#include <bits/stdc++.h>
using namespace std;
#define MAXV 1001
#define MAXE 10001
#define pb push_back

int V,E;
vector<int> adj[MAXV];
vector<int> revAdj[MAXV];
int in[MAXV];
int revIn[MAXV];

void DFS(int v,bool visited[]) {
    visited[v]=1;
    for(int i=0;i<(int)adj[v].size();i++)
        if(!visited[adj[v][i]])
            DFS(adj[v][i],visited);
}

void revDFS(int v,bool visited[]) {
    visited[v]=1;
    for(int i=0;i<(int)revAdj[v].size();i++)
        if(!visited[revAdj[v][i]])
            revDFS(revAdj[v][i],visited);
}

bool SC() {
    bool visited[V];
    for(int i=0;i<V;i++) visited[i]=0;
    int n;
    for(n=0;n<V;n++)
        if(adj[n].size()>0)
            break;
    DFS(n,visited);
    for(int i=0;i<V;i++)
        if(adj[i].size()>0 && !visited[i])
            return false;
    
    for(int i=0;i<V;i++) visited[i]=0;
    revDFS(n,visited);
    for(int i=0;i<V;i++)
        if(adj[i].size()>0 && !visited[i])
            return false;
    return true;
}

bool exists() {
    if(!SC())
        return false;
    for(int i=0;i<V;i++)
        if((int)adj[i].size()!=in[i])
            return false;
    return true;
}

void hierholzer() {
    int edge_count[V];
    for(int i=0;i<V;i++)
        edge_count[i]=(int)adj[i].size();
    if(V==0)
        return;
    stack<int> cur_path;
    vector<int> circuit;
    cur_path.push(0);
    int cur=0;
    while(!cur_path.empty()) {
        if(edge_count[cur]) {
            cur_path.push(cur);
            int next=adj[cur].back();
            edge_count[cur]--;
            adj[cur].pop_back();
            cur=next;
        }
        else {
            circuit.pb(cur);
            cur=cur_path.top();
            cur_path.pop();
        }
    }
    
    for(int i=(int)circuit.size()-1;i>=0;i--)
        printf("%d ",circuit[i]+1);
    printf("\n");
}

int main()
{
    for(int i=0;i<V;i++) in[i]=0,revIn[i]=0;
    
    scanf("%d%d",&V,&E);
    for(int i=0;i<E;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        u--,v--;
        adj[u].pb(v);
        in[v]++;
        revAdj[v].pb(u);
        revIn[u]++;
    }
    
    if(exists()) {
        hierholzer();
    }
    else {
        printf("-1\n");
    }
    
    return 0;
}
