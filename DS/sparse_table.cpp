#include <bits/stdc++.h>
using namespace std;

const int k = 17;
const int MAXN = 100001;
const int ZERO = - 1e9 - 1;

// F can be any transitive function (like max, min, +, ...)
int F(int a, int b) {
	return max(a, b);
}

int n, q;
int table[MAXN][k+1];
int values[MAXN];

void build() {
	for(int i = 0; i < n; i++) table[i][0] = values[i];
	for(int j = 1; j <= k; j++)
		for(int i = 0; i <= n - (1 << j); i++)
			table[i][j] = F(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
}

int query(int L, int R) {
	int ans = ZERO;
	for(int j = k; j >= 0; j--) {
		if(L + (1 << j) - 1 <= R) {
			ans = F(ans, table[L][j]);
			L += (1 << j);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n;
	for(int i = 0; i < n; i++) cin >> values[i];
	
	build();
	
	cin >> q;
	for(int i = 0; i < q; i++) {
		int L, R;
		cin >> L >> R;
		L--, R--;
		cout << query(L, R) << '\n';
	}
}
