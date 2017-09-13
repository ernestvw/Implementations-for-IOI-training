#include <bits/stdc++.h>
using namespace std;

int nbCoups, nbCols = 1e5+2;
const int MAX_COL = 1e6;
const int oo = 1e9;

struct Seg {
    int gauche, droit;
    Seg (int g = 0, int d = 0) : gauche(g), droit(d) {}
    bool contient(Seg autre) {
        return gauche <= autre.gauche && autre.droit <= droit;
    }
    bool disjointDe(Seg autre) {
        return autre.droit < gauche || droit < autre.gauche;
    }
    int milieu() {
        return (gauche + droit) / 2;
    }
    Seg moitieGauche() {
        return Seg(gauche, milieu());
    }
    Seg moitieDroite() {
        return Seg(milieu()+1, droit);
    }
};

struct Noeud {
    int maxi, hauteur;
    Noeud() { maxi = hauteur = 0; }
    void changer(int h) { maxi = hauteur = h; }
};

Noeud arbre[MAX_COL];

void modifier(Seg intervalle, Seg modif, int val, int noeud) {
    if(modif.disjointDe(intervalle)) return;
    else if(modif.contient(intervalle))
        arbre[noeud].changer(val);
    else {
        int &hauteur = arbre[noeud].hauteur;
        if(hauteur > 0) {
            arbre[2*noeud+1].changer(hauteur);
            arbre[2*noeud+2].changer(hauteur);
            hauteur = 0;
        }
        modifier(intervalle.moitieGauche(), modif, val, 2*noeud+1);
        modifier(intervalle.moitieDroite(), modif, val, 2*noeud+2);
        arbre[noeud].maxi = max(arbre[2*noeud+1].maxi,
                                arbre[2*noeud+2].maxi);
    }
}

int trouverMax(Seg intervalle, Seg requete, int noeud) {
    if(requete.disjointDe(intervalle)) return -oo;
    else if(requete.contient(intervalle))
        return arbre[noeud].maxi;
    else {
        if(arbre[noeud].hauteur)
            return arbre[noeud].hauteur;
        return max(
        trouverMax(intervalle.moitieGauche(), requete, 2*noeud+1),
        trouverMax(intervalle.moitieDroite(), requete, 2*noeud+2));
    }
}
