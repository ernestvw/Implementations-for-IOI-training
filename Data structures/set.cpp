#include <bits/stdc++.h>
using namespace std;

int add(int SET,int val) {
    SET|=(1<<val);
    return SET;
}

bool inSet(int SET,int val) {
    return SET&(1<<val);
}

void outputElements(int SET) {
    for(int i=0;i<32;i++)
        if(inSet(SET,i)) printf("%d ",i);
    printf("\n");
}

int UNION(int SET1,int SET2) {
    int SET3=SET1|SET2;
    return SET3;
}
