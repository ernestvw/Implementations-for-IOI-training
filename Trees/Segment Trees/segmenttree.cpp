#include <bits/stdc++.h>
using namespace std;
#define MAX 200001

int N;
int A[MAX];
int segment[MAX];

int sum(int a,int b) {
    a+=N,b+=N;
    int s=0;
    while(a<=b) {
        if(a%2==1) s+=segment[a++];
        if(b%2==0) s+=segment[b--];
        a/=2,b/=2;
    }
    return s;
}

void add(int i,int x) {
    i+=N;
    segment[i]+=x;
    for(i/=2;i>=1;i/=2)
        segment[i]=segment[2*i]+segment[2*i+1];
}


/* LAZY PROPAGATION */
void util(int si,int ss,int se,int s,int d,int val) {
    if(lazy[si]) {
        segment[si]+=(se-ss+1)*lazy[si];
        if(ss!=se) {
            lazy[si*2+1]+=lazy[si];
            lazy[si*2+2]+=lazy[si];
        }
        lazy[si]=0;
    }
    if(ss>se || ss>d || se<s) return;
    if(ss>=s && se<=d) {
        segment[si]+=(se-ss+1)*val;
        if(ss!=se) {
            lazy[si*2+1]+=val;
            lazy[si*2+2]+=val;
        }
        return;
    }
    int mid=(ss+se)/2;
    util(si*2+1,ss,mid,s,d,val);
    util(si*2+2,mid+1,se,s,d,val);
    segment[si]=segment[si*2+1]+segment[si*2+2];
}

void updateRange(int s,int d,int val) {
    util(0,0,N-1,s,d,val);
}

int getSumUtil(int ss,int se,int s,int d,int si) {
    if(lazy[si]) {
        segment[si]+=(se-ss+1)*lazy[si];
        if(ss!=se) {
            lazy[si*2+1]+=lazy[si];
            lazy[si*2+2]+=lazy[si];
        }
        lazy[si]=0;
    }
    if(ss>se || ss>d || se<s) return 0;
    if(ss>=s && se<=d) return segment[si];
    int mid=(ss+se)/2;
    return getSumUtil(ss,mid,s,d,2*si+1)+getSumUtil(mid+1,se,s,d,2*si+2);
}

int getSum(int s,int d) {
    if(s<0 || d>N-1 || s>d) return -1;
    return getSumUtil(0,N-1,s,d,0);
}
