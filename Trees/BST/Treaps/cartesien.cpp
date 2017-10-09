#include <bits/stdc++.h>
 using namespace std;
 
 struct Noeud {
 	int x, y, k, i;
 	Noeud *gauche, *droite;
 };
 typedef Noeud * pNoeud;
 
 const int MAX_CANARDS = 100 * 1000;
 int nbCanards;
 char nom[MAX_CANARDS][100];
 pNoeud racine;
 
 int card(pNoeud u) { return u ? u->k : 0; }
 
 pNoeud fusionner(pNoeud u, pNoeud v) {
 	if(!u) return v;
 	else if(!v) return u;
 	else if(u->y < v->y) {
 		u->k += v->k;
 		u->droite = fusionner(u->droite, v);
 		return u;
 	}
 	else {
 		v->k += u->k;
 		v->gauche = fusionner(u, v->gauche);
 		return v;
 	}
 }
 
 pair<pNoeud, pNoeud> couper(pNoeud u, int x) {
 	if(!u) return {NULL, NULL};
 	else if(u->x < x) {
 		pair<pNoeud, pNoeud> vw = couper(u->droite, x);
 		Noeud *v = vw.first, *w = vw.second;
 		u->droite = v;
 		u->k -= card(w);
 		return {u, w};
 	}
 	else {
 		pair<pNoeud, pNoeud> vw = couper(u->gauche, x);
 		Noeud *v = vw.first, *w = vw.second;
  	u->gauche = w;
 		u->k -= card(v);
 		return {v, u};
 	}
 }
 
 void inserer(pNoeud *r, int x, int i) {
 	int y = rand();
 	pNoeud u = new Noeud {x, y, 1, i, NULL, NULL};
 	pair<pNoeud, pNoeud> vw = couper(*r, x);
 	*r = fusionner(vw.first, fusionner(u, vw.second));
 }
 
 int i(pNoeud u, int q) {
  if(card(u->gauche) == q) return u->i;
 	else if(q < card(u->gauche)) return i(u->gauche, q);
 	else return i(u->droite, q - card(u->gauche) - 1);
 }

// -----------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;
#define pb push_back
#define mp make_pair
#define endl '\n'
const int oo = 1e9;
const ll OO = 1e18;
ll max(ll a, ll b){return a > b ? a : b;}
ll min(ll a, ll b){return a < b ? a : b;}
#define fast_io() ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const double eps = 1e-9;
const double PI = 4.0 * atan(1.0);

struct Noeud {
	int x, y, k, i;
	Noeud *gauche, *droite;
};
typedef Noeud * pNoeud;

const int MAX_NB_NOMBRES = 100 * 1000 + 1;
int nbNombres;
pNoeud racine;

int card(pNoeud u) { return u ? u->k : 0; }

pNoeud fusionner(pNoeud u, pNoeud v) {
	if(!u) return v;
	else if(!v) return u;
	else if(u->y < v->y) {
		u->k += v->k;
		u->droite = fusionner(u->droite, v);
		return u;
	}
	else {
		v->k += u->k;
		v->gauche = fusionner(u, v->gauche);
		return v;
	}
}

pair<pNoeud, pNoeud> couper(pNoeud u, int x) {
	if(!u) return {NULL, NULL};
	else if(u->x < x) {
		pair<pNoeud, pNoeud> vw = couper(u->droite, x);
		pNoeud v = vw.first, w = vw.second;
		u->droite = v;
		u->k -= card(w);
		return {u, w};
	}
	else {
		pair<pNoeud, pNoeud> vw = couper(u->gauche, x);
		pNoeud v = vw.first, w = vw.second;
		u->gauche = w;
		u->k -= card(v);
		return {v, u};
	}
}

void inserer(pNoeud *r, int x, int i) {
	int y = rand();
	pNoeud u = new Noeud {x, y, 1, i, NULL, NULL};
	pair<pNoeud, pNoeud> vw = couper(*r, x);
	*r = fusionner(vw.first, fusionner(u, vw.second));
}

void effacer(pNoeud &u, int x) {
	if(!u) return;
	else if(u->x == x) {
		u = fusionner(u->gauche, u->droite);
		u->k = card(u->droite) + card(u->gauche) + 1;
	}
	else if(u->x > x) effacer(u->gauche, x);
	else effacer(u->droite, x);
	u->k = card(u->gauche) + card(u->droite) + 1;
}

int valeur(pNoeud u, int i) {
	if(!u) return -1;
	else if(card(u->gauche) + 1 == i) return u->i;
	else if(card(u->gauche) + 1 > i) return valeur(u->gauche, i);
	else return valeur(u->droite, i - 1 - card(u->gauche));
}

void f(pNoeud u) {
	if(u->gauche) {
		cout << "(";
		f(u->gauche);
		cout << ")";
	}
	cout << u->i;
	if(u->droite) {
		cout << "(";
		f(u->droite);
		cout << ")";
	}
}

int main()
{
	fast_io();

	srand(42);
	cin >> nbNombres;
	racine = NULL;
	for(int i = 1; i <= nbNombres; i++)
		inserer(&racine, i, i);
	f(racine);
	cout << endl;
	for(int i = 1; i <= nbNombres; i++)
		cout << valeur(racine, i) << " ";
	cout << endl;
	effacer(racine, 7);
	f(racine);
	cout << endl;
	for(int i = 1; i <= nbNombres; i++)
		cout << valeur(racine, i) << " ";
	cout << endl;

	return 0;
}

