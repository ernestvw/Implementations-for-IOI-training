#include <bits/stdc++.h>
using namespace std;
#define MAX 10001
#define pb push_back
#define NIL -1

int V,E;
vector<int> adj[MAX];
vector<int> revAdj[MAX];
vector<int> SCCs[MAX];
int nbSCC=0;
stack<int> Q;

void DFSUtil(int v,bool visited[]) {
    visited[v]=1;
    SCCs[nbSCC].pb(v);
    for(int i=0;i<(int)revAdj[v].size();i++)
        if(!visited[revAdj[v][i]])
            DFSUtil(revAdj[v][i],visited);
}

void DFS(int v,bool visited[]) {
    visited[v]=1;
    for(int i=0;i<(int)adj[v].size();i++)
        if(!visited[adj[v][i]])
            DFS(adj[v][i],visited);
    Q.push(v);
}

void findSCC()
{
    bool visited[V];
    for(int i=0;i<V;i++) visited[i]=0;
    for(int i=0;i<V;i++)
        if(!visited[i])
            DFS(i,visited);
    for(int i=0;i<V;i++) visited[i]=0;
    while(!Q.empty()) {
        int v=Q.top();
        Q.pop();
        if(!visited[v]) {
            DFSUtil(v,visited);
            nbSCC++;
        }
    }
}

int main()
{
    V=5;
    adj[1].pb(0); revAdj[0].pb(1);
    adj[0].pb(2); revAdj[2].pb(0);
    adj[2].pb(1); revAdj[1].pb(2);
    adj[0].pb(3); revAdj[3].pb(0);
    adj[3].pb(4); revAdj[4].pb(3);
    findSCC();
    for(int i=0;i<nbSCC;i++) {
        for(int j=0;j<(int)SCCs[i].size();j++)
            cout<<SCCs[i][j]<<" ";
        cout<<endl;
    }
    
    return 0;
}
