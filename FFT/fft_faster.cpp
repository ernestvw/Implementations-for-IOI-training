#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long double num;
typedef vector<num> vn;
typedef pair<num, num> nn;
typedef vector<nn> vnn;

vnn table;
int N;
void pn(nn p){
    //printf("%.3Lf %.3Lf\n", p.first, p.second);
}

void printTable(vnn t = table){
 
    for(auto p : t){
        pn(p);
    }
}

int rev(int n, int b){
    int r = 0;
    b = b >> 1;
    while(b){
        r = r << 1;
        r |= n & 1;
        n = n >> 1;
        b = b >> 1;
    }
    return r;
}

void fft(vn& real, vn& imag){
    int n = real.size();
    if(n == 1) return;
    vn re(n);
    vn im(n);
    for(int i = 0; i < n; i++){
        re[i] = real[rev(i, n)];
        im[i] = imag[rev(i, n)];
    }
    int bs = 1;
    num mr = -1;
    num mi = 0;
    num cr = 1;
    num ci = 0;
    while(bs != n){

        for(int i = 0; i < n; i++){
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
        if(mr == -1){
            mr = 0;
            mi = 1;
        } else {
            mr++;
            num len = sqrt(mr * mr + mi * mi);
            mr /= len;
            mi /= len; 
        }
        bs = bs << 1;
    }
    real.swap(re);
    imag.swap(im);
}

void ifft(vn& real, vn& imag){
    fft(imag, real);
    int n = real.size();
    for(int i = 0; i < n; i++){
        real[i] /= n;
        imag[i] /= n;
    }
}

int main(){
    
    vn imag(8, 0);
    vn real(8);
    real[0] = 1;
    real[1] = 1;
    real[2] = 1;
    real[3] = 1;
    real[4] = 1;
    real[5] = 1;
    real[6] = 1;
    real[7] = 1;

    fft(real, imag);
    //ifft(real, imag);
    for(int i = 0; i < real.size(); i++){
        printf("%.3Lf %.3Lf\n", real[i], imag[i]);
    }
}



