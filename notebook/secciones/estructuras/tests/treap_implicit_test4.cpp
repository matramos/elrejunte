//Problem: https://codeforces.com/group/j1UosVRZar/contest/287404/problem/J
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
#ifdef ANARAP
	#define MAXN 2000
#else
	#define MAXN 200010
#endif
#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

// An array represented as a treap, where the "key" is the index.
// However, the key is not stored explicitly, but can be calculated as
// the sum of the sizes of the left child of the ancestors where the node
// is in the right subtree of it.
// (commented parts are specific to range sum queries and other problems)
// rng = random number generator, works better than rand in some cases
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef struct item* pitem;
struct item {
  int pr, cnt;
  ll val;
  bool rev;  // for reverse operation
  ll sum;   // for range query
  ll add;   // for lazy prop
  pitem l, r;
  pitem p;  // ptr to parent, for getRoot
  item(int val) : pr(rng()), cnt(1), val(val), rev(false), sum(val), add(0) {
    l = r = p = NULL;
  }
};
void push(pitem node) {
  if (node) {
    // for reverse operation
    if (node->rev) {
      swap(node->l, node->r);
      if (node->l) node->l->rev ^= true;
      if (node->r) node->r->rev ^= true;
      node->rev = false;
    }
    // for lazy prop
    if(node->add)
	{
		node->val += node->add; node->sum += node->cnt * node->add;
		node->val %= MOD;
		node->sum %= MOD;
		if(node->l)
		{
			node->l->add += node->add;
			node->l->add %= MOD;
		}
		if(node->r)
		{
			node->r->add += node->add;
			node->r->add %= MOD;
		}
		node->add = 0;
	}
  }
}
int cnt(pitem t) { return t ? t->cnt : 0; }
ll sum(pitem t) { return t ? push(t), t->sum : 0; }  // for range query
void upd_cnt(pitem t) {
  if (t) {
    t->cnt = cnt(t->l) + cnt(t->r) + 1;
    t->sum = (t->val+sum(t->l)+sum(t->r))%MOD;  // for range sum
    if (t->l) t->l->p = t;                    // for getRoot
    if (t->r) t->r->p = t;                    // for getRoot
    t->p = NULL;                              // for getRoot
  }
}
void split(pitem node, pitem& L, pitem& R, int sz) {  // sz: wanted size for L
  if (!node) {
    L = R = 0;
    return;
  }
  push(node);
  // If node's left child has at least sz nodes, go left
  if (sz <= cnt(node->l)) split(node->l, L, node->l, sz), R = node;
  // Else, go right changing wanted sz
  else split(node->r, node->r, R, sz - 1 - cnt(node->l)), L = node;
  upd_cnt(node);
}
void merge(pitem& result, pitem L, pitem R) {  // O(log)
  push(L), push(R);
  if (!L || !R) result = L ? L : R;
  else if (L->pr > R->pr) merge(L->r, L->r, R), result = L;
  else merge(R->l, L, R->l), result = R;
  upd_cnt(result);
}
void insert(pitem& node, pitem x, int pos) {  // 0-index O(log)
  pitem l, r;
  split(node, l, r, pos);
  merge(l, l, x);
  merge(node, l, r);
}
void erase(pitem& node, int pos) {  // 0-index O(log)
  if (!node) return;
  push(node);
  if (pos == cnt(node->l)) merge(node, node->l, node->r);
  else if (pos < cnt(node->l)) erase(node->l, pos);
  else erase(node->r, pos - 1 - cnt(node->l));
  upd_cnt(node);
}
// reverse operation
void reverse(pitem& node, int L, int R) {  //[L, R) O(log)
  pitem t1, t2, t3;
  split(node, t1, t2, L);
  split(t2, t2, t3, R - L);
  t2->rev ^= true;
  merge(node, t1, t2);
  merge(node, node, t3);
}
// lazy add
void add(pitem& node, int L, int R, int x) {  //[L, R) O(log)
  pitem t1, t2, t3;
  split(node, t1, t2, L);
  split(t2, t2, t3, R - L);
  t2->add += x;
  t2->add %= MOD;
  merge(node, t1, t2);
  merge(node, node, t3);
}
// range query get
ll get(pitem& node, int L, int R) {  //[L, R) O(log)
  pitem t1, t2, t3;
  split(node, t1, t2, L);
  split(t2, t2, t3, R - L);
  push(t2);
  ll ret = t2->sum;
  merge(node, t1, t2);
  merge(node, node, t3);
  return ret;
}
void push_all(pitem t) {  // for getRoot
  if (t->p) push_all(t->p);
  push(t);
}
pitem getRoot(pitem t, int& pos) {  // get root and position for node t
  push_all(t);
  pos = cnt(t->l);
  while (t->p) {
    pitem p = t->p;
    if (t == p->r) pos += cnt(p->l) + 1;
    t = p;
  }
  return t;
}
void output(pitem t) {  // useful for debugging
  if (!t) return;
  push(t);
  output(t->l);
  cout << ' ' << t->val;
  output(t->r);
}

vector<int> g[MAXN];
pitem nodes[2*MAXN], L[MAXN], R[MAXN];
int pos, v[MAXN];

void dfs(int node)
{
	L[node] = nodes[pos] = new item(v[node]);
	pos++;
	forall(it, g[node]) dfs(*it);
	R[node] = nodes[pos] = new item(v[node]);
	pos++;
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
	int n,q;
	cin >> n >> q;
	forn(i,n) cin >> v[i];
	forn(i,n-1)
	{
		int p;
		cin >> p;
		g[p-1].pb(i+1);
	}
	dfs(0);
	pitem root = NULL;
	forn(i, 2*n) insert(root, nodes[i], i);
	forn(_,q)
	{
		int t;
		cin >> t;
		if(t == 1)
		{
			int a,b;
			cin >> a >> b;
			a--;b--;
			int l, r;
			getRoot(L[a], l);
			getRoot(R[a], r);
			pitem noL, noR, subtree;
			split(root, noL, subtree, l);
			split(subtree, subtree, noR, r-l+1);
			merge(root, noL, noR);
			int pos;
			getRoot(L[b], pos);
			split(root, noL, noR, pos+1);
			merge(root, noL, subtree);
			merge(root, root, noR);
		}
		else if(t == 2)
		{
			int s, x;
			cin >> s >> x;
			x--;
			int l, r;
			getRoot(L[x], l);
			getRoot(R[x], r);
			add(root, l, r+1, s);
		}
		else
		{
			int x;
			cin >> x;
			x--;
			int l, r;
			getRoot(L[x], l);
			getRoot(R[x], r);
			cout << get(root, l, r+1)*500000004%MOD << '\n';
		}
	}
    return 0;
}
