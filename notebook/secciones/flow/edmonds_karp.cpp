struct EdmondsKarp {
	int N;
	vector<unordered_map<int,ll>> g;
	vector<int> p;
	ll f;
	EdmondsKarp(int n) : N(n), g(n), p(n) {}
	void addEdge(int a, int b, int w) { g[a][b] = w; }
	void augment(int v, int SRC, ll minE) {
		if(v == SRC) f = minE;
		else if(p[v] != -1) {
			augment(p[v], SRC, min(minE, g[p[v]][v]));
			g[p[v]][v] -= f, g[v][p[v]] += f;
		}
	}
	ll maxflow(int SRC, int SNK) { //O(min(VE^2,Mf*E))
		ll ret = 0;
		do {
			queue<int> q; q.push(SRC);
			fill(p.begin(), p.end(), -1);
			f = 0;
			while(sz(q)) {
				int node = q.front(); q.pop();
				if(node == SNK) break;
				forall(it, g[node])if(it->snd > 0 && p[it->fst] == -1) {
					q.push(it->fst), p[it->fst] = node;
				}
			}
			augment(SNK, SRC, INF); // INF > max possible flow
			ret += f;
		} while(f);
		return ret;
	}
};
