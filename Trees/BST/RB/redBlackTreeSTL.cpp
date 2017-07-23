#include <bits/stdc++.h>
using namespace std;

set<int> redBlackTree;

int main()
{
    int nbQueries;
    cin >> nbQueries;
    while(nbQueries--) {
        char typeOfQuery;
        cin >> typeOfQuery;
        int x;
        cin >> x;
        if(typeOfQuery == INSERT)
            redBlackTree.insert(x);
        else if(typeOfQuery == QUESTION)
            cout << (redBlackTree.find(x) == redBlackTree.end() ? "yes" : "no") << endl;
        else if(typeOfQuery == ERASE)
            redBlackTree.erase(x);
        else if(typeOfQuery == SIZE)
            cout << redBlackTree.size() << endl;
        else if(typeOfQuery == COUNT)
            cout << redBlackTree.count(x);
        else
            cout << "unknown operation\n";
    }
    
    return 0;
}
