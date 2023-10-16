// Usage: 1. HLD(# nodes) 2. add tree edges 3. build() 4. use it
struct HLD {
	vector<int> w, p, dep; // weight,father,depth
	vector<vector<int>> g;
	HLD(int n) : w(n), p(n), dep(n), g(n), pos(n), head(n) {}
	void addEdge(int a, int b) { g[a].pb(b); g[b].pb(a); }
	void build() { p[0]=-1; dep[0]=0; dfs1(0); curpos=0; hld(0,-1); }
	void dfs1(int x) {
		w[x] = 1;
		for(int y : g[x]) if(y != p[x]) {
			p[y] = x; dep[y] = dep[x]+1; dfs1(y);
			w[x] += w[y];
		}
	}
	int curpos;
	vector<int> pos, head;
	void hld(int x, int c) {
		if(c < 0) c = x;
		pos[x] = curpos++; head[x] = c;
		int mx = -1;
		for(int y : g[x]) if(y != p[x] && (mx < 0 || w[mx] < w[y])) mx = y;
		if(mx >= 0) hld(mx, c);
		for(int y : g[x]) if(y != mx && y != p[x]) hld(y, -1);
	}
	// Here ST is segtree static/dynamic/lazy according to problem
	tipo query(int x, int y, ST &st) { // ST tipo
		tipo r = neutro;
		while(head[x] != head[y]) {
			if(dep[head[x]] > dep[head[y]]) swap(x,y);
			r = oper(r, st.get(pos[head[y]], pos[y]+1)); // ST oper
			y = p[head[y]];
		}
		if(dep[x] > dep[y]) swap(x,y); // now x is lca
		r = oper(r, st.get(pos[x], pos[y]+1)); // ST oper
		return r;
	}
};
// for point updates: st.set(pos[x], v) (x = node, v = new value)
// for lazy range updates: something similar to the query method
// for queries on edges: - assign values of edges to "child" node
//                       - change pos[x] to pos[x]+1 in query (line 34)
