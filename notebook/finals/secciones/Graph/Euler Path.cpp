// Be careful, comments below assume that there are no nodes
// with degree 0. Euler [path/cycle] exists in a BIDIREC
// graph iff it is connected and have at most [2/0] odd
// degree nodes. Path starts from odd vertex when exists
// Euler [path/cycle] exists in a DIREC graph iff the graph
// is [connected when making edges bidirectional / a single
// SCC], and at most [1/0] node have indg - outdg = 1, at
// most [1/0] node have outdg - indg = 1, all the other
// nodes have indg = outdg. Start from node with outdg -
// indg = 1, when exists
struct edge { // Dir version (add commented code for undir)
  int y;
  // list<edge>::iterator rev;
  edge(int yy) : y(yy) {}
};
struct EulerPath {
  vector<list<edge>> g;
  EulerPath(int n) : g(n) {}
  void addEdge(int a, int b) {
    g[a].push_front(edge(b));
    // auto ia = g[a].begin(); g[b].push_front(edge(a));
    // auto ib = g[b].begin(); ia->rev=ib, ib->rev=ia;
  }
  vector<int> p;
  void go(int x) {
    while (sz(g[x])) {
      int y = g[x].front().y;
      // g[y].erase(g[x].front().rev);
      g[x].pop_front(); go(y);
    }
    p.push_back(x);
  }
  vector<int> getPath(int x){//get a path that starts from x
    // you must check that path exists from x before calling
    p.clear(), go(x); reverse(p.begin(), p.end()); return p;
  }
};
