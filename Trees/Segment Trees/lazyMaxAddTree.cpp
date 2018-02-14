struct Arbre {
	// range max query, range sum update
	vector<int> arbre(3000, 0);
	vector<int> lazy(3000, 0);
	int util(int l, int r, int L, int R, int n, int val);
	void ajouter(int l, int r, int val);
	int query(int l, int r, int L, int R, int n);
	int maxi(int l, int r);
};

int Arbre::util(int l, int r, int L, int R, int n, int val) {
	if(lazy[n]) {
		arbre[n] += lazy[n];
		if(l != r) {
			lazy[2*n+1] += lazy[n];
			lazy[2*n+2] += lazy[n];
		}
		lazy[n] = 0;
	}
	if(l > r or l > R or r < L) return -oo;
	if(L <= l and r <= R) {
		arbre[n] += val;
		if(l != r) {
			lazy[2*n+1] += val;
			lazy[2*n+2] += val;
		}
		return arbre[n];
	}
	int m = (l+r) / 2;
	arbre[n] = max(util(l, m, L, R, 2*n+1, val), util(m+1, r, L, R, 2*n+2, val));
	return arbre[n];
}

void Arbre::ajouter(int l, int r, int val) {
	util(0, nbLig+1, l, r, 0, val);
}

int Arbre::query(int l, int r, int L, int R, int n) {
	if(lazy[n]) {
		arbre[n] += lazy[n];
		if(l != r) {
			lazy[2*n+1] += lazy[n];
			lazy[2*n+2] += lazy[n];
		}
		lazy[n] = 0;
	}
	if(l > r or l > R or r < L) return -oo;
	if(L <= l and r <= R) return arbre[n];
	int m = (l+r) / 2;
	return max(query(l, m, L, R, 2*n+1), query(m+1, r, L, R, 2*n+2));
}

int Arbre::maxi(int l, int r) {
	return query(0, nbLig+1, l, r, 0);
}
