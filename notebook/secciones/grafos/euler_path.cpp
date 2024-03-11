// Be careful with nodes with degree 0 when solving your problem, the
// comments below assume that there are no nodes with degree 0.
//
// Euler [path/cycle] exists in a bidirectional graph iff the graph is
// connected and at most [2/0] nodes have odd degree. The path must
// start from an odd degree vertex when there are 2.
//
// Euler [path/cycle] exists in a directed graph iff the graph is
// [connected when making edges bidirectional / a single SCC], and
// at most [1/0] node have indg - outdg = 1, at most [1/0] node have
// outdg - indg = 1, all the other nodes have indg = outdg. The path
// must start from the node with outdg - indg = 1, when there is one.
//
// Directed version (uncomment commented code for undirected)
struct edge {
  int y;
  // list<edge>::iterator rev;
  edge(int yy) : y(yy) {}
};
struct EulerPath {
  vector<list<edge>> g;
  EulerPath(int n) : g(n) {}
  void addEdge(int a, int b) {
    g[a].push_front(edge(b));
    // auto ia = g[a].begin();
    // g[b].push_front(edge(a));
    // auto ib = g[b].begin();
    // ia->rev=ib, ib->rev=ia;
  }
  vector<int> p;
  void go(int x) {
    while (sz(g[x])) {
      int y = g[x].front().y;
      // g[y].erase(g[x].front().rev);
      g[x].pop_front();
      go(y);
    }
    p.push_back(x);
  }
  vector<int> getPath(int x) {  // get a path that starts from x
    // you must check that a path exists from x before calling get_path!
    p.clear(), go(x);
    reverse(p.begin(), p.end());
    return p;
  }
};
