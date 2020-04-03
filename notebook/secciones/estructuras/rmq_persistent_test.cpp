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
#define MAXN 100010

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

typedef int tipo;
tipo oper(const tipo &a, const tipo &b){
    return a+b;
}
struct node{
	tipo v; node *l, *r;
	node(tipo v) : v(v), l(NULL), r(NULL) {}
    node(node *l, node *r) : l(l), r(r) {
        if(!l) v = r->v;
        else if(!r) v = l->v;
        else v = oper(l->v, r->v);
    }
};
node *build(int tl, int tr) {//construye el ST a partir de un arreglo
	if(tl+1 == tr) return new node(0);
	int tm = (tl+tr)>>1;
	return new node(build(tl, tm), build(tm, tr));
}
node *update(int pos, node *t, int tl, int tr) {
	if(tl+1 == tr) return new node(t->v+1);
	int tm = (tl+tr)>>1;
	if(pos < tm) return new node(update(pos, t->l, tl, tm), t->r);
	else return new node(t->l, update(pos, t->r, tm, tr));
}
tipo get(int l, int r, node *t, int tl, int tr) {
    if(l==tl && tr==r) return t->v;
	int tm = (tl+tr)>>1;
    if(r <= tm) return get(l, r, t->l, tl, tm);
    else if(l >= tm) return get(l, r, t->r, tm, tr);
	return oper(get(l, tm, t->l, tl, tm), get(tm, r, t->r, tm, tr));
}
tipo kth(node *L, node *R, int tl, int tr, int k) {
	if(L == NULL || R == NULL) return -1;
	if(R->v - L->v < k) return -1;
	if(tl+1 == tr) return tl;
	int tm = (tl+tr)/2;
	int ret = kth(L->l, R->l, tl, tm, k);
	if(ret == -1)
	{
		assert(R->l != NULL && L->l != NULL);
		ret = kth(L->r, R->r, tm, tr, k-(R->l->v - L->l->v));
	}
	return ret;
}

int main()
{
	#ifdef REJUNTE
	freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m;
	node *roots[MAXN];
	map<int,int> xToN, nToX;
	cin >> n >> m;
	vector<int> v(n);
	set<int> s;
	forn(i,n)
	{
		cin >> v[i];
		s.insert(v[i]);
	}
	int aux = 0;
	forall(it,s)
	{
		xToN[*it] = aux;
		nToX[aux] = *it;
		aux++;
	}
	roots[0] = build(0, n);
	forn(i,n)
	{
		int pos = xToN[v[i]];
		roots[i+1] = update(pos, roots[i], 0, n);
	}
	forn(i,m)
	{
		int a,b,k;
		cin >> a >> b >> k;
		cout << nToX[kth(roots[a-1], roots[b], 0, n, k)] << '\n';
	}
	return 0;
}