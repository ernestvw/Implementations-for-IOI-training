#include <bits/stdc++.h>
using namespace std;

const int oo = 1000*1000*1000 + 7;

int tailleTexte, tailleMotif;

vector<int> plusLongBord;

vector<int> chaine;

vector<vector<int>> arbre;

vector<int> fusion(vector<int> A, vector<int> B) {
	vector<int> C;
	int i = 0, j = 0;
	while(i < (int)A.size() or j < (int)B.size()) {
		if(i == (int)A.size()) {
			C.push_back(B[j]);
			j++;
		}
		else if(j == (int)B.size()) {
			C.push_back(A[i]);
			i++;
		}
		else if(A[i] < B[j]) {
			C.push_back(A[i]);
			i++;
		}
		else {
			C.push_back(B[j]);
			j++;
		}
	}
	return C;
}

void construire(int noeud, int l, int r) {
	if(l == r) {
		arbre[noeud].push_back(chaine[l]);
		return;
	}
	int mid = (l+r) / 2;
	construire(2 * noeud + 1, l, mid);
	construire(2 * noeud + 2, mid + 1, r);
	arbre[noeud] = fusion(arbre[2*noeud+1], arbre[2*noeud+2]);
}

int _n, _i;
int dicho(int noeud, int x) {
	_n = (int)arbre[noeud].size();
	if(_n == 0) return 0;
	if(arbre[noeud][0] >= x) return 0;
	_i = 0;
	for(int saut=21;saut>=0;saut--)
		if(_i+(1<<saut)<_n and arbre[noeud][_i+(1<<saut)]<x)
			_i += (1<<saut);
	return _i+1;
}

int requete(int noeud, int l, int r, int L, int R, int x) {
	if(l > R or r < L or l > r) return 0;
	if(L <= l and r <= R)
		return dicho(noeud, x);
	int mid = (l+r) / 2;
	return requete(2*noeud+1, l, mid, L, R, x)
		+ requete(2*noeud+2, mid+1, r, L, R, x);
}

bool equiv(int position, int indice) {
	return requete(0, 0, tailleMotif+tailleTexte, 0, position-1, chaine[position]) == requete(0, 0, tailleMotif+tailleTexte, indice-position, indice-1, chaine[indice]);
}

void calculBord() {
	int longueurMotif = tailleTexte + 1 + tailleMotif;
	plusLongBord[0] = 0;
	for(int i = 1; i < longueurMotif; i++) {
		int position = plusLongBord[i-1];
		while(position > 0 and !equiv(position, i))
			position = plusLongBord[position-1];
		if(equiv(position, i))
			position++;
		plusLongBord[i] = position;
	}
}

vector<int> correspondances() {
	vector<int> rep;
	calculBord();
	for(int i = 2*tailleMotif; i < tailleMotif + tailleTexte + 1; i++)
		if(plusLongBord[i] == tailleMotif)
			rep.push_back(i - 2 * tailleMotif);
	return rep;
}

vector<int> P;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> tailleMotif >> tailleTexte;

	P.resize(tailleMotif);
	plusLongBord.resize(tailleMotif+tailleTexte+1);
	chaine.resize(tailleMotif+tailleTexte+1);
	arbre.resize(4 * (tailleMotif + tailleTexte + 1));

	for(int i = 0; i < tailleMotif; i++)
		cin >> P[i];
	for(int i = 0; i < tailleMotif; i++)
		chaine[P[i]-1] = i+1;
	chaine[tailleMotif] = +oo;
	for(int i = tailleMotif + 1; i < tailleMotif + 1 + tailleTexte; i++)
		cin >> chaine[i];

	construire(0, 0, tailleMotif+tailleTexte);

	vector<int> rep = correspondances();
	
	cout << rep.size() << endl;
	for(int i = 0; i < (int)rep.size(); i++) {
		if(i) cout << " ";
		cout << rep[i]+1;
	}
	cout << endl;
}
