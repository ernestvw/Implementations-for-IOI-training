//I read similar techniques in a blog ( it was in russian ) (http://e-maxx.ru/algo/lca_simpler)
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > g, p; //graph, ancestor-structure
int N;
int counter=0;
vector<int> d, in, out; //depth, check-in, check-out

int pow(int n, int e){
	if(e==0)
		return 1;
	if(1&e){
		int ret = pow(n, e>>1);
		return ret*ret*n;
	} else {
		int ret = pow(n, e>>1);
		return ret*ret;
	}
}

void dfs(int n, int pr, int dp){
	d[n] = dp;
	in[n] = counter++;
	p[n].push_back(pr);
	for(int x=1; pow(2, x)<dp; x++){
		p[n].push_back(p[p[n][x-1]][x-1]);
	}
	for(int x=0; x<g[n].size(); x++){
		if(g[n][x]!=pr){
			dfs(g[n][x], n, dp+1);
		}
	}
	out[n] = counter++;
}

bool ancestor(int P, int N){
	//returns whether P is ancestor of N, or equal
	if(in[P]<=in[N]&&out[P]>=out[N])
		return true;
	else
		return false;
}



int LCA(int A, int B){
	if(d[A]<d[B])//this is actually unnecessary
		swap(A, B);
	if(ancestor(A, B))
		return A;
	if(ancestor(p[A][0], B))
		return p[A][0];
	int x=0;
	for(; x<p[A].size(); x++){
		if(ancestor(p[A][x], B))
			break; //2^xth ancestor of A also ancestor of B
	}
	return LCA(p[A][x-1], B);
}

int main(){
	cin>>N;
	g.assign(N+1, vector<int>());
	d.assign(N+1, -1);
	in.assign(N+1, -1);
	out.assign(N+1, -1);
	p.assign(N+1, vector<int>());
	
	int A, B;
	for(int n=1; n<N; n++){
		cin>>A>>B;
		g[A].push_back(B);
		g[B].push_back(A);
	}
	//let's root the tree at 1
	dfs(1, -1, 1);
	int Q; cin>>Q;
	while(Q--){
		cin>>A>>B;
		cout << LCA(A, B) << endl;
	}
	return 0;
}
