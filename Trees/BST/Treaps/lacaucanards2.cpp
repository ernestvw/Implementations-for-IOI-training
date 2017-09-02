#include <bits/stdc++.h>
using namespace std;

struct Noeud {
	int x, y, i;
	bool aRetourner;
	Noeud *gauche, *droite;
};
typedef Noeud * pNoeud;

const int MAX_CANARDS = 100 * 1001;
int nbCanards, nbRequetes;
char nom[MAX_CANARDS][100];
pNoeud racine;

int card(pNoeud u) { return u ? u->x : 0; }

void actualiser(pNoeud u) {
    if(u && u->aRetourner) {
        swap(u->gauche, u->droite);
        if(u->gauche) u->gauche->aRetourner ^= true;
        if(u->droite) u->droite->aRetourner ^= true;
    }
}

pNoeud fusionner(pNoeud u, pNoeud v) {
    actualiser(u), actualiser(v);
	if(!u) return v;
	else if(!v) return u;
	else if(u->y < v->y) {
		u->x += v->x;
		u->droite = fusionner(u->droite, v);
		return u;
	}
	else {
		v->x += u->x;
		v->gauche = fusionner(u, v->gauche);
		return v;
	}
}

pair<pNoeud, pNoeud> couper(pNoeud u, int x) {
	if(!u) return {NULL, NULL};
	actualiser(u);
	if(u->x < x) {
		pair<pNoeud, pNoeud> vw = couper(u->droite, x);
		Noeud *v = vw.first, *w = vw.second;
		u->droite = v;
		u->x -= card(w);
		return {u, w};
	}
	else {
		pair<pNoeud, pNoeud> vw = couper(u->gauche, 1 + card(u->gauche));
		Noeud *v = vw.first, *w = vw.second;
		u->gauche = w;
		u->x -= card(v);
		return {v, u};
	}
}

void inserer(pNoeud *r, int x, int i) {
	int y = rand();
	pNoeud u = new Noeud {x, y, i, false, NULL, NULL};
	pair<pNoeud, pNoeud> vw = couper(*r, x);
	*r = fusionner(vw.first, fusionner(u, vw.second));
}

void retourner(pNoeud u, int iGauche, int iDroit) {
    pair<pNoeud, pNoeud> coupe = couper(u, iGauche);
    pair<pNoeud, pNoeud> reCoupe = couper(coupe.second, iDroit - iGauche + 1);
    reCoupe.first->aRetourner ^= true;
    u = fusionner(coupe.first, reCoupe.first);
    u = fusionner(u, reCoupe.second);
}

int indice(pNoeud u, int i) {
    actualiser(u);
    if(card(u->gauche) == i) return u->i;
    else if(i < card(u->gauche)) return indice(u->gauche, i);
    else return indice(u->droite, i - card(u->gauche) - 1);
}

void afficher(pNoeud u) {
    if(!u) return;
    actualiser(u);
    afficher(u->gauche);
    cout << u->i << " ";
    afficher(u->droite);
}

int main()
{
	srand(42);
	racine = NULL;
	scanf("%d%d", &nbCanards, &nbRequetes);
	for(int iCanard = 1; iCanard <= nbCanards; iCanard++) {
		scanf("%s", nom[iCanard]);
		inserer(&racine, iCanard, iCanard);
	}
	
	afficher(racine);
	cout << endl;
	
	for(int iRequete = 0; iRequete < nbRequetes; iRequete++) {
	    char typeDeRequete[2];
	    scanf("%s", typeDeRequete);
	    if(typeDeRequete[0] == 'R') {
	        int iGauche, iDroit;
	        scanf("%d%d", &iGauche, &iDroit);
	        iGauche--, iDroit -= 2;
	        retourner(racine, iGauche, iDroit);
	    }
	    else {
	        int question;
	        scanf("%d", &question);
	        question--;
	        printf("%s\n", nom[indice(racine, question)]);
	    }
	}
}


























































