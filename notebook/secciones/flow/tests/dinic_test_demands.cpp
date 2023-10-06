// https://codeforces.com/gym/101308/problem/I
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef ANARAP
//local
#else
//judge
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

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

const int INF = 10010;

// Dinic wrapper to allow setting demands of min flow on edges
struct DinicWithDemands {
	int N;
	vector<pair<Edge, ll>> E; // (normal dinic edge, min flow)
	Dinic dinic;
	DinicWithDemands(int n): N(n), E(0), dinic(n+2) {}
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
		// Now go back to the original network, to a valid
		// state where all min flow values are satisfied.
		forn(i,sz(E)) {
			forn(j,4) {
			    assert(j%2 || dinic.E[6*i+j].flow == E[i].snd);
			    dinic.E[6*i+j].cap = dinic.E[6*i+j].flow = 0;
			}
			dinic.E[6*i+4].cap += E[i].snd;
			dinic.E[6*i+4].flow += E[i].snd;
			// don't change edge [6*i+5] to keep forcing the mins
		}
		forn(i,2) dinic.E[6*sz(E)+i].cap = dinic.E[6*sz(E)+i].flow = 0;
		// Just finish the maxFlow now
		dinic.maxFlow(S, T);
		flow = 0; // get the result manually
		forall(e, dinic.g[S]) flow += dinic.E[*e].flow;
		return flow;
	}
};



int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output","w", stdout);
	#else
		freopen("inspection.in", "r", stdin);
		freopen("inspection.out","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	vector<ii> v;
	forn(i,n)
	{
		int k;
		cin >> k;
		forn(_,k)
		{
			int x;
			cin >> x;
			v.pb(mp(i,x-1));
		}
	}
	int L = 1, R = sz(v);
	const int SRC0 = n, SRC1 = n+1, SNK = n+2;
	while(L < R)
	{
		int M = (L+R)/2;
		DinicWithDemands dinic(n+3);
		forall(it,v) dinic.addEdge(it->fst, it->snd, M, 1);
		dinic.addEdge(SRC0, SRC1, M, 0);
		forn(i,n)
		{
			dinic.addEdge(SRC1, i, M, 0);
			dinic.addEdge(i, SNK, M, 0);
		}
		if(dinic.maxFlow(SRC0, SNK) == -1) L = M+1;
		else R = M;
	}
	DinicWithDemands dinic(n+3);
	forall(it,v) dinic.addEdge(it->fst, it->snd, L, 1);
	dinic.addEdge(SRC0, SRC1, L, 0);
	forn(i,n)
	{
		dinic.addEdge(SRC1, i, L, 0);
		dinic.addEdge(i, SNK, L, 0);
	}
	assert(dinic.maxFlow(SRC0, SNK) == L);
	cout << L << '\n';
	forn(i,L)
	{
		int node = SRC1;
		while(node != SNK)
		{
			bool found = false;
			if(node != SRC1) cout << node+1 << ' ';
			forall(it,dinic.dinic.g[node]) if(*it%2 == 0 && dinic.dinic.E[*it].flow)
			{
				int nxt = node^dinic.dinic.E[*it].u^dinic.dinic.E[*it].v;
				if(nxt <= SNK)
				{
					node = nxt;
					found = true;
					dinic.dinic.E[*it].flow--;
					break;
				}
			}
			assert(found);
		}
		cout << '\n';
	}
	return 0;
}
