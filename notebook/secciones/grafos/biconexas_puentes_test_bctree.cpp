// Problem: https://codeforces.com/gym/103427/problem/H
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

struct Bicon {
	vector<vector<int>> G;
	struct edge {
		int u, v, comp, w;
		bool bridge;
	};
	vector<edge> ve;
	void addEdge(int u, int v, int w) {
		G[u].pb(sz(ve)), G[v].pb(sz(ve));
		ve.pb({u, v, -1, w, false});
	}
	// d[i] = dfs id
	// b[i] = lowest id reachable from i
	// art[i]>0 iff i is an articulation point
	// nbc = total # of biconnected comps
	// nart = total # of articulation points
	vector<int> d, b, art;
	int n, t, nbc, nart;
	Bicon(int nn) {
		n = nn;
		t = nbc = nart = 0;
		b = d = vector<int>(n,-1);
		art = vector<int>(n,0);
		G = vector<vector<int>>(n);
		ve.clear();
	}
	stack<int> st;
	void dfs(int u, int pe) { //O(n + m)
		b[u] = d[u] = t++;
		forall(eid, G[u]) if(*eid != pe) {
			int v = ve[*eid].u ^ ve[*eid].v ^ u;
			if(d[v] == -1) {
				st.push(*eid); dfs(v, *eid);
				if(b[v] > d[u]) ve[*eid].bridge = true; // bridge
				if(b[v] >= d[u]) { // art
					if(art[u]++ == 0) nart++;
					int last; // start biconnected
					do {
						last = st.top(); st.pop();
						ve[last].comp = nbc;
					}while(last != *eid);
					nbc++; // end biconnected
				}
				b[u] = min(b[u], b[v]);
			}
			else if(d[v] < d[u]) { // back edge
				st.push(*eid);
				b[u] = min(b[u], d[v]);
			}
		}
	}
	void run() { forn(i,n) if(d[i] == -1) dfs(i,-1); }
	// block-cut tree (copy only if needed)
	vector<map<int, int>> bctree; // set to dedup
	vector<int> artid; // art nodes to tree node (-1 for !arts)
	void buildBlockCutTree() { // call run first!!
		// node id: [0, nbc) -> bc, [nbc, nbc+nart) -> art
		int ntree = nbc+nart, auxid = nbc;
		bctree = vector<map<int, int>>(ntree);
		artid = vector<int>(n, -1);
		forn(i,n) if(art[i]) {
			forall(eid, G[i]) { // edges always bc <-> art
				// depending on the problem, may want
				// to add more data on bctree edges
				int w = 2e9;
				if(ve[*eid].bridge) w = ve[*eid].w;
				if(!bctree[auxid].count(ve[*eid].comp)) bctree[auxid][ve[*eid].comp] = bctree[ve[*eid].comp][auxid] = w;
				bctree[auxid][ve[*eid].comp] = bctree[ve[*eid].comp][auxid] = min(bctree[auxid][ve[*eid].comp], w);
			}
			artid[i] = auxid++;
		}
	}
	int getTreeIdForGraphNode(int u) {
		if(artid[u] != -1) return artid[u];
		if(!G[u].empty()) return ve[G[u][0]].comp;
		return -1; // for nodes with no neighbours in G
	}
};

Bicon bicon(0);
vector<int> vcnt;
vector<int> bcEdgeCount;

int dfs1(int node, int p)
{
	int ret = 0;
	if(node < bicon.nbc) ret += bcEdgeCount[node];
	forall(it, bicon.bctree[node]) if(it->fst != p) ret += dfs1(it->fst, node);
	return vcnt[node] = ret;
}

int dfs2(int node, int p, int fromp)
{
	int ret = 2e9;
	forall(it, bicon.bctree[node])
	{
		if(it->fst != p)
		{
			ret = min(ret, dfs2(it->fst, node, fromp+vcnt[node]-vcnt[it->fst]));
			if(vcnt[it->fst]%2 == 0 && node < bicon.nbc) ret = min(ret, it->snd);
		}
		else if(fromp%2 == 0 && node < bicon.nbc) ret = min(ret, it->snd);
	}
	return ret;
}

int n,m;

int solve()
{
	if(m%2 == 0) return 0;
	bicon.run();
	bicon.buildBlockCutTree();
	int ret = 2e9;
	bcEdgeCount.rsz(bicon.nbc,0);
	forall(it,bicon.ve)
	{
		bcEdgeCount[it->comp]++;
		if(!it->bridge) ret = min(ret, it->w);
	}
	int node0 = bicon.getTreeIdForGraphNode(0);
	vcnt.rsz(sz(bicon.bctree),0);
	assert(dfs1(node0, node0) == m);
	ret = min(ret, dfs2(node0, node0, 0));
	return ret;
}

int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m;
	bicon = Bicon(n);
	ll sum = 0;
	forn(i,m)
	{
		int a,b,w;
		cin >> a >> b >> w;
		a--;b--;
		bicon.addEdge(a,b,w);
		sum += w;
	}
	cout << sum - solve() << '\n';
	return 0;
}
