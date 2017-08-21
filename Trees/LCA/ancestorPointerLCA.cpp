//source: some CF blog (http://codeforces.com/blog/entry/22325)
//this technique can be used as an alternative to heavy-light decomposition or other decomposition of a tree
#include <iostream>
#include <vector>

using namespace std;

//max number of ancestors noted
const int maxp = 20; //2^20= large number

vector<vector<int> > g;//contains the graph
vector<vector<int> > p; //contains log(N) ancestors of each node, the 2^0th ancestor, the 2^1st ancestor etc.
vector<int> d;//contains the depth of each node

//efficient power function
int power(int f, int s){
	if(s==0){
		return 1;
	}
	if(s&1){
		int ret = power(f, (s>>1));
		return ret*ret*f;
	} else {
		int ret = power(f, (s>>1));
		return ret*ret;
	}
}

void dfs(int n, int pn, int dpth){
	d[n] = dpth;
	p[n][0] = pn; //0th ancestor is direct parent
	for(int i=1; power(2, i)<dpth; i++){
		p[n][i] = p[p[n][i-1]][i-1];
	}
	for(int x=0; x<g[n].size(); x++){
		if(g[n][x]!=pn){
			dfs(g[n][x], n, dpth+1);
		}
	}
}

//if dp>d[n], this recursion will never finish
int ancestorAtDepth(int n, int dp){
	if(d[n]==dp){
		return n;
	} else {
		int x=0;
		for(; x<p[n].size(); x++){
			if(d[p[n][x]]<dp){
				break;
			}
		}
		return ancestorAtDepth(d[p[n][x-1]], dp);
	}
}

int approachLCA(int A, int B){
	if(A==B){
		return A;
	}
	if(p[A][0]==p[B][0]){
		return p[A][0];
	}
	int x=0;
	for(; x<p[A].size(); x++){
		if(p[A][x]==p[B][x])
			break;
	}
	return approachLCA(p[A][x], p[B][x]);
}

int LCA(int A, int B){
	if(d[B]<d[A])
		swap(A, B);
	//B is always deeper
	B = ancestorAtDepth(B, d[A]);
	return approachLCA(A, B);
}

int main(){
	int N; cin>>N;
	//for the purpose of this problem, the tree will be rooted at 1
	int A, B;
	g.assign(N+1, vector<int>());
	d.assign(N+1, 0);
	p.assign(N+1, vector<int>(20, -1));
	for(int n=1; n<N; n++){
		cin>>A>>B;
		g[A].push_back(B);
		g[B].push_back(A);
	}
	dfs(1, -1, 1);
	int Q; cin>>Q;
	while(Q--){
		int A, B; cin>>A>>B;
		cout << LCA(A, B) << endl;
	}
	return 0;
}
