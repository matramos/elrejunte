// https://codeforces.com/problemset/problem/427/C
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

struct Kosaraju {
	vector<vector<int>> G, gt;
	//nodos 0...N-1 ; componentes 0...cantcomp-1
	int N,cantcomp;
	vector<int> comp, used;
	stack<int> pila;
	Kosaraju(int n): G(n), gt(n), N(n), comp(n) {}
	void addEdge(int a, int b){ G[a].pb(b); gt[b].pb(a); }
	void dfs1(int nodo) {
		used[nodo]=1;
		forall(it,G[nodo]) if(!used[*it]) dfs1(*it);
		pila.push(nodo);
	}
	void dfs2(int nodo) {
		used[nodo]=2;
		comp[nodo]=cantcomp-1;
		forall(it,gt[nodo]) if(used[*it]!=2) dfs2(*it);
	}
	void run() {
		cantcomp=0;
		used = vector<int>(N, 0);
		forn(i,N) if(!used[i]) dfs1(i);
		while(!pila.empty()) {
			if(used[pila.top()]!=2) {
				cantcomp++;
				dfs2(pila.top());
			}
			pila.pop();
		}
	}
};

const ll MOD = 1000000007;

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
	int n;
	cin >> n;
	vector<int> v(n);
	forn(i,n) cin >> v[i];
	int m;
	cin >> m;
	Kosaraju ks(n);
	forn(_,m)
	{
		int a,b;
		cin >> a >> b;
		a--;b--;
		ks.addEdge(a,b);
	}
	ks.run();
	vector<int> minOfComp(ks.cantcomp, 2e9), cntOfComp(ks.cantcomp, 0);
	forn(i,n) minOfComp[ks.comp[i]] = min(minOfComp[ks.comp[i]], v[i]);
	forn(i,n) if(v[i] == minOfComp[ks.comp[i]]) cntOfComp[ks.comp[i]]++;
	ll ans = 0, cnt = 1;
	forn(i,ks.cantcomp) ans += minOfComp[i];
	forn(i,ks.cantcomp) cnt = cnt * cntOfComp[i]%MOD;
	cout << ans << ' ' << cnt << '\n';
	return 0;
}
