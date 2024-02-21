typedef ll tf;
typedef ll tc;
const tf INF_FLOW = 1e14;
const tc INF_COST = 1e14;
struct edge {
	int u, v;
	tf cap, flow;
	tc cost;
	tf rem() { return cap - flow; }
};
struct MCMF {
	vector<edge> e;
	vector<vector<int>> g;
	vector<tf> vcap;
	vector<tc> dist;
	vector<int> pre;
	tc minCost;
	tf maxFlow;
	// tf wantedFlow; // Use it for fixed flow instead of max flow
	MCMF(int n): g(n), vcap(n), dist(n), pre(n) {}
	void addEdge(int u, int v, tf cap, tc cost) {
		g[u].pb(sz(e)); e.pb({u, v, cap, 0, cost});
		g[v].pb(sz(e)); e.pb({v, u, 0, 0, -cost});
	}
	// O(n*m * min(flow, n*m)), sometimes faster in practice
	void run(int s, int t) { 
		vector<bool> inq(sz(g));
		maxFlow = minCost = 0; // result will be in these variables
		while(1) {
			fill(vcap.begin(), vcap.end(), 0); vcap[s] = INF_FLOW;
			fill(dist.begin(), dist.end(), INF_COST); dist[s] = 0;
			fill(pre.begin(), pre.end(), -1); pre[s] = 0;
			queue<int> q; q.push(s); inq[s] = true;
			while(sz(q)) { // Fast bellman-ford
				int u = q.front(); q.pop(); inq[u] = false;
				for(auto eid : g[u]) {
					edge &E = e[eid];
					if(E.rem() && dist[E.v] > dist[u] + E.cost) {
						dist[E.v] = dist[u] + E.cost;
						pre[E.v] = eid;
						vcap[E.v] = min(vcap[u], E.rem());
						if(!inq[E.v]) q.push(E.v), inq[E.v] = true;
					}
				}
			}
			if (pre[t] == -1) break;
			tf flow = vcap[t];
			// flow = min(flow, wantedFlow - maxFlow); //For fixed flow
			maxFlow += flow;
			minCost += flow*dist[t];
			for (int v = t; v != s; v = e[pre[v]].u) {
				e[pre[v]].flow += flow;
				e[pre[v]^1].flow -= flow;
			}
			// if(maxFlow == wantedFlow) break; //For fixed flow
		}
	}
};
