#include <bits/stdc++.h>
using namespace std;
#define MAX 10001
#define NIL -1
#define pb push_back

int V,E;

vector<vector<int> > SCCs;
vector<int> adj[MAX];

void SCCUtil(int u,int disc[],int low[],stack<int> st,bool stackMember[]) {
    static int time=0;
    disc[u]=low[u]=++time;
    st.push(u);
    stackMember[u]=1;
    for(int i=0;i<(int)adj[u].size();i++) {
        int v=adj[u][i];
        if(disc[v]==NIL) {
            SCCUtil(v,disc,low,st,stackMember);
            low[u]=min(low[u],low[v]);
        }
        else if(stackMember[v])
            low[u]=min(low[u],disc[v]);
    }
    int w=0;
    if(low[u]==disc[u]) {
        vector<int> scc;
        while(st.top()!=u) {
            w=st.top();
            st.pop();
            stackMember[w]=0;
            scc.pb(w);
        }
        w=st.top();
        scc.pb(w);
        stackMember[w]=0;
        st.pop();
        if(scc.size()) SCCs.pb(scc);
    }
}

void SCC()
{
    int disc[V];
    int low[V];
    bool stackMember[V];
    stack<int> st;
    for(int i=0;i<V;i++) disc[i]=NIL,low[i]=NIL,stackMember[i]=0;
    for(int i=0;i<V;i++)
        if(disc[i]==NIL)
            SCCUtil(i,disc,low,st,stackMember);
}
