#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = a; i<b; i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i = n-1; i>-1; i--)
#define forall(i,v) for(auto i = v.begin(); i != v.end(); i++)
#define sz(v) ((int) v.size()) 
#define pb push_back
#define fst first
#define snd second
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

struct green_hackenbush {
	vector<vector<int>> g;
	vector<int> tin, low, gr;
	int t, root, ans;
	green_hackenbush(int n) {
		t = 0, root = -1, ans = 0;
		g.resize(n); gr.resize(n);
		tin.resize(n); low.resize(n);
	}
	// make u a node in the ground
	void ground(int u) { 
		gr[u] = 1; if(root == -1) root = u;
	}
	// call first ground() if u or v are in the ground
	void add_edge(int u, int v) { 
		if(gr[u]) u = root;
		if(gr[v]) v = root;
		if(u == v) { ans ^= 1; return; }
		g[u].pb(v); g[v].pb(u);
	}
	int solve(int u, int d) { 
		tin[u] = low[u] = ++t;
		int ret = 0;
		forn(i,sz(g[u])) {
			int v = g[u][i];
			if(v == d) continue;
			if(tin[v] == 0) {
				int retv = solve(v,u);
				low[u] = min(low[u],low[v]);
				if(low[v] >  tin[u]) ret ^= (1+retv)^1;
				else ret ^= retv;
			}else low[u] = min(low[u], tin[v]);
		}
		forn(i,sz(g[u])) {
			int v = g[u][i];
			if(v != d && tin[u] <= tin[v]) ret ^= 1;
		}
		return ret;
	}
	int solve() {
		return root == -1? 0 : ans^solve(root,-1);
	}
};

int main () {
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int t; cin >> t;
	forn(tt,t) {
		int n; cin >> n;
		green_hackenbush gh(n);
		forn(i,n) {
			int g; cin >> g;
			if(g) gh.ground(i);
		}
		forn(i,n-1) {
			int u, v; cin >> u >> v; u--, v--;
			gh.add_edge(u,v);
		}
		cout << (gh.solve() != 0) << "\n";
	}
	
	#ifdef JP
		cerr << "Time elapsed: " <<  clock() * 1000 / CLOCKS_PER_SEC << " ms\n";
	#endif
}
