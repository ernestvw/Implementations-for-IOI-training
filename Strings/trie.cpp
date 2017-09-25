#include <bits/stdc++.h>
using namespace std;
#define fast_io() ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct Noeud {
	struct Noeud *enfants[26];
	bool finDeMot;
};
typedef Noeud * pNoeud;

pNoeud nouvNoeud() {
	pNoeud noeud = new Noeud;
	noeud->finDeMot = false;
	for(int i = 0; i < 26; i++) noeud->enfants[i] = NULL;
	return noeud;
}

void inserer(pNoeud racine, string cle) {
	pNoeud actuel = racine;
	for(int i = 0; i < (int)cle.length(); i++) {
		int indice = cle[i] - 'a';
		if(!actuel->enfants[indice])
			actuel->enfants[indice] = nouvNoeud();
		actuel = actuel->enfants[indice];
	}
	actuel->finDeMot = true;
}

bool chercher(pNoeud racine, string cle) {
	pNoeud actuel = racine;
	for(int i = 0; i < (int)cle.length(); i++) {
		int indice = cle[i] - 'a';
		if(!actuel->enfants[indice])
			return false;
		actuel = actuel->enfants[indice];
	}
	return (actuel && actuel->finDeMot);
}

int dfs(pNoeud u) {
	if(!u) return 0;
	int nbEnfants = 1;
	for(int v = 0; v < 26; v++)
		nbEnfants += dfs(u->enfants[v]);
	return nbEnfants;
}

int nbMots;
vector<string> mots;

int main()
{
	fast_io();
	
	pNoeud racine = new Noeud;
	racine = nouvNoeud();

	string mot;
	while(cin >> mot) mots.push_back(mot);
	nbMots = (int)mots.size();

	for(string mot : mots) inserer(racine, mot);

	int reponse = dfs(racine);

	cout << reponse;

	return 0;
}
