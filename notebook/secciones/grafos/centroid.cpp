// Usage: 1. Centroid(# nodes), 2. add tree edges, 3. build(), 4. use it
struct Centroid {
	vector<vector<int>> g;
	vector<int> vp, vsz;
	vector<bool> taken;
	Centroid(int n) : g(n), vp(n), vsz(n), taken(n) {}
	void addEdge(int a, int b) { g[a].pb(b); g[b].pb(a); }
	void build() { centroid(0, -1, -1); } // O(nlogn)
	int dfs(int node, int p) {
		vsz[node] = 1;
		forall(it, g[node]) if(*it != p && !taken[*it])
			vsz[node] += dfs(*it, node);
		return vsz[node];
	}
	void centroid(int node, int p, int cursz) {
		if(cursz == -1) cursz = dfs(node, -1);
		forall(it, g[node]) if(!taken[*it] && vsz[*it] >= cursz/2) {
			vsz[node] = 0; centroid(*it, p, cursz); return;
		}
		taken[node] = true; vp[node] = p;
		forall(it, g[node]) if(!taken[*it]) centroid(*it, node, -1);
	}
};
