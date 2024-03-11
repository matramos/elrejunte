struct HopcroftKarp {  // [0,n)->[0,m) (ids independent in each side)
  vector<vector<int>> g;
  int n, m;
  vector<int> mt, mt2, ds;
  HopcroftKarp(int nn, int mm) : n(nn), m(mm), g(n) {}
  void add(int a, int b) { g[a].pb(b); }
  bool bfs() {
    queue<int> q;
    ds = vector<int>(n, -1);
    forn(i, n) if (mt2[i] < 0) ds[i] = 0, q.push(i);
    bool r = false;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (int y : g[x]) {
        if (mt[y] >= 0 && ds[mt[y]] < 0) {
          ds[mt[y]] = ds[x] + 1, q.push(mt[y]);
        } else if (mt[y] < 0) r = true;
      }
    }
    return r;
  }
  bool dfs(int x) {
    for (int y : g[x]) {
      if (mt[y] < 0 || ds[mt[y]] == ds[x] + 1 && dfs(mt[y])) {
        mt[y] = x, mt2[x] = y;
        return true;
      }
    }
    ds[x] = 1 << 30;
    return false;
  }
  int mm() {  // O(sqrt(V)*E)
    int r = 0;
    mt = vector<int>(m, -1);
    mt2 = vector<int>(n, -1);
    while (bfs()) forn(i, n) if (mt2[i] < 0) r += dfs(i);
    return r;
  }
};
