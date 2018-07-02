int V;
vector<int> adj[1001];
bool seen[1001];
int match[1001];

bool aug(int u) {
	if(seen[u]) return 0;
	seen[u] = 1;
	for(int v : adj[u]) {
		if(match[v] == -1 or aug(match[v])) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}

int MCBM() {
	int mcbm = 0;
	fill_n(match, V+1, -1);
	for(int i = 0; i < V; i++) {
		fill_n(seen, V+1, 0);
		mcbm += aug(i);
	}
	return mcbm;
}
