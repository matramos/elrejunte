//Problem: https://www.spoj.com/problems/QTREE/
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

#define MAXN 10001

typedef ll tipo;
const tipo neutro = 0;
tipo oper(const tipo& a, const tipo& b) { return max(a,b); }
struct ST {
	int sz;
	vector<tipo> t;
	ST(int n) {
		sz = 1 << (32 - __builtin_clz(n));
		t = vector<tipo>(2*sz, neutro);
	}
	tipo &operator[](int p) { return t[sz+p]; }
	void updall() { dforn(i, sz) t[i] = oper(t[2*i], t[2*i+1]); }
	tipo get(int i, int j) { return get(i, j, 1, 0, sz); }
	tipo get(int i, int j, int n, int a, int b) { //O(log n), [i, j)
		if(j <= a || b <= i) return neutro;
		if(i <= a && b <= j) return t[n]; // n = node of range [a,b)
		int c = (a+b)/2;
		return oper(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	void set(int p, tipo val) { //O(log n)
		p += sz;
		while(p>0 && t[p] != val) {
			t[p] = val;
			p /= 2;
			val = oper(t[p*2], t[p*2+1]);
		}
	}
}; //Use: definir oper tipo neutro,
//cin >> n; ST st(n); forn(i, n) cin >> st[i]; st.updall();

// Usage: 1. HLD(# nodes) 2. add tree edges 3. build() 4. use it
struct HLD {
  vector<int> w, p, dep;  // weight,father,depth
  vector<vector<int>> g;
  HLD(int n) : w(n), p(n), dep(n), g(n), pos(n), head(n) {}
  void addEdge(int a, int b) { g[a].pb(b), g[b].pb(a); }
  void build() { p[0] = -1, dep[0] = 0, dfs1(0), curpos = 0, hld(0, -1); }
  void dfs1(int x) {
    w[x] = 1;
    for (int y : g[x]) if (y != p[x]) {
        p[y] = x, dep[y] = dep[x] + 1, dfs1(y);
        w[x] += w[y];
      }
  }
  int curpos;
  vector<int> pos, head;
  void hld(int x, int c) {
    if (c < 0) c = x;
    pos[x] = curpos++, head[x] = c;
    int mx = -1;
    for (int y : g[x]) if (y != p[x] && (mx < 0 || w[mx] < w[y])) mx = y;
    if (mx >= 0) hld(mx, c);
    for (int y : g[x]) if (y != mx && y != p[x]) hld(y, -1);
  }
  // Here ST is segtree static/dynamic/lazy or other DS according to problem
  tipo query(int x, int y, ST& st) {  // ST tipo
    tipo r = neutro;
    while (head[x] != head[y]) {
      if (dep[head[x]] > dep[head[y]]) swap(x, y);
      r = oper(r, st.get(pos[head[y]], pos[y] + 1));  // ST oper
      y = p[head[y]];
    }
    if (dep[x] > dep[y]) swap(x, y);          // now x is lca
    r = oper(r, st.get(pos[x]+1, pos[y] + 1));  // ST oper
    return r;
  }
};
// for point updates: st.set(pos[x], v) (x = node, v = new value)
// for lazy range updates: something similar to the query method
// for queries on edges: - assign values of edges to "child" node
//                       - change pos[x] to pos[x]+1 in query (line 34)


ST st(1);
HLD hld(1);
vector<int> edgeIdToNode;
map<ii,int> edgeId;
vector<vector<ii>> g;

void buildSt(int node, int prev)
{
	forall(it,g[node]) if(it->fst != prev)
	{
		edgeIdToNode[edgeId[mp(node, it->fst)]] = it->fst;
		st[hld.pos[it->fst]] = it->snd;
		buildSt(it->fst, node);
	}
}

int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	forn(T,t)
	{
		int n;
		cin >> n;
		hld = HLD(n);
		g.rsz(n);
		forn(i,n-1)
		{
			int a,b,c;
			cin >> a >> b >> c;
			a--;b--;
			edgeId[mp(a,b)] = i;
			edgeId[mp(b,a)] = i;
			g[a].pb(mp(b,c));
			g[b].pb(mp(a,c));
			hld.addEdge(a,b);
		}
		hld.build();
		st = ST(n);
		edgeIdToNode = vector<int>(n-1);
		buildSt(0,0);
		st.updall();
		string s;
		while(cin >> s)
		{
			if(s == "DONE") break;
			if(s == "CHANGE")
			{
				int id,x;
				cin >> id >> x;
				id--;
				st.set(hld.pos[edgeIdToNode[id]], x);
			}
			else
			{
				int a,b;
				cin >> a >> b;
				a--;b--;
				cout << hld.query(a,b,st) << '\n';
			}
		}
		edgeId.clear();
		edgeIdToNode.clear();
		g.clear();
	}
	return 0;
}
