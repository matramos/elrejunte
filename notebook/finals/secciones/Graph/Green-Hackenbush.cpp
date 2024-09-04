/* A two-player game played on an undirected graph where
some nodes are connected to the ground. On each turn, a
player removes an edge. If this removal splits the graph
into two components, any component that is not connected 
to the ground is removed. A player loses the game if it's 
impossible to make a move. */
struct green_hackenbush {
  vector<vector<int>> g;
  vector<int> tin, low, gr;
  int t, root, ans;
  green_hackenbush(int n) {
    t = 0, root = -1, ans = 0;
    g.resize(n); gr.resize(n);
    tin.resize(n); low.resize(n);
  }
  // make u a node in the ground
  void ground(int u) { 
    gr[u] = 1; if(root == -1) root = u;
  }
  // call first ground() if u or v are in the ground
  void add_edge(int u, int v) { 
    if(gr[u]) u = root;
    if(gr[v]) v = root;
    if(u == v) { ans ^= 1; return; }
    g[u].pb(v); g[v].pb(u);
  }
  int solve(int u, int d) { 
    tin[u] = low[u] = ++t;
    int ret = 0;
    forn(i,sz(g[u])) {
      int v = g[u][i];
      if(v == d) continue;
      if(tin[v] == 0) {
        int retv = solve(v,u);
        low[u] = min(low[u],low[v]);
        if(low[v] >  tin[u]) ret ^= (1+retv)^1;
        else ret ^= retv;
      }else low[u] = min(low[u], tin[v]);
    }
    forn(i,sz(g[u])) {
      int v = g[u][i];
      if(v != d && tin[u] <= tin[v]) ret ^= 1;
    }
    return ret;
  }
  int solve() {
    return root == -1? 0 : ans^solve(root,-1);
  }
};