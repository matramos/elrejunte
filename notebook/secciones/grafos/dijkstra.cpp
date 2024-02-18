struct Dijkstra { // WARNING: ii usually needs to be pair<ll, int>
	vector<vector<ii>> G;//ady. list with pairs (weight, dst)
	vector<ll> dist;
	//vector<int> vp; // for path reconstruction (parent of each node)
	int N;
	Dijkstra(int n): G(n), N(n) {}
	void addEdge(int a, int b, ll w) { G[a].pb(mp(w, b)); }
	void run(int src) { //O(|E| log |V|)
		dist = vector<ll>(N, INF);
		//vp = vector<int>(N, -1);
		priority_queue<ii, vector<ii>, greater<ii>> Q;
		Q.push(make_pair(0, src)); dist[src] = 0;
		while(sz(Q)) {
			int node = Q.top().snd;
			ll d = Q.top().fst;
			Q.pop();
			if(d > dist[node]) continue;
			forall(it, G[node]) if(d + it->fst < dist[it->snd]) {
				dist[it->snd] = d + it->fst;
				//vp[it->snd] = node;
				Q.push(mp(dist[it->snd], it->snd));
			}
		}
	}
};
