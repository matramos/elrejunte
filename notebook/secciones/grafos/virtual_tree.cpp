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
