#include <bits/stdc++.h>
using namespace std;

const long long MOD = 167772161;

long long TAILLE, INV_TAILLE;

inline long long modInv(long long a, long long b) {
	return 1 < a ? b - modInv(b % a, a) * b / a : 1LL;
}

inline long long exp(long long a, long long b) {
	long long c = 1LL;
	while(b > 0) {
		if(b & 1LL) c = c * a % MOD;
		b = b >> 1LL;
		a = a * a % MOD;
	}
	return c;
}

inline void NTT(vector<int> &a, long long len, int type) {
	for(int i = 0, t = 0; i < len; i++) {
		if(i < t) swap(a[i], a[t]);
		for(int j = len >> 1; (t ^= j) < j; j >>= 1);
	}
	long long t;
	for(int i = 2; i <= len; i <<= 1) {
		const long long wn = exp(3, (MOD - 1) / i);
		for(int j = 0; j < len; j += i) {
			long long w = 1;
			const int borne = j + (i >> 1);
			for(int k=j,kd=k+(i>>1);k<borne;++k,++kd) {
				t = a[kd] * w % MOD;
				a[kd] = a[k] - t;
				if(a[kd] < 0) a[kd] += MOD;
				a[k] = a[k] + t;
				if(a[k] >= MOD) a[k] -= MOD;
				w *= wn;
				w %= MOD;
			}
		}
	}
	if(type == -1) {
		for(int i=1;i<len>>1;i++) swap(a[i],a[len-i]);
		for(int i=0;i<len;i++) a[i]=a[i]*INV_TAILLE%MOD;
	}
}

vector<int> multiplier(vector<int> &P, vector<int> &Q) {
	for(long long bit = 30; bit >= 0; bit--)
		if((1LL << bit) >= max(P.size(), Q.size()))
			TAILLE = (1LL << (bit+1LL));
	INV_TAILLE = modInv(TAILLE, MOD);
	while(P.size() < TAILLE) P.push_back(0);
	while(Q.size() < TAILLE) Q.push_back(0);
	vector<int> R(TAILLE, 0);
	
	NTT(P, TAILLE, 1);
	NTT(Q, TAILLE, 1);
	
	for(int i = 0; i < TAILLE; i++)
		R[i] = (long long)P[i] * (long long)Q[i] % MOD;
	
	NTT(R, TAILLE, -1);
	
	return R;
}

vector<int> P, Q, R;

int main() {
	int deg;
	cin >> deg;
	P.resize(deg);
	for(int i = 0; i < deg; i++) cin >> P[i];
	cin >> deg;
	Q.resize(deg);
	for(int i = 0; i < deg; i++) cin >> Q[i];
	
	R = multiplier(P, Q);
}












































