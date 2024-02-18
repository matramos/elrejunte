// https://codeforces.com/contest/613/problem/D
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
 
#define lg(x) (31-__builtin_clz(x))//=floor(log2(x))
// Usage: 1) Create 2) Add edges 3) Call build 4) Use
struct LCA {
	int N, LOGN, ROOT;
	//vp[node][k] holds the 2^k ancestor of node
	//L[v] holds the level of v
	vector<int> L;
	vector<vector<int>> vp, G;
	LCA(int n, int root): N(n), LOGN(lg(n)+1), ROOT(root), L(n), G(n) {
		// Here you may want to replace the default from root to other
		// value, like maybe -1.
		vp = vector<vector<int>>(n, vector<int>(LOGN, root));
	}
	void addEdge(int a, int b) { G[a].pb(b); G[b].pb(a); }
	void dfs(int node, int p, int lvl) {
		vp[node][0] = p; L[node] = lvl;
		forall(it, G[node]) if(*it != p) dfs(*it, node, lvl+1);
	}
	void build() {
		// Here you may also want to change the 2nd param to -1
		dfs(ROOT, ROOT, 0);
		forn(k, LOGN-1) forn(i, N) vp[i][k+1] = vp[vp[i][k]][k];
	}
	int climb(int a, int d) { //O(lgn)
		if(!d) return a;
		dforn(i, lg(L[a])+1) if(1<<i <= d) a = vp[a][i], d -= 1<<i;
		return a;
	}
	int lca(int a, int b){ //O(lgn)
		if(L[a] < L[b]) swap(a, b);
		a = climb(a, L[a]-L[b]);
		if(a==b) return a;
		dforn(i, lg(L[a])+1) if(vp[a][i] != vp[b][i])
			a = vp[a][i], b = vp[b][i];
		return vp[a][0];
	}
	int dist(int a, int b) { //returns distance between nodes
		return L[a] + L[b] - 2*L[lca(a, b)];
	}
};

// Usage: (VT = VirtualTree)
// 1- Build the LCA and use it for creating 1 VT instance
// 2- Call updateVT every time you want
// 3- Between calls of updateVT you probably want to use the tree, imp
// and VTroot variables from this struct to solve your problem
struct VirtualTree {
	// n = #nodes full tree
	// curt used for computing tin and tout
	int n, curt;
	LCA* lca;
	vector<int> tin, tout;
	vector<vector<ii>> tree; // {node, dist}
	// imp[i] = true iff i was part of 'newv' from last time that
	// updateVT was called (note that LCAs are not imp)
	vector<bool> imp;
	void dfs(int node, int p) {
		tin[node] = curt++;
		forall(it,lca->G[node]) if(*it != p) dfs(*it, node);
		tout[node] = curt++;
	}
	VirtualTree(LCA* l) { // must call l.build() before
		lca = l; n = sz(l->G); lca = l; curt = 0;
		tin.rsz(n); tout.rsz(n); tree.rsz(n); imp.rsz(n);
		dfs(l->ROOT,l->ROOT);
	}
	//bool cmp(int& a, int& b) { return tin[a] < tin[b]; }
	bool isAncestor(int a, int b) {
		return tin[a] < tin[b] && tout[a] > tout[b];
	}
	int VTroot = -1; // root of the current VT
	vector<int> v; // list of nodes of current VT (includes LCAs)
	void updateVT(vector<int>& newv) { // O(sz(v)*log)
		auto cmp = [this](int a, int b) { return tin[a] < tin[b]; };
		forn(i,sz(v)) tree[v[i]].clear(), imp[v[i]] = false;
		v = newv;
		sort(v.begin(), v.end(), cmp);
		set<int> s;
		forn(i,sz(v)) s.insert(v[i]), imp[v[i]] = true;
		forn(i,sz(v)-1) s.insert(lca->lca(v[i], v[i+1]));
		v.clear();
		forall(it,s) v.pb(*it);
		sort(v.begin(), v.end(), cmp);
		stack<int> st;
		forn(i,sz(v)) {
			while(!st.empty() && !isAncestor(st.top(), v[i])) st.pop();
			assert(i == 0 || !st.empty());
			if(!st.empty()) {
				tree[st.top()].pb(mp(v[i], lca->dist(st.top(), v[i])));
			}
			st.push(v[i]);
		}
		VTroot = v[0];
	}
};
 
const int INF = 1000100;
 
ii solve(int node, VirtualTree& vt)
{
	int ret = 0, cnt = vt.imp[node];
	forall(it,vt.tree[node])
	{
		if(vt.imp[node] && vt.imp[it->fst] && it->snd == 1) return mp(INF, 0);
		ii aux = solve(it->fst, vt);
		ret = min(INF, ret+aux.fst);
		assert(aux.snd == 0 || aux.snd == 1);
		if(aux.snd == 1)
		{
			if(vt.imp[node]) ret = min(INF, ret+1);
			else cnt++;
		}
	}
	if(cnt > 1) ret = min(INF, ret+1), cnt = 0;
	return mp(ret, cnt);
}
 
int solve(vector<int>& v, VirtualTree& vt)
{
	vt.updateVT(v);
	int ans = solve(vt.VTroot, vt).fst;
	if(ans == INF) ans = -1;
	assert(ans < INF);
	return ans;
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
	int n;
	cin >> n;
	LCA lca(n,0);
	forn(i,n-1) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		lca.addEdge(a,b);
	}
	lca.build();
	VirtualTree vt(&lca);
	int q;
	cin >> q;
	forn(_,q)
	{
		int k;
		cin >> k;
		vector<int> v(k);
		forn(i,k) cin >> v[i];
		forn(i,k) v[i]--;
		cout << solve(v, vt) << '\n';
	}
	return 0;
}
