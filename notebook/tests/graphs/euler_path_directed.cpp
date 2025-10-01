// https://cses.fi/problemset/task/1693
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

// Be careful with nodes with degree 0 when solving your problem, the
// comments below assume that there are no nodes with degree 0.
//
// Euler [path/cycle] exists in a bidirectional graph iff the graph is
// connected and at most [2/0] nodes have odd degree. The path must
// start from an odd degree vertex when there are 2.
//
// Euler [path/cycle] exists in a directed graph iff the graph is
// [connected when making edges bidirectional / a single SCC], and
// at most [1/0] node have indg - outdg = 1, at most [1/0] node have
// outdg - indg = 1, all the other nodes have indg = outdg. The path
// must start from the node with outdg - indg = 1, when there is one.
//
// Directed version (uncomment commented code for undirected)
struct edge {
  int y;
  // list<edge>::iterator rev;
  edge(int yy) : y(yy) {}
};
struct EulerPath {
  vector<list<edge>> g;
  EulerPath(int n) : g(n) {}
  void addEdge(int a, int b) {
    g[a].push_front(edge(b));
    // auto ia = g[a].begin();
    // g[b].push_front(edge(a));
    // auto ib = g[b].begin();
    // ia->rev=ib, ib->rev=ia;
  }
  vector<int> p;
  void go(int x) {
    while (sz(g[x])) {
      int y = g[x].front().y;
      // g[y].erase(g[x].front().rev);
      g[x].pop_front();
      go(y);
    }
    p.push_back(x);
  }
  vector<int> getPath(int x) {  // get a path that starts from x
    // you must check that a path exists from x before calling get_path!
    p.clear(), go(x);
    reverse(p.begin(), p.end());
    return p;
  }
};


vector<vector<int>> g;
vector<bool> used;
int dg;

void dfs(int node) {
	dg += sz(g[node]);
	used[node] = true;
	forall(it,g[node]) if(!used[*it]) dfs(*it);
}

int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m;
	cin >> n >> m;
	g.rsz(n);
	EulerPath euler(n);
	vector<int> indg(n), outdg(n);
	forn(i,m)
	{
		int a,b;
		cin >> a >> b;
		a--,b--;
		g[a].pb(b);
		g[b].pb(a);
		euler.addEdge(a,b);
		indg[b]++;
		outdg[a]++;
	}
	used.rsz(n);
	dfs(0);
	assert(dg <= 2*m);
	bool ok = dg == 2*m && outdg[0]-indg[0] == 1 && indg[n-1]-outdg[n-1] == 1;
	forr(i,1,n-1) if(indg[i] != outdg[i]) ok = false;
	if(!ok) cout << "IMPOSSIBLE\n";
	else {
		vector<int> vans = euler.getPath(0);
		forn(i,sz(vans)) {
			if(i) cout << ' ';
			cout << vans[i]+1;
		}
		cout << '\n';
	}
	return 0;
}
