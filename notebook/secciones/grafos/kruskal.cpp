struct UF {
  void init(int n) {}
  void unir(int a, int v) {}
  int comp(int n) { return 0; }
} uf;
vector<ii> G[MAXN];
int n;

struct Ar {
  int a, b, w;
};
bool operator<(const Ar& a, const Ar& b) { return a.w < b.w; }
vector<Ar> E;

// Minimun Spanning Tree in O(e log e)
ll kruskal() {
  ll cost = 0;
  sort(E.begin(), E.end());  // ordenar aristas de menor a mayor
  uf.init(n);
  forall(it, E) {
    if (uf.comp(it->a) != uf.comp(it->b)) {  // si no estan conectados
      uf.unir(it->a, it->b);                 // conectar
      cost += it->w;
    }
  }
  return cost;
}
