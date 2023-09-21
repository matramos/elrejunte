// https://cses.fi/problemset/task/2077/
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define dforall(it,v) for(auto it=v.rbegin();it!=v.rend();it++)
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

struct Bicon {
	vector<vector<int>> G;
	struct edge {
		int u, v, comp;
		bool bridge;
	};
	vector<edge> ve;
	void addEdge(int u, int v) {
		G[u].pb(sz(ve)), G[v].pb(sz(ve));
		ve.pb({u, v, -1, false});
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
	void run() { forn(i,n) if(d[i] == -1) art[i]--, dfs(i,-1); }
	// block-cut tree (copy only if needed)
	vector<set<int>> bctree; // set to dedup
	vector<int> artid; // art nodes to tree node (-1 for !arts)
	void buildBlockCutTree() { // call run first!!
		// node id: [0, nbc) -> bc, [nbc, nbc+nart) -> art
		int ntree = nbc+nart, auxid = nbc;
		bctree = vector<set<int>>(ntree);
		artid = vector<int>(n, -1);
		forn(i,n) if(art[i] > 0) {
			forall(eid, G[i]) { // edges always bc <-> art
				// depending on the problem, may want
				// to add more data on bctree edges
				bctree[auxid].insert(ve[*eid].comp);
				bctree[ve[*eid].comp].insert(auxid);
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


int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m;
	cin >> n >> m;
	Bicon bicon(n);
	forn(_,m)
	{
		int a,b;
		cin >> a >> b;
		a--;b--;
		bicon.addEdge(a,b);
	}
	bicon.run();
	cout << bicon.nart << '\n';
	bool fst = true;
	forn(i,n) if(bicon.art[i] > 0)
	{
		if(fst) fst = false;
		else cout << ' ';
		cout << i+1;
	}
	cout << '\n';
	return 0;
}
