struct Kosaraju {
  vector<vector<int>> G, gt;
  // nodos 0...N-1 ; componentes 0...cantcomp-1
  int N, cantcomp;
  vector<int> comp, used;
  stack<int> pila;
  Kosaraju(int n) : G(n), gt(n), N(n), comp(n) {}
  void addEdge(int a, int b) { G[a].pb(b), gt[b].pb(a); }
  void dfs1(int nodo) {
    used[nodo] = 1;
    forall(it, G[nodo]) if (!used[*it]) dfs1(*it);
    pila.push(nodo);
  }
  void dfs2(int nodo) {
    used[nodo] = 2;
    comp[nodo] = cantcomp - 1;
    forall(it, gt[nodo]) if (used[*it] != 2) dfs2(*it);
  }
  void run() {
    cantcomp = 0;
    used = vector<int>(N, 0);
    forn(i, N) if (!used[i]) dfs1(i);
    while (!pila.empty()) {
      if (used[pila.top()] != 2) {
        cantcomp++;
        dfs2(pila.top());
      }
      pila.pop();
    }
  }
};
