#include <bits/stdc++.h>
using namespace std;
#define MAX 1001

int N;
int dp[MAX][MAX];

int sumRectangle(int x1,int y1,int x2,int y2) {
    return dp[x2][y2]-dp[x1-1][y2]-dp[x2][y1-1]+dp[x1-1][y1-1];
}

int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            scanf("%d",&dp[i][j]);
    
    for(int i=2;i<=N;i++) {
        dp[1][i]+=dp[1][i-1];
        dp[i][1]+=dp[i-1][1];
    }
    
    for(int i=2;i<=N;i++)
        for(int j=2;j<=N;j++)
            dp[i][j]+=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
    
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) cout<<dp[i][j]<<" ";
        cout<<endl;
    }
    
    cout<<sumRectangle(2,2,3,3)<<endl;
    
    return 0;
}
