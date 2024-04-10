struct Bicon {
  vector<vector<int>> G;
  struct edge { int u, v, comp; bool bridge; };
  vector<edge> ve;
  void addEdge(int u, int v) {
    G[u].pb(sz(ve)), G[v].pb(sz(ve)); ve.pb({u,v,-1,false});
  }
  // d[i] = dfs id, b[i] = lowest id reachable from i
  // art[i]>0 iff i is an articulation point
  vector<int> d, b, art;
  int n, t, nbc, nart; // nbc = # of bicon comps
  Bicon(int nn) {
    n = nn; t = nbc = nart = 0; b = d = vector<int>(n, -1);
    art = vector<int>(n, 0); G = vector<vector<int>>(n);
    ve.clear();
  }
  stack<int> st;
  void dfs(int u, int pe) {  // O(n + m)
    b[u] = d[u] = t++;
    forall(eid, G[u]) if (*eid != pe) {
      int v = ve[*eid].u ^ ve[*eid].v ^ u;
      if (d[v] == -1) {
        st.push(*eid); dfs(v, *eid);
        if (b[v] > d[u]) ve[*eid].bridge = true;  // bridge
        if (b[v] >= d[u]) {                       // art
          if (art[u]++ == 0) nart++;
          int last;  // start biconnected
          do { last=st.top(); st.pop(); ve[last].comp=nbc; }
          while (last != *eid);
          nbc++;  // end biconnected
        }
        b[u] = min(b[u], b[v]);
      } else if (d[v] < d[u]) {  // back edge
        st.push(*eid); b[u] = min(b[u], d[v]);
      }
    }
  }
  void run(){forn(i,n) if(d[i] == -1) art[i]--, dfs(i, -1);}
  vector<set<int>> bctree; // block-cut tree, set to dedup
  vector<int> artid; //art nodes to tree node (-1 for !arts)
  void buildBlockCutTree() {  // call run first!!
    // node id: [0, nbc) -> bc, [nbc, nbc+nart) -> art
    int ntree = nbc + nart, auxid = nbc;
    bctree = vector<set<int>>(ntree);
    artid = vector<int>(n, -1);
    forn(i, n) if (art[i] > 0) {
      forall(eid, G[i]) {  // edges always bc <-> art
        // may want to add more data in bctree edges
        bctree[auxid].insert(ve[*eid].comp);
        bctree[ve[*eid].comp].insert(auxid);
      }
      artid[i] = auxid++;
    }
  }
  int getTreeIdForGraphNode(int u) {
    if (artid[u] != -1) return artid[u];
    if (!G[u].empty()) return ve[G[u][0]].comp;
    return -1;  // for nodes with no neighbours in G
  }
};
