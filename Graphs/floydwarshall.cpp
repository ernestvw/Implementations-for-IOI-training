#include <bits/stdc++.h>
using namespace std;
#define MAX 1001
#define INF (int)1e9

int V,E;
int D[MAX][MAX];

void floydwarshall() {
    for(int k=1;k<=V;k++) {
        for(int i=1;i<=V;i++) {
            for(int j=1;j<=V;j++) {
                D[i][j]=min(D[i][j],D[i][k]+D[k][j]);
            }
        }
    }
}

int main()
{
    scanf("%d%d",&V,&E);
    for(int i=1;i<=V;i++)
        for(int j=1;j<=V;j++)
            D[i][j]=INF;
    for(int i=0;i<E;i++) {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        D[u][v]=w;
    }
    
    floydwarshall();
    
    for(int i=2;i<=V;i++) printf("%d ",D[1][i]);
    printf("\n");
    
    return 0;
}
