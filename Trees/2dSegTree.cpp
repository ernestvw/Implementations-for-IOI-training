#include <bits/stdc++.h>
using namespace std;

const int MAX_DIMENSIONS = 500;
const int MAX_TAILLE = 5*MAX_DIMENSIONS*MAX_DIMENSIONS;
const int oo = 1e9;

int nbLignes, nbColonnes, nbQuestions;
int valeurs[MAX_DIMENSIONS][MAX_DIMENSIONS];
int arbre[MAX_TAILLE];

int construire(int X1, int Y1, int X2, int Y2, int noeud) {
    if(X1 == X2 && Y1 == Y2)
        return arbre[noeud] = valeurs[X1][Y1];
    if(X1 > X2 || Y1 > Y2) return +oo;
    int X3 = (X1 + X2) / 2;
    int Y3 = (Y1 + Y2) / 2;
    arbre[noeud] = +oo;
    arbre[noeud] = min(arbre[noeud],
            construire(X1, Y1, X3, Y3, 4*noeud+1));
    arbre[noeud] = min(arbre[noeud],
            construire(X1, Y3+1, X3, Y2, 4*noeud+2));
    arbre[noeud] = min(arbre[noeud],
            construire(X3+1, Y1, X2, Y3, 4*noeud+3));
    arbre[noeud] = min(arbre[noeud],
            construire(X3+1, Y3+1, X2, Y2, 4*noeud+4));
    return arbre[noeud];
}

int query(int X1, int Y1, int X2, int Y2,
        int x1, int y1, int x2, int y2, int noeud) {
    if(X1 > x2 || X2 < x1 || Y1 > y2 || Y2 < y1 || X1 > X2 || Y1 > Y2)
        return +oo;
    if(X1 >= x1 && X2 <= x2 && Y1 >= y1 && Y2 <= y2)
        return arbre[noeud];
    int X3 = (X1 + X2) / 2;
    int Y3 = (Y1 + Y2) / 2;
    int reponse = +oo;
    reponse = min(reponse,
            query(X1, Y1, X3, Y3,
                x1, y1, x2, y2, 4*noeud+1));
    reponse = min(reponse,
            query(X1, Y3+1, X3, Y2,
                x1, y1, x2, y2, 4*noeud+2));
    reponse = min(reponse,
            query(X3+1, Y1, X2, Y3,
                x1, y1, x2, y2, 4*noeud+3));
    reponse = min(reponse,
            query(X3+1, Y3+1, X2, Y2,
                x1, y1, x2, y2, 4*noeud+4));
    return reponse;
}

int minimum(int x1, int y1, int x2, int y2) {
    return query(0, 0, nbLignes-1, nbColonnes-1,
            x1, y1, x2, y2, 0);
}

int changer(int X1, int Y1, int X2, int Y2,
        int x, int y, int val, int noeud) {
    if(X1 == X2 || Y1 == Y2) return arbre[noeud] = val;
    if(X1 > X2 || Y1 > Y2) return +oo;
    int X3 = (X1 + X2) / 2;
    int Y3 = (Y1 + Y2) / 2;
    if(X1 <= x && x <= X3 && Y1 <= y && y <= Y3) {
        arbre[noeud] = changer(X1, Y1, X3, Y3, x, y, val, 4*noeud+1);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+2]);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+3]);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+4]);
    }
    else if(X1 <= x && x <= X3 && Y3+1 <= y && y <= Y2) {
        arbre[noeud] = changer(X1, Y3+1, X3, Y2, x, y, val, 4*noeud+2);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+1]);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+3]);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+4]);
    }
    else if(X3+1 <= x && x <= X2 && Y1 <= y && y <= Y3) {
        arbre[noeud] = changer(X3+1, Y1, X2, Y3, x, y, val, 4*noeud+3);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+1]);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+2]);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+4]);
    }
    else if(X3+1 <= x && x <= X2 && Y3+1 <= y && y <= Y2) {
        arbre[noeud] = changer(X3+1, Y3+1, X2, Y2, x, y, val, 4*noeud+4);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+1]);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+2]);
        arbre[noeud] = min(arbre[noeud], arbre[4*noeud+3]);
    }
    return arbre[noeud];
}

int main()
{
    cin >> nbLignes >> nbColonnes;
    for(int lig = 0; lig < nbLignes; lig++)
        for(int col = 0; col < nbColonnes; col++)
            cin >> valeurs[lig][col];

    construire(0, 0, nbLignes-1, nbColonnes-1, 0);

    cin >> nbQuestions;
    for(int q = 0; q < nbQuestions; q++) {
        char op;
        int a, b, c;
        cin >> op >> a >> b >> c;
        if(op == 'm') {
            int d;
            cin >> d;
            cout << minimum(a, b, c, d) << endl;
        }
        else {
            changer(0, 0, nbLignes-1, nbColonnes-1, a, b, c, 0);
        }
    }

    return 0;
}
