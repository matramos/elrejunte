struct SuffixTree {
  vector<char> s;
  vector<map<int, int>> to; // fst char of edge -> node
  // s[fpos[i], fpos[i]+len[i]): susbtr on edge from i's
  // father to i.
  // link[i] goes to the node that corresponds to the substr
  // that result after "removing" the first char of the
  // substr that i represents. Not defined for leaf nodes.
  vector<int> len, fpos, link;
  SuffixTree() { make_node(0, INF); }// maybe reserve memory
  int node = 0, pos = 0, n = 0;
  int make_node(int p, int l) {
    fpos.pb(p), len.pb(l), to.pb({}), link.pb(0);
    return sz(to) - 1;
  }
  void go_edge() {
    while (pos > len[to[node][s[n - pos]]]) {
      node = to[node][s[n - pos]];
      pos -= len[node];
    }
  }
  void add(char c) {
    int last = 0; s.pb(c), n++, pos++;
    while (pos > 0) {
      go_edge(); int edge = s[n - pos];
      int& v = to[node][edge]; int t = s[fpos[v] + pos-1];
      if (v == 0) {
        v=make_node(n-pos, INF); link[last]=node; last=0;
      } else if (t == c) { link[last] = node; return; }
      else {
        int u = make_node(fpos[v], pos - 1);
        to[u][c] = make_node(n - 1, INF);
        to[u][t] = v; fpos[v] += pos-1, len[v] -= pos-1;
        v = u, link[last] = u, last = u;
      }
      if (node == 0) pos--;
      else node = link[node];
    }
  }
  void finishedAdding() {
    forn(i,sz(len)) if(len[i]+fpos[i]>n) len[i] = n-fpos[i];
  }
  // Map each suffix with it corresponding leaf node
  // vleaf[i] = node id of leaf of suffix s[i..n)
  // The last character of the string must be unique. Use
  // 'buildLeaf' not 'dfs' directly. Also 'finishedAdding'
  // must be called before calling 'buildLeaf'. When this is
  // needed, usually binary lifting (vp) and depths are also
  // needed. Usually you also need to compute extra
  // information in the dfs
  vector<int> vleaf, vdepth; vector<vector<int>> vp;
  void dfs(int cur, int p, int curlen) {
    if (cur > 0) curlen += len[cur];
    vdepth[cur] = curlen; vp[cur][0] = p;
    if (to[cur].empty()) {
      assert(0 < curlen && curlen <= n);
      assert(vleaf[n - curlen] == -1);
      vleaf[n - curlen] = cur;
      // here maybe compute some extra info
    } else forall(it, to[cur]) {
        dfs(it->snd, cur, curlen);
        // here maybe compute some extra info
      }
  }
  void buildLeaf() {
    vdepth.rsz(sz(to), 0);                // tree size
    vleaf.rsz(n, -1);                     // string size
    vp.rsz(sz(to), vector<int>(MAXLOG));  // tree size * log
    dfs(0, 0, 0);
    forr(k, 1, MAXLOG) forn(i, sz(to))
      vp[i][k] = vp[vp[i][k - 1]][k - 1];
    forn(i, n) assert(vleaf[i] != -1);
  }
};
