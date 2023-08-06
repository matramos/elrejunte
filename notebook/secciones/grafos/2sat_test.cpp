// https://codeforces.com/contest/776/problem/D
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
typedef pair<ll,int> ii;

struct Sat2 {
	//We have a vertex representing a variable and other for its
	//negation. Every edge stored in G represents an implication.
	vector<vector<int>> G;
	//idx[i]=index assigned in the dfs
	//lw[i]=lowest index(closer from the root) reachable from i
	//verdad[cmp[i]]=valor de la variable i
	int N, qidx, qcmp;
	vector<int> lw, idx, cmp, verdad;
	stack<int> q;
	Sat2(int n): G(2*n), N(n) {}
	int neg(int x) { return x >= N ? x-N : x+N; }
	void tjn(int v) {
		lw[v] = idx[v] = ++qidx;
		q.push(v), cmp[v] = -2;
		forall(it, G[v]) if(!idx[*it] || cmp[*it] == -2) {
			if(!idx[*it]) tjn(*it);
			lw[v] = min(lw[v], lw[*it]);
		}
		if(lw[v] == idx[v]) {
			int x;
			do { x = q.top(); q.pop(); cmp[x] = qcmp; } while(x != v);
			verdad[qcmp] = (cmp[neg(v)] < 0);
			qcmp++;
		}
	}
	bool satisf() { // O(N)
		idx = lw = verdad = vector<int>(2*N, 0);
		cmp = vector<int>(2*N, -1);
		qidx = qcmp = 0;
		forn(i, N){
			if(!idx[i]) tjn(i);
			if(!idx[neg(i)]) tjn(neg(i));
		}
		forn(i, N) if(cmp[i] == cmp[neg(i)]) return false;
		return true;
	}
	// a -> b
	void addimpl(int a, int b) { G[a].pb(b); G[neg(b)].pb(neg(a)); }
	void addor(int a, int b) { addimpl(neg(a), b); } // a | b = ~a -> b
	void addeq(int a, int b) { // a = b, a <-> b (iff)
		addimpl(a, b);
		addimpl(b, a);
	}
	void addxor(int a, int b) { addeq(a, neg(b)); } // a xor b
	void force(int x, bool val) { // force x to take val
		if(val) addimpl(neg(x), x);
		else addimpl(x, neg(x));
	}
	// At most 1 true in each vv[i]. You must call this before all
	// other methods and no more than 1 time, because N gets modified
	// here, doing so after any edge was added would break the graph
	void atmost1(vector<vector<int>> vv) {
		int extra = 0;
		forn(i,sz(vv)) extra += sz(vv[i]);
		int auxid = N;
		N += extra;
		G.rsz(2*N);
		forn(i,sz(vv)) forn(j,sz(vv[i])) {
			addimpl(auxid, neg(vv[i][j]));
			if(j) {
				addimpl(auxid, auxid-1);
				addimpl(vv[i][j], auxid-1);
			}
			auxid++;
		}
		assert(auxid == N);
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
	int n, m;
	cin >> n >> m;
	vector<int> v(n);
	vector<vector<int>> vv(n);
	forn(i,n) cin >> v[i];
	forn(i,m)
	{
		int k;
		cin >> k;
		forn(_,k)
		{
			int x;
			cin >> x;
			vv[x-1].pb(i);
		}
	}
	Sat2 sat(m);
	forn(i,n)
	{
		assert(sz(vv[i]) == 2);
		if(v[i]) sat.addeq(vv[i][0], vv[i][1]);
		else sat.addxor(vv[i][0], vv[i][1]);
	}
	if(sat.satisf()) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}
