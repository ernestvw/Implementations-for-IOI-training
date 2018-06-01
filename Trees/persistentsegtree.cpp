#include <bits/stdc++.h>
using namespace std;

struct Noeud {
	int val, gauche, droit;
};

int N, Q;
int act = 0;
Noeud noeuds[3000000];
vector<int> version, valeurs;

int nouvNoeud() {
	noeuds[act] = {0, -1, -1};
	act++;
	return act-1;
}

int query(int l, int r, int L, int R, int arbre) {
	if(arbre == -1 or l > r or l > R or r < L) return 0;
	if(L <= l and r <= R) return noeuds[arbre].val;
	return query(l, (l + r) / 2, L, R, noeuds[arbre].gauche) + query((l + r) / 2 + 1, r, L, R, noeuds[arbre].droit);
}

int build(int l, int r, int arbre) {
	if(l > r) return 0;
	if(l == r) return noeuds[arbre].val = valeurs[l];
	noeuds[arbre].gauche = nouvNoeud();
	noeuds[arbre].droit = nouvNoeud();	
	return noeuds[arbre].val = build(l, (l+r)/2, noeuds[arbre].gauche) + build((l+r)/2+1, r, noeuds[arbre].droit);
}

void update(int l, int r, int i, int ancien, int arbre, int val) {
	if(l > r or l > i or r < i) return;
	if(l == r) {
		noeuds[arbre].val = val;
		return;
	}
	int mid = (l + r) / 2;
	if(i <= mid) {
		noeuds[arbre].droit = noeuds[ancien].droit;
		noeuds[arbre].gauche = nouvNoeud();
		update(l, mid, i, noeuds[ancien].gauche, noeuds[arbre].gauche, val);
	}
	else {
		noeuds[arbre].gauche = noeuds[ancien].gauche;
		noeuds[arbre].droit = nouvNoeud();
		update(mid + 1, r, i, noeuds[ancien].droit, noeuds[arbre].droit, val);
	}
	noeuds[arbre].val = noeuds[noeuds[arbre].gauche].val + noeuds[noeuds[arbre].droit].val;
}

int main() {
	scanf("%d", &N);
	valeurs.resize(N);
	for(int i = 0; i < N; i++)
		scanf("%d", &valeurs[i]);

	version.push_back(nouvNoeud());
	build(0, N-1, version[0]);

	int iversion = 0;

	scanf("%d", &Q);
	for(int q = 0; q < Q; q++) {
		char type[2];
		scanf("%s", type);
		if(type[0] == 'M') {
			int k, v;
			scanf("%d%d", &k, &v);
			version.push_back(nouvNoeud());
			update(0, N-1, k, version[iversion], version[iversion+1], v);
			iversion++;
		}
		else {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", query(0, N-1, l, r, version[iversion]));
		}
	}
}
