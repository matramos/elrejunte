// problem: https://codeforces.com/contest/1887/problem/D
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

typedef ii datain;     // data that goes into the DS
typedef int query;     // info related to a query
typedef bool dataout;  // data that results from a query
struct DS {
  set<datain> s;  // replace set with what's needed for the problem
  void insert(const datain& x) {
    // modify this method according to problem
    // the example below is "disjoint intervals" (i.e. union of ranges)
    datain xx = x;  // copy to avoid changing original
    if (xx.fst >= xx.snd) return;
    auto at = s.lower_bound(xx);
    auto it = at;
    if (at != s.begin() && (--at)->snd >= xx.fst) xx.fst = at->fst, --it;
    for (; it != s.end() && it->fst <= xx.snd; s.erase(it++))
      xx.snd = max(xx.snd, it->snd);
    s.insert(xx);
  }
  void get(const query& q, dataout& ans) {
    // modify this method according to problem
    // the example below is "is there any range covering q?"
    set<datain>::iterator ite = s.ub(mp(q + 1, 0));
    if (ite != s.begin() && prev(ite)->snd > q) ans = true;
  }
};
struct MST {
  int sz;
  vector<DS> t;
  MST(int n) {
    sz = 1 << (32 - __builtin_clz(n));
    t = vector<DS>(2 * sz);
  }
  void insert(int i, int j, datain& x) { insert(i, j, x, 1, 0, sz); }
  void insert(int i, int j, datain& x, int n, int a, int b) {
    if (j <= a || b <= i) return;
    if (i <= a && b <= j) {
      t[n].insert(x);
      return;
    }
    // needed when want to update ranges that intersec with [i,j)
    // usually only needed on range-query + point-update problem
    // t[n].insert(x);
    int c = (a + b) / 2;
    insert(i, j, x, 2 * n, a, c);
    insert(i, j, x, 2 * n + 1, c, b);
  }
  void get(int i, int j, query& q, dataout& ans) {
    return get(i, j, q, ans, 1, 0, sz);
  }
  void get(int i, int j, query& q, dataout& ans, int n, int a, int b) {
    if (j <= a || b <= i) return;
    if (i <= a && b <= j) {
      t[n].get(q, ans);
      return;
    }
    // needed when want to get from ranges that intersec with [i,j)
    // usually only needed on point-query + range-update problem
    t[n].get(q, ans);
    int c = (a + b) / 2;
    get(i, j, q, ans, 2 * n, a, c);
    get(i, j, q, ans, 2 * n + 1, c, b);
  }
};  // Use: 1- definir todo lo necesario en DS, 2- usar


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
	vector<vector<int>> vv(n);
	forn(i,n)
	{
		cin >> v[i];
		v[i]--;
		vv[v[i]].pb(i);
	}
	MST st(n);
	set<int> s0, s1;
	forr(i,-1,n+1) s0.insert(i);
	s1.insert(n);
	forn(i,n)
	{
		forall(it,vv[i]) s0.erase(*it), s1.insert(*it);
		forall(it,vv[i])
		{
			set<int>::iterator ite = s0.lb(*it);
			if(*ite != n)
			{
				datain aux = {*ite, *s1.lb(*ite)};
				st.insert(1+*prev(ite), *ite, aux);
			}
		}
	}
	int q;
	cin >> q;
	forn(_,q)
	{
		int l,r;
		cin >> l >> r;
		l--;r--;
		dataout ans = false;
		st.get(l,l+1,r,ans);
		if(ans) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
}
