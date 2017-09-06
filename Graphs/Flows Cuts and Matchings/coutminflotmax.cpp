#include <bits/stdc++.h>
using namespace std;

const int oo = 1e9;
int nbNoeuds, nbArcs, nbChemins;
const int MAX_NB_NOEUDS = 251;
const int MAX_NB_ARCS = 2501;
bool trouve[MAX_NB_NOEUDS];
int capacite[MAX_NB_NOEUDS][MAX_NB_NOEUDS] = {{0}};
int flot[MAX_NB_NOEUDS][MAX_NB_NOEUDS] = {{0}};
int couts[MAX_NB_NOEUDS][MAX_NB_NOEUDS] = {{0}};
int parent[MAX_NB_NOEUDS] = {0};
int D[MAX_NB_NOEUDS];
int pi[MAX_NB_NOEUDS] = {0};

bool chercher(int source, int puit) {
	fill_n(trouve, MAX_NB_NOEUDS, false);
	fill_n(D, MAX_NB_NOEUDS, +oo);
	D[source] = 0;
	while(source != nbNoeuds) {
		int meilleur = nbNoeuds;
		trouve[source] = true;
		for(int k = 0; k < nbNoeuds; k++) {
			if(trouve[k]) continue;
			if(flot[k][source] != 0) {
				int val = D[source] + pi[source] - pi[k] - couts[k][source];
				if(D[k] > val) {
					D[k] = val;
					parent[k] = source;
				}
			}
			if(flot[source][k] < capacite[source][k]) {
				int val = D[source] + pi[source] - pi[k] + couts[source][k];
				if(D[k] > val) {
					D[k] = val;
					parent[k] = source;
				}
			}
			if(D[k] < D[meilleur]) meilleur = k;
		}
		source = meilleur;
	}
	for(int k = 0; k < nbNoeuds; k++)
		pi[k] = min(pi[k] + D[k], +oo);
	return trouve[puit];
}

int calcFlotMax(int source, int puit) {
	int Flot = 0, Cout = 0;
	while(chercher(source, puit) && Flot < nbChemins) {
		int aug = +oo;
		for(int x = puit; x != source; x = parent[x])
			aug = min(aug, flot[x][parent[x]] != 0 ? flot[x][parent[x]] :
					capacite[parent[x]][x] - flot[parent[x]][x]);
		for(int x = puit; x != source; x = parent[x]) {
			if(flot[x][parent[x]] != 0) {
				flot[x][parent[x]] -= aug;
				Cout -= aug * couts[x][parent[x]];
			}
			else {
				flot[parent[x]][x] += aug;
				Cout += aug * couts[parent[x]][x];
			}
		}
		Flot += aug;
	}
	return Cout;
}

int main()
{
	scanf("%d%d%d", &nbNoeuds, &nbArcs, &nbChemins);
	
	for(int i = 0; i < nbNoeuds; i++)
	    for(int j = 0; j < nbNoeuds; j++)
	        capacite[i][j] = couts[i][j] = 0;
	
	for(int iArc = 0; iArc < nbArcs; iArc++) {
		int noeud1, noeud2, Cout;
		scanf("%d%d%d", &noeud1, &noeud2, &Cout);
		noeud1--, noeud2--;
		capacite[noeud1][noeud2] = 1;
		couts[noeud1][noeud2] = Cout;
	}

	int source = 0;
	int puit = nbNoeuds - 1;

	printf("%d", calcFlotMax(source, puit));
}
