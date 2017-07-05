#include <bits/stdc++.h>
using namespace std;

const int MAX_NOEUDS = 2e4;
const int MAX_ARCS = 2e4;
const int oo = 1e9;

struct Arc {
    int v, c, i, sens;
};

int nbNoeuds, nbArcs, source, destination;
vector<Arc> adj[MAX_NOEUDS];
int flot[MAX_ARCS];
bool vu[MAX_NOEUDS];

int augmenter(int u, int dFlot) {
    if(u == destination)
        return dFlot;
    else if(!vu[u] && dFlot > 0) {
        vu[u] = true;
        for(Arc a : adj[u]) {
            int nvdFlot = min(dFlot, a.c - a.sens * flot[a.i]);
            nvdFlot = augmenter(a.v, nvdFlot);
            if(nvdFlot > 0) {
                flot[a.i] += a.sens * nvdFlot;
                return nvdFlot;
            }
        }
    }
    return 0;
}

int trouverFlot() {
    int maxFlot = 0;
    bool maximal = false;
    while(!maximal) {
        for(int u = 1; u <= nbNoeuds; u++)
            vu[u] = false;
        int dFlot = augmenter(source, +oo);
        maxFlot += dFlot;
        if(dFlot == 0)
            maximal = true;
    }
    return maxFlot;
}

int main()
{
    scanf("%d%d", &nbNoeuds, &nbArcs);
    source = 1;
    destination = nbNoeuds;
    
    for(int iArc = 0; iArc < nbArcs; iArc++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[u].push_back({v, c, iArc, 1});
        adj[v].push_back({u, 0, iArc, -1});
        flot[iArc] = 0;
    }

    printf("%d\n", trouverFlot());
}
