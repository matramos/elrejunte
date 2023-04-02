//Mas lento que Dijsktra, pero maneja arcos con peso negativo
//Can solve systems of "difference inequalities":
//1. for each inequality x_i - x_j <= k add an edge j->i with weight k
//2. create an extra node Z and add an edge Z->i with weigth 0 for
// each variable x_i in the inequalities
//3. run(Z): if negcycle, no solution, otherwise "dist" is a solution
struct BellmanFord {
	vector<vector<ii>> G;//ady. list with pairs (weight, dst)
	vector<ll> dist;
	int N;
	BellmanFord(int n) { N = n; G.rsz(n); dist.rsz(n); }
	void addEdge(int a, int b, int w) { G[a].pb(mp(w, b)); }
	void run(int src){//O(VE)
		dist[src] = 0;
		forn(i, N-1) forn(j, N) if(dist[j] != INF) forall(it, G[j])
			dist[it->snd] = min(dist[it->snd], dist[j] + it->fst);
	}

	bool hasNegCycle(){
		forn(j, N) if(dist[j] != INF) forall(it, G[j])
			if(dist[it->snd] > dist[j] + it->fst) return true;
		//inside if: all points reachable from it->snd will have -INF distance(do bfs)
		return false;
	}
};
