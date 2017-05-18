#include <bits/stdc++.h>
using namespace std;
#define MAX 10001

int parent[MAX];

int find(int x) {
    return parent[x]==x ? x : (parent[x]=find(parent[x]));
}

void merge(int x,int y) {
    parent[find(x)]=find(y);
}
