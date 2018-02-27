#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 1000*1000*1000;

struct edge {
	int b, u, c, f;
	int back;
};

int n, m;
vector<vector<edge>> g;

void addEdge(int a, int b, int u, int c) {
	edge r1 = {b, u, c, 0, g[b].size()};
	edge r2 = {a, 0, -c, 0, g[a].size()};
	g[a].push_back(r1);
	g[b].push_back(r2);
}

int mcmf(int s, int t, int k) {
	int flow = 0, cost = 0;
	while(flow < k) {
		vector<int> id(n, 0);
		vector<int> d(n, INF);
		vector<int> q(n);
		vector<int> p(n);
		vector<int> pEdge(n);
		int qh = 0, qt = 0;
		q[qt++] = s;
		d[s] = 0;
		while(qh != qt) {
			int v = q[qh++];
			id[v] = 2;
			if(qh == n) qh = 0;
			for(int i = 0; i < g[v].size(); i++) {
				edge &r = g[v][i];
				if(r.f < r.u and d[v] + r.c < d[r.b]) {
					d[r.b] = d[v] + r.c;
					if(id[r.b] == 0) {
						q[qt++] = r.b;
						if(qt == n) qt = 0;
					}
					else if(id[r.b] == 2) {
						if(--qh == -1) qh = n-1;
						q[qh] = r.b;
					}
					id[r.b] = 1;
					p[r.b] = v;
					pEdge[r.b] = i;
				}
			}
		}
		if(d[t] == INF) break;
		int addflow = k - flow;
		for(int v = t; v != s; v = p[v]) {
			int pv = p[v];
			int pr = pEdge[v];
			addflow = min(addflow, g[pv][pr].u - g[pv][pr].f);
		}
		for(int v = t; v != s; v = p[v]) {
			int pv = p[v];
			int pr = pEdge[v];
			int r = g[pv][pr].back;
			g[pv][pr].f += addflow;
			g[v][r].f -= addflow;
			cost += g[pv][pr].c * addflow;
		}
		flow += addflow;
	}
	return cost;
}

int main() {
	int k;
	scanf("%d%d%d", &n, &m, &k);
	g.resize(n);
	for(int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a--, b--;
		addEdge(a, b, 1, c);
	}

	printf("%d\n", mcmf(0, n-1, k));

	return 0;
}
