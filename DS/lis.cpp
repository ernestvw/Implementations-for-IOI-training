#include <bits/stdc++.h>

using namespace std;

const int oo = 1e9 + 7;

int n;
int a[1000001], M[1000001];

int main() {
	int T; T=1;//cin >> T;
	while(T--){
	cin >> n;
	for(int i = 0; i < n; i++) cin >> a[i];
	fill_n(M, n+1, +oo);
	M[0] = -oo;
	for(int i = 0; i < n; i++) {
		int l = 0, r = n;
		while(l < r) {
			int mid = (l + r + 1) / 2;
			if(M[mid] != +oo and a[M[mid]] < a[i]) l = mid;
			else r = mid-1;
		}
		if(M[l+1] == +oo or a[M[l+1]] > a[i]) M[l+1] = i;
	}
	int ans = 0;
	for(int i = 0; i <= n; i++) if(M[i] != +oo) ans = i;
	cout << ans << endl;}
}
