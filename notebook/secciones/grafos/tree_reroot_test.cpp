// Problem: https://codeforces.com/problemset/problem/543/D
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
#else
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

#define MOD 1000000007

struct Edge {
	int u, v; // maybe add more data, depending on the problem
};
// USAGE:
// 1- define all the logic in SubtreeData
// 2- create a reroot and add all the edges
// 3- call Reroot.run()
struct SubtreeData {
	// Define here what data you need for each subtree
	ll ways[2];
	SubtreeData(){} // just empty
	SubtreeData(int node) {
		// Initialize the data here as if this new subtree
		// has size 1, and its only node is 'node'
		ways[0] = 1;
		ways[1] = 0;
	}
	void merge(Edge* e, SubtreeData &s) {
		// Modify this subtree's data to reflect that 's' is being
		// merged into 'this' through the edge 'e'.
		// When e == NULL, then no edge is present, but the root of
		// 's' is the same as the root of 'this', these 2 subtrees
		// don't have any other shared nodes nor edges.
		ll new0 = ways[0]*s.ways[0]%MOD;
		ll new1 = (e != NULL) * ways[1];
		forn(i,2)forn(j,2) if(e != NULL || i+j != 0) new1 = (new1 + ways[i]*s.ways[j])%MOD;
		ways[0] = new0;
		ways[1] = new1;
	}
};
struct Reroot {
	int N; // # of nodes
	// vresult[i] = SubtreeData for the tree where i is the root
	// this should be what you need as result
	vector<SubtreeData> vresult, vs;
	vector<Edge> ve;
	vector<vector<int>> g; // the tree as a bidirectional graph
	Reroot(int n): N(n), vresult(n), vs(n), ve(0), g(n) {}
	void addEdge(Edge e) { // will be added in both ways
		g[e.u].pb(sz(ve)); g[e.v].pb(sz(ve));
		ve.pb(e);
	}
	void dfs1(int node, int p) {
		vs[node] = SubtreeData(node);
		forall(e, g[node]) {
			int nxt = node ^ ve[*e].u ^ ve[*e].v;
			if(nxt == p) continue;
			dfs1(nxt, node);
			vs[node].merge(&ve[*e], vs[nxt]);
		}
	}
	void dfs2(int node, int p, SubtreeData fromp) {
		vector<SubtreeData> vsuf(sz(g[node])+1);
		int pos = sz(g[node]);
		SubtreeData pref = vsuf[pos] = SubtreeData(node);
		vresult[node] = vs[node];
		dforall(e, g[node]) { // dforall = forall in reverse
			pos--;
			vsuf[pos] = vsuf[pos+1];
			int nxt = node ^ ve[*e].u ^ ve[*e].v;
			if(nxt == p) {
				pref.merge(&ve[*e], fromp);
				vresult[node].merge(&ve[*e], fromp);
				continue;
			}
			vsuf[pos].merge(&ve[*e], vs[nxt]);
		}
		assert(pos == 0);
		forall(e, g[node]) {
			pos++;
			int nxt = node ^ ve[*e].u ^ ve[*e].v;
			if(nxt == p) continue;
			SubtreeData aux = pref;
			aux.merge(NULL, vsuf[pos]);
			dfs2(nxt, node, aux);
			pref.merge(&ve[*e], vs[nxt]);
		}
	}
	void run() {
		dfs1(0, 0);
		dfs2(0, 0, SubtreeData());
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
	int n;
	cin >> n;
	Reroot reroot(n);
	forn(i,n-1)
	{
		int x;
		cin >> x;
		x--;
		reroot.addEdge({x, i+1});
	}
	reroot.run();
	forn(i,n)
	{
		if(i) cout << ' ';
		cout << (reroot.vresult[i].ways[0] + reroot.vresult[i].ways[1])%MOD;
	}
	cout << '\n';
	return 0;
}
