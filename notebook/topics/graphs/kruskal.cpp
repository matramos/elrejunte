struct Edge {
  int a, b, w;
};
bool operator<(const Edge& a, const Edge& b) { return a.w < b.w; }
// Minimun Spanning Tree in O(E log E)
ll kruskal(vector<Edge> &E, int n) {
  ll cost = 0; sort(E.begin(), E.end()); 
  UnionFind uf(n);
  forall(it, E) if(!uf.join(it->a, it->b))
    cost += it->w;
  return cost;
}
