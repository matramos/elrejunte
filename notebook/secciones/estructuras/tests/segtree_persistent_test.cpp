//Problem: https://www.spoj.com/problems/MKTHNUM/
#include <bits/stdc++.h>
#define sqr(a) ((a)*(a))
#define rsz resize
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second
 
using namespace std;
 
typedef long long ll;
typedef pair<int,int> ii;

typedef int tipo;
const tipo neutro = 0;
tipo oper(const tipo& a, const tipo& b) { return a + b; }
struct ST {
  int n;
  vector<tipo> st;
  vector<int> L, R;
  ST(int nn) : n(nn), st(1, neutro), L(1, 0), R(1, 0) {}
  int new_node(tipo v, int l = 0, int r = 0) {
    int id = sz(st);
    st.pb(v), L.pb(l), R.pb(r);
    return id;
  }
  int init(vector<tipo>& v, int l, int r) {
    if (l + 1 == r) return new_node(v[l]);
    int m = (l + r) / 2, a = init(v, l, m), b = init(v, m, r);
    return new_node(oper(st[a], st[b]), a, b);
  }
  int update(int cur, int pos, tipo val, int l, int r) {
    int id = new_node(st[cur], L[cur], R[cur]);
    if (l + 1 == r) {
      st[id] = val;
      return id;
    }
    int m = (l + r) / 2, ASD;  // MUST USE THE ASD!!!
    if (pos < m) ASD = update(L[id], pos, val, l, m), L[id] = ASD;
    else ASD = update(R[id], pos, val, m, r), R[id] = ASD;
    st[id] = oper(st[L[id]], st[R[id]]);
    return id;
  }
  tipo get(int cur, int from, int to, int l, int r) {
    if (to <= l || r <= from) return neutro;
    if (from <= l && r <= to) return st[cur];
    int m = (l + r) / 2;
    return oper(get(L[cur], from, to, l, m), get(R[cur], from, to, m, r));
  }
  int init(vector<tipo>& v) { return init(v, 0, n); }
  int update(int root, int pos, tipo val) {
    return update(root, pos, val, 0, n);
  }
  tipo get(int root, int from, int to) { return get(root, from, to, 0, n); }
};  // usage: ST st(n); root = st.init(v) (or root = 0);
// new_root = st.update(root,i,x); st.get(root,l,r);
 
int kth(ST& st, int xl, int xr, int k, int l, int r)
{
	if(l+1 == r) return l;
	int aux = st.st[st.L[xr]] - st.st[st.L[xl]];
	int m = (l+r)/2;
	if(aux >= k) return kth(st, st.L[xl], st.L[xr], k, l, m);
	return kth(st, st.R[xl], st.R[xr], k-aux, m, r);
}
 
int main()
{
	#ifdef ANARAP
		freopen("input.in","r",stdin);
		//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m;
	cin >> n >> m;
	vector<int> v(n);
	forn(i,n) cin >> v[i];
	map<int,int> comp;
	forall(it,v) comp[*it] = -1;
	int aux = 0;
	forall(it,comp) it->snd = aux++;
	map<int,int> decomp;
	forall(it,comp) decomp[it->snd] = it->fst;
	ST st(aux);
	vector<int> roots;
	roots.reserve(n+1);
	roots.pb(0);
	forn(i,n) roots.pb(st.update(roots.back(), comp[v[i]], st.get(roots.back(), comp[v[i]], comp[v[i]]+1)+1));
	forn(_,m)
	{
		int l,r,k;
		cin >> l >> r >> k;
		l--;
		cout << decomp[kth(st, roots[l], roots[r], k, 0, st.n)] << '\n';
	}
	return 0;
}
