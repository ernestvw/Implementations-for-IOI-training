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
