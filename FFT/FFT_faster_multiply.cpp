#include <bits/stdc++.h>
using namespace std;

typedef long double num;

int retourner(int n, int b) {
	int r = 0;
	b = b >> 1;
	while(b) {
		r = r << 1;
		r |= n & 1;
		n = n >> 1;
		b = b >> 1;
	}
	return r;
}

int puissance(int n) {
	int k = 0;
	while(n) {
		k++;
		n = n >> 1;
	}
	return 1 << k;
}

void FFT(vector<num>& reel, vector<num>& imag) {
	int n = reel.size();
	if(n == 1) return;
	vector<num> re(n), im(n);
	for(int i = 0; i < n; i++) {
		re[i] = reel[retourner(i, n)];
		im[i] = imag[retourner(i, n)];
	}
	int bs = 1;
	num mr = -1, mi = 0, cr = 1, ci = 0;
	while(bs != n) {
		for(int i = 0; i < n; i++) {
			if(i & bs) {
				i += bs;
				cr = 1;
				ci = 0;
				if(i >= n) continue;
			}
			num re1, im1, re2, im2, tr1, ti1, tr2, ti2;
			tr1 = re[i];
			ti1 = im[i];
			tr2 = re[i+bs];
			ti2 = im[i+bs];
			re1 = tr1 + tr2 * cr - ti2 * ci;
			im1 = ti1 + tr2 * ci + ti2 * cr;
			re2 = tr1 - tr2 * cr + ti2 * ci;
			im2 = ti1 - tr2 * ci - ti2 * cr;
			re[i] = re1;
			im[i] = im1;
			re[i+bs] = re2;
			im[i+bs] = im2;
			tr1 = cr;
			ti1 = ci;
			cr = tr1 * mr - ti1 * mi;
			ci = tr1 * mi + ti1 * mr;
		}
		if(mr == -1) {
			mr = 0;
			mi = 1;
		}
		else {
			mr++;
			num len = sqrt(mr * mr + mi * mi);
			mr /= len;
			mi /= len;
		}
		bs = bs << 1;
	}
	reel.swap(re);
	imag.swap(im);
}

void iFFT(vector<num>& reel, vector<num>& imag) {
	FFT(imag, reel);
	int n = reel.size();
	for(int i = 0; i < n; i++) {
		reel[i] /= n;
		imag[i] /= n;
	}
}

void mult(num &r1, num &i1, num &r2, num &i2){
	num tr1 = r1;
	num ti1 = i1;
	r1 = tr1 * r2 - ti1 * i2;
	i1 = ti1 * r2 + tr1 * i2;
}

vector<int> multiplier(vector<int> P, vector<int> Q) {
	int n = puissance(P.size() + Q.size());
	vector<num> re1(n, 0), im1(n, 0);
	vector<num> re2(n, 0), im2(n, 0);
	for(int i = 0; i < P.size(); i++)
		re1[i] = (num)P[i];
	for(int i = 0; i < Q.size(); i++)
		re2[i] = (num)Q[i];
	FFT(re1, im1);
	FFT(re2, im2);
	for(int i = 0; i < n; i++)
		mult(re1[i], im1[i], re2[i], im2[i]);
	vector<int> R;
	iFFT(re1, im1);
	for(num p : re1)
		R.push_back(round(p));
	while(!R.back()) R.pop_back();
	return R;
}

int main() {
	int n;
	scanf("%d", &n);
	vector<int> P(n, 0), Q(n, 0);
	for(int i = 0; i < n; i++)
		scanf("%d", &P[i]);
	for(int i = 0; i < n; i++)
		scanf("%d", &Q[i]);
	
	vector<int> R = multiplier(P, Q);
	
	for(int i : R) printf("%d ", i);
	printf("\n");


	return 0;
}






























