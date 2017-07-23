#include <bits/stdc++.h>
using namespace std;

const int MAX_NB_NOEUDS = 3e5;

struct Arc {
    int u, v;
    bool lourd;
};

int nbNoeuds, nbArcs;
int nbComposantes = 0;
int composante[MAX_NB_NOEUDS];
bool dansComposantes[MAX_NB_NOEUDS];
vector<Arc> adj[MAX_NB_NOEUDS];
int tailleSousArbre[MAX_NB_NOEUDS];
int profondeur[MAX_NB_NOEUDS];
bool vu[MAX_NB_NOEUDS] = {0};
int parent[MAX_NB_NOEUDS];
vector<Arc> arcsLourds;

int trouverTaille(int iNoeud, int profondeurActuelle, int avant) {
    if(vu[iNoeud]) return 0;
    vu[iNoeud] = 1;
    parent[iNoeud] = avant;
    tailleSousArbre[iNoeud] = 1;
    profondeur[iNoeud] = profondeurActuelle;
    for(Arc iVoisin : adj[iNoeud])
        tailleSousArbre[iNoeud] += trouverTaille(iVoisin.v, profondeurActuelle+1, iNoeud);
    return tailleSousArbre[iNoeud];
}

void trouverLourds(int iNoeud) {
    int tailleLourde = (tailleSousArbre[iNoeud]+1)/2;
    // cout << iNoeud << " ";
    vu[iNoeud] = true;
    for(int iArc = 0; iArc < (int)adj[iNoeud].size(); iArc++) {
        Arc iVoisin = adj[iNoeud][iArc];
        if(vu[iVoisin.v]) continue;
        if(tailleSousArbre[iVoisin.v] >= tailleLourde) {
            iVoisin.lourd = true;
            arcsLourds.push_back(iVoisin);
            adj[iNoeud][iArc] = iVoisin;
        }
        trouverLourds(iVoisin.v);
    }
}

void trouverComposantes(int iNoeud, bool dansComposante, int premierNoeud) {
    if(vu[iNoeud]) return;
    vu[iNoeud] = 1;
    for(Arc iVoisin : adj[iNoeud]) {
        if(iVoisin.lourd && !dansComposante) {
            dansComposante = 1;
            premierNoeud = iNoeud;
            nbComposantes++;
        }
    }
    if(iNoeud != premierNoeud) composante[iNoeud] = premierNoeud;
    if(dansComposante) dansComposantes[iNoeud] = true;
    for(Arc iVoisin : adj[iNoeud]) {
        if(iVoisin.lourd)
            trouverComposantes(iVoisin.v, true, premierNoeud);
        else
            trouverComposantes(iVoisin.v, false, -1);
    }
}

int lca(int iNoeud1, int iNoeud2) {
    int n1 = iNoeud1, n2 = iNoeud2;
    while(iNoeud1 != iNoeud2) {
        if(profondeur[iNoeud1] > profondeur[iNoeud2]) {
            n1 = iNoeud1;
            if(composante[iNoeud1] == -1) {
                iNoeud1 = parent[iNoeud1];
                n1 = iNoeud1;
            }
            else
                iNoeud1 = composante[iNoeud1];
        }
        else {
            n2 = iNoeud2;
            if(composante[iNoeud2] == -1) {
                iNoeud2 = parent[iNoeud2];
                n2 = iNoeud2;
            }
            else
                iNoeud2 = composante[iNoeud2];
        }
    }
    if(profondeur[n1] >= profondeur[n2])
        return n2;
    return n1;
}

int main()
{
    scanf("%d", &nbNoeuds);
    nbArcs = nbNoeuds - 1;
    for(int iArc = 0; iArc < nbArcs; iArc++) {
        int iNoeud1, iNoeud2;
        scanf("%d%d", &iNoeud1, &iNoeud2);
        adj[iNoeud1].push_back({iNoeud1, iNoeud2, 0});
        adj[iNoeud2].push_back({iNoeud2, iNoeud1, 0});
    }

    tailleSousArbre[1] = trouverTaille(1, 1, 1);
    fill_n(vu, nbNoeuds+1, false);
    trouverLourds(1);
    fill_n(vu, nbNoeuds+1, false);
    fill_n(composante, nbNoeuds+1, -1);
    trouverComposantes(1, false, -1);

    // cout << lca(2, 8) << endl;

    long long total = 0;
    for(int i = 1; i <= nbNoeuds; i++) {
        for(int j = 2*i; j <= nbNoeuds; j += i) {
            // cout << i << " " << j << " " << profondeur[i] + profondeur[j] + 1 - 2*profondeur[lca(i, j)] << endl;
            total += (long long)profondeur[i] + profondeur[j] + 1;
            total -= (long long)2*profondeur[lca(i, j)];
        }
    }

    printf("%lld\n", total);

    return 0;
}
