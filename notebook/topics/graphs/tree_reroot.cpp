struct Edge {
  int u, v;  // maybe add more data, depending on the problem
};
// USAGE:
// 1- define all the logic in SubtreeData
// 2- create a reroot and add all the edges
// 3- call Reroot.run()
struct SubtreeData {
  // Define here what data you need for each subtree
  SubtreeData() {}  // just empty
  SubtreeData(int node) {
    // Initialize the data here as if this new subtree
    // has size 1, and its only node is 'node'
  }
  void merge(Edge* e, SubtreeData& s) {
    // Modify this subtree's data to reflect that 's' is being
    // merged into 'this' through the edge 'e'.
    // When e == NULL, then no edge is present, but then, 'this'
    // and 's' have THE SAME ROOT (be CAREFUL with this).
    // These 2 subtrees don't have any other shared nodes nor edges.
  }
};
struct Reroot {
  int N;  // # of nodes
  // vresult[i] = SubtreeData for the tree where i is the root
  // this should be what you need as result
  vector<SubtreeData> vresult, vs;
  vector<Edge> ve;
  vector<vector<int>> g;  // the tree as a bidirectional graph
  Reroot(int n) : N(n), vresult(n), vs(n), ve(0), g(n) {}
  void addEdge(Edge e) {  // will be added in both ways
    g[e.u].pb(sz(ve));
    g[e.v].pb(sz(ve));
    ve.pb(e);
  }
  void dfs1(int node, int p) {
    vs[node] = SubtreeData(node);
    forall(e, g[node]) {
      int nxt = node ^ ve[*e].u ^ ve[*e].v;
      if (nxt == p) continue;
      dfs1(nxt, node);
      vs[node].merge(&ve[*e], vs[nxt]);
    }
  }
  void dfs2(int node, int p, SubtreeData fromp) {
    vector<SubtreeData> vsuf(sz(g[node]) + 1);
    int pos = sz(g[node]);
    SubtreeData pref = vsuf[pos] = SubtreeData(node);
    vresult[node] = vs[node];
    dforall(e, g[node]) {  // dforall = forall in reverse
      pos--;
      vsuf[pos] = vsuf[pos + 1];
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
      pos++;
      int nxt = node ^ ve[*e].u ^ ve[*e].v;
      if (nxt == p) continue;
      SubtreeData aux = pref;
      aux.merge(NULL, vsuf[pos]);
      dfs2(nxt, node, aux);
      pref.merge(&ve[*e], vs[nxt]);
    }
  }
  void run() {
    dfs1(0, 0);
    dfs2(0, 0, SubtreeData());
  }
};
