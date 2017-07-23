#include <bits/stdc++.h>
using namespace std;

void DFS(int node) {
    if(visited[node]) return;
    visited[node] = true;
    printf("%d ", node);
    for(int neighbour : adj[node])
        DFS(neighbour);
}
