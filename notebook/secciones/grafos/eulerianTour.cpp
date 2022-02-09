//In a connected graph where all the nodes have even degree
//finds a path that start and finish in the same node (SRC)
// and uses every edge once.
struct EulerianTour {
  int N, M = 0, odd = 0;
  std::vector<std::vector<std::pair<int, int>>> E;
  std::vector<int> deg;
  std::vector<bool> vis;
  EulerianTour(int N) : N(N), E(N), deg(N), vis(N) {}
  void add_edge(int u, int v) {
    int V[2] = {u, v};
    for (auto t : {0, 1}) {
      int v = V[t];
      E[v].emplace_back(V[t ^ 1], M << 1 | t);
      deg[v] += 1;
      odd += (deg[v] % 2 ? +1 : -1);
    }
    ++M;
  }
  // returns eulerian tour by vertices and edges (reversed if first bit is 1)
  pair<vector<int>, vector<int>> find(int src) {
	  //run for every component if graph isn't connected
    assert(odd == 0);
    auto d = deg;
    vector<bool> dead(M, false);
    vector<int> ptr(N, 0), p, e;
    stack<ii> stk;
    stk.emplace(src, -1);
    while (!stk.empty()) {
	  ii aux = stk.top();
	  int u=aux.fst, i = aux.snd;
      vis[u] = true;
      if (d[u] == 0) {
        stk.pop();
        p.push_back(u);
        if (i != -1) e.push_back(i);
      } else {
        for (int& l = ptr[u]; l < deg[u]; ++l) {
          ii aux2 = E[u][l];
          int v=aux2.fst, j=aux2.snd;
          if (!dead[j >> 1]) {
            stk.emplace(v, j);
            --d[u], --d[v], dead[j >> 1] = true;
            break;
          }
        }
      }
    }
    return {p, e};
  }
};

