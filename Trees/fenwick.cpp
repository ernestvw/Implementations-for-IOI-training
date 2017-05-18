#include <bits/stdc++.h>
using namespace std;
#define MAX 1001

int A[MAX];
int N;

void update(int BIT[],int i,int val)
{
    while(i<=N)
    {
        BIT[i]+=val;
        i += i&(-i);
    }
}

void updateRange(int BIT1[],int BIT2[],int a,int b,int val) {
    update(BIT1,a,val);
    update(BIT1,b+1,-val);
    update(BIT2,a,val*(a-1));
    update(BIT2,b+1,-val*b);
}

int query(int BIT[],int i)
{
    int sum=0;
    while(i>0)
    {
        sum+=BIT[i];
        i -= i&(-i);
    }
    return sum;
}

int sum(int BIT1[],int BIT2[],int i) {
    return query(BIT1,i)*i-query(BIT2,i);
}

int main()
{
    scanf("%d",&N);
    int BIT1[N+2]={0};
    int BIT2[N+2]={0};
    for(int i=1;i<=N;i++) {
        scanf("%d",&A[i]);
        updateRange(BIT1,BIT2,i,i,A[i]);
    }
    updateRange(BIT1,BIT2,2,5,2);
    for(int i=1;i<=N;i++) cout<<sum(BIT1,BIT2,i)-sum(BIT1,BIT2,i-1)<<" ";
    cout<<endl;
    
    return 0;
}
