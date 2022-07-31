// Problem: https://codeforces.com/problemset/problem/704/D
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
#else
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

const int INF = 100010;

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


int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m;
	ll r,b;
	cin >> n >> m >> r >> b;
	int idx = 0, idy = n;
	map<int,int> cntx, cnty, mx, my, midx, midy;
	int auxid = 0;
	map<ii,vector<int>> mid;
	DinicWithMinOnEdges dinic(2*n+2);
	int SRC = 2*n, SNK = 2*n+1;
	forn(i,n)
	{
		int x,y;
		cin >> x >> y;
		if(!midx.count(x)) midx[x] = idx++;
		if(!midy.count(y)) midy[y] = idy++;
		mid[mp(midx[x], midy[y])].pb(auxid++);
		cntx[x]++;
		cnty[y]++;
		dinic.addEdge(midx[x], midy[y], 1, 0);
	}
	forn(i,m)
	{
		int t,l,d;
		cin >> t >> l >> d;
		if(t == 1)
		{
			if(!cntx.count(l)) continue;
			if(cntx[l]%2 && d == 0)
			{
				cout << "-1\n";
				return 0;
			}
			mx[l] = max(mx[l], (cntx[l]-d+1)/2);
		}
		else
		{
			if(!cnty.count(l)) continue;
			if(cnty[l]%2 && d == 0)
			{
				cout << "-1\n";
				return 0;
			}
			my[l] = max(my[l], (cnty[l]-d+1)/2);
		}
	}
	forall(it,cntx)
	{
		assert(it->snd >= 2*mx[it->fst]);
		dinic.addEdge(SRC, midx[it->fst], it->snd-mx[it->fst], mx[it->fst]);
	}
	forall(it,cnty)
	{
		assert(it->snd >= 2*my[it->fst]);
		dinic.addEdge(midy[it->fst], SNK, it->snd-my[it->fst], my[it->fst]);
	}
	ll f1 = dinic.maxFlow(SRC, SNK);
	if(f1 == -1)
	{
		cout << "-1\n";
		return 0;
	}
	assert(f1 >= (n+1)/2);
	ll f2 = n-f1;
	char goodc = 'b', badc = 'r';
	if(b > r) swap(goodc, badc);
	cout << f1*min(b,r) + f2*max(b,r) << '\n';
	string ans;
	ans.rsz(n,badc);
	forn(i,idx) forall(eid, dinic.dinic.g[i]) if(dinic.dinic.E[*eid].flow == 1)
	{
		int u = dinic.dinic.E[*eid].u;
		int v = dinic.dinic.E[*eid].v;
		assert(u == i);
		//cout << "edge " << u << ' ' << v << '\n';
		assert(!mid[mp(u,v)].empty());
		ans[mid[mp(u,v)].back()] = goodc;
		mid[mp(u,v)].pop_back();
	}
	cout << ans << '\n';
	return 0;
}
