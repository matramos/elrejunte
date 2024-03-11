// https://codeforces.com/gym/104252/problem/F
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

struct HopcroftKarp {  // [0,n)->[0,m) (ids independent in each side)
  int n, m;
  vector<vector<int>> g;
  vector<int> mt, mt2, ds;
  HopcroftKarp(int nn, int mm) : n(nn), m(mm), g(n) {}
  void add(int a, int b) { g[a].pb(b); }
  bool bfs() {
    queue<int> q;
    ds = vector<int>(n, -1);
    forn(i, n) if (mt2[i] < 0) ds[i] = 0, q.push(i);
    bool r = false;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (int y : g[x]) {
        if (mt[y] >= 0 && ds[mt[y]] < 0) {
          ds[mt[y]] = ds[x] + 1, q.push(mt[y]);
        } else if (mt[y] < 0) r = true;
      }
    }
    return r;
  }
  bool dfs(int x) {
    for (int y : g[x]) {
      if (mt[y] < 0 || ds[mt[y]] == ds[x] + 1 && dfs(mt[y])) {
        mt[y] = x, mt2[x] = y;
        return true;
      }
    }
    ds[x] = 1 << 30;
    return false;
  }
  int mm() {  // O(sqrt(V)*E)
    int r = 0;
    mt = vector<int>(m, -1);
    mt2 = vector<int>(n, -1);
    while (bfs()) forn(i, n) if (mt2[i] < 0) r += dfs(i);
    return r;
  }
};


const int MAXN = 100;

int dfs(vector<int> g[MAXN], vector<int>& vsz, int node, int p)
{
	vsz[node] = 1;
	forall(it, g[node]) if(*it != p) vsz[node] += dfs(g, vsz, *it, node);
	return vsz[node];
}

vector<int> g1[MAXN], g2[MAXN];
vector<int> vsz1, vsz2;

bool solve(int n1, int p1, int n2, int p2)
{
	int n = sz(g1[n1]), m = sz(g2[n2]);
	bool hasp = n1 != p1;
	if(m - hasp <= 0) return true; 
	if(vsz1[n1] < vsz2[n2] || n < m) return false;
	HopcroftKarp hk(n, m);
	forn(i,n) if(g1[n1][i] != p1) forn(j,m) if(g2[n2][j] != p2) 
	{
		if(solve(g1[n1][i], n1, g2[n2][j], n2)) hk.add(i, j);
	}
	return hk.mm() == m - hasp;
}

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
	int n1, n2;
	cin >> n1;
	forn(_,n1-1)
	{
		int a,b;
		cin >> a >> b;
		a--;b--;
		g1[a].pb(b);
		g1[b].pb(a);
	}
	cin >> n2;
	forn(_,n2-1)
	{
		int a,b;
		cin >> a >> b;
		a--;b--;
		g2[a].pb(b);
		g2[b].pb(a);
	}
	if(n1 < n2)
	{
		cout << "N\n";
		return 0;
	}
	vsz1.rsz(n1);
	vsz2.rsz(n2);
	dfs(g2, vsz2, 0, 0);
	forn(i,n1)
	{
		dfs(g1, vsz1, i, i);
		if(solve(i, i, 0, 0))
		{
			cout << "Y\n";
			return 0;
		}
	}
	cout << "N\n";
	return 0;
}
