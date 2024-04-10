struct Edge { int u, v; };  // maybe add more data
struct SubtreeData {  // Define data for each subtree
  SubtreeData() {}    // just empty
  SubtreeData(int node) { /*implement this*/ }
  void merge(Edge* e, SubtreeData& s) { /*implement this*/ }
};
struct Reroot {
  int N; // # of nodes
  vector<SubtreeData> vresult, vs;//vresult[i], when root==i
  vector<Edge> ve;
  vector<vector<int>> g; // the tree as a bidirec graph
  Reroot(int n) : N(n), vresult(n), vs(n), ve(0), g(n) {}
  void addEdge(Edge e) {
    g[e.u].pb(sz(ve)); g[e.v].pb(sz(ve)); ve.pb(e);
  }
  void dfs1(int node, int p) {
    vs[node] = SubtreeData(node);
    forall(e, g[node]) {
      int nxt = node ^ ve[*e].u ^ ve[*e].v;
      if (nxt == p) continue;
      dfs1(nxt, node); vs[node].merge(&ve[*e], vs[nxt]);
    }
  }
  void dfs2(int node, int p, SubtreeData fromp) {
    vector<SubtreeData> vsuf(sz(g[node]) + 1);
    int pos = sz(g[node]);
    SubtreeData pref = vsuf[pos] = SubtreeData(node);
    vresult[node] = vs[node];
    dforall(e, g[node]) {  // dforall = forall in reverse
      pos--; vsuf[pos] = vsuf[pos + 1];
      int nxt = node ^ ve[*e].u ^ ve[*e].v;
      if (nxt == p) {
        pref.merge(&ve[*e], fromp);
        vresult[node].merge(&ve[*e], fromp);
        continue;
      }
      vsuf[pos].merge(&ve[*e], vs[nxt]);
    }
    assert(pos == 0);
    forall(e, g[node]) {
      pos++; int nxt = node ^ ve[*e].u ^ ve[*e].v;
      if (nxt == p) continue;
      SubtreeData aux = pref;
      aux.merge(NULL, vsuf[pos]); dfs2(nxt, node, aux);
      pref.merge(&ve[*e], vs[nxt]);
    }
  }
  void run() { dfs1(0, 0); dfs2(0, 0, SubtreeData()); }
};
