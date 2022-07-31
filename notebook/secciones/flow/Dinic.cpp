struct Edge {
	int u, v;
	ll cap, flow;
	Edge() {}
	Edge(int uu, int vv, ll c): u(uu), v(vv), cap(c), flow(0) {}
};
struct Dinic {
	int N;
	vector<Edge> E;
	vector<vector<int>> g;
	vector<int> d, pt;
	Dinic(int n): N(n), E(0), g(n), d(n), pt(n) {} //clear and init
	void addEdge(int u, int v, ll cap) {
		if (u != v) {
			E.emplace_back(Edge(u, v, cap));
			g[u].emplace_back(E.size() - 1);
			E.emplace_back(Edge(v, u, 0));
			g[v].emplace_back(E.size() - 1);
		}
	}
	bool BFS(int S, int T) {
		queue<int> q({S});
		fill(d.begin(), d.end(), N + 1);
		d[S] = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if (u == T) break;
			for (int k: g[u]) {
				Edge &e = E[k];
				if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
					d[e.v] = d[e.u] + 1;
					q.emplace(e.v);
				}
			}
		}
		return d[T] != N + 1;
	}
	ll DFS(int u, int T, ll flow = -1) {
		if (u == T || flow == 0) return flow;
		for (int &i = pt[u]; i < sz(g[u]); ++i) {
			Edge &e = E[g[u][i]];
			Edge &oe = E[g[u][i]^1];
			if (d[e.v] == d[e.u] + 1) {
				ll amt = e.cap - e.flow;
				if (flow != -1 && amt > flow) amt = flow;
				if (ll pushed = DFS(e.v, T, amt)) {
					e.flow += pushed;
					oe.flow -= pushed;
					return pushed;
				}
			}
		}
		return 0;
	}
	ll maxFlow(int S,int T) { //O(V^2*E), unit nets: O(sqrt(V)*E)
		ll total = 0;
		while(BFS(S, T)) {
			fill(pt.begin(), pt.end(), 0);
			while (ll flow = DFS(S, T)) total += flow;
		}
		return total;
	}
};
// Dinic wrapper to allow setting min flow on edges
struct DinicWithMinOnEdges {
	int N;
	vector<pair<Edge, ll>> E; // (normal dinic edge, min flow)
	Dinic dinic;
	DinicWithMinOnEdges(int n): N(n), E(0), dinic(n+2) {}
	void addEdge(int u, int v, ll cap, ll minFlow) {
		assert(minFlow <= cap);
		if (u != v) E.emplace_back(mp(Edge(u, v, cap), minFlow));
	}
	ll maxFlow(int S, int T) { // Same complexity as normal Dinic
		int SRC = N, SNK = N+1;
		ll minFlowSum = 0;
		forall(e, E) { // force the min flow
			minFlowSum += e->snd;
			dinic.addEdge(SRC, e->fst.v, e->snd);
			dinic.addEdge(e->fst.u, SNK, e->snd);
			dinic.addEdge(e->fst.u, e->fst.v, e->fst.cap - e->snd);
		}
		dinic.addEdge(T,S,INF); // INF >= max possible flow
		ll flow = dinic.maxFlow(SRC, SNK);
		if(flow < minFlowSum) return -1; // no valid flow exists
		assert(flow == minFlowSum);
		// Not sure why this commented part doesn't seem to be
		// necessary. And also not sure why it's not needed to
		// rebuild the dinic for getting the actual maxflow
		/*forn(i,sz(E)) {
			dinic.E[6*i+4].cap += E[i].snd;
			dinic.E[6*i+4].flow += E[i].snd;
			dinic.E[6*i+5].flow -= E[i].snd;
		}
		forn(_,2) dinic.E.pop_back();*/
		return dinic.maxFlow(S, T);
	}
};
