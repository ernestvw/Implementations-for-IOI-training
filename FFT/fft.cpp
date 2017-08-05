#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long double num;
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

nn mult(nn a, nn b){
    return mp(a.first * b.first - a.second * b.second,
              a.first * b.second + a.second * b.first);
}

nn sum(nn a, nn b){
    return mp(a.first + b.first, a.second + b.second);
}

nn lookup(int k, int n){
    return table[k*table.size()/n];
}

// pre: n power of 2, n >= 4
void fillTable(int n){
    N = n;
    vnn t(n);
    table.assign(n, mp(0, 0));
    table[0] = mp(1, 0);
    table[1] = mp(0, 1);
    table[2] = mp(-1, 0);
    table[3] = mp(0, -1);

    int i = 4;
    while(i < n){
        for(int k = 0; k < i; k++){
            t[2*k] = table[k];
            
            auto temp = sum(table[k], table[(k+1) % i]);
            num l = sqrt(temp.first * temp.first + temp.second * temp.second);  
            temp.first /= l;
            temp.second /= l;
            t[2*k+1] = temp;
        }
        i *= 2;
        table.swap(t);
    }
}

vnn fft(vnn x){
    int n = x.size();
    if(n == 1) return x;
    vnn p, q;
    for(int i = 0; i < n; i++){
        i % 2 == 0 ? p.pb(x[i]) : q.pb(x[i]);
    }   
    p = fft(p);
    q = fft(q);
    for(int i = 0; i < n; i++){
        x[i] = sum(p[(i) % (n/2)], mult(q[(i) % (n/2)], lookup(i, n)));
    }
    return x;
}

vnn ifft(vnn x){
    reverse(x.begin()+1, x.end());
    x = fft(x);
    for(int i = 0; i < x.size(); i++){
        x[i].first /= x.size();
        x[i].second /= x.size();
    }
    return x;
}

int main(){
    fillTable(1 << 6);
    

    for(int i = 0; i < N; i++){
        printf("%.1Lf %.1Lf \n", lookup(i, N).first, lookup(i, N).second);
    }

    vnn x(4);
    x[0] = mp(1, 0);
    x[1] = mp(2, 0);
    x[2] = mp(3, 0);
    x[3] = mp(4, 0);
    
    auto y = ifft(fft(x));
    for(auto p : y){
      printf("%.199Lf %.199Lf\n", p.first, p.second);
    }
    
}



