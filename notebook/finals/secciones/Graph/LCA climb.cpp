#define lg(x) (31 - __builtin_clz(x))  //=floor(log2(x))
struct LCA {  // Usage: 1) Create 2) Add edges 3) Call build
  int N, LOGN, ROOT;
  vector<int> L;  // L[v] holds the level of v
  vector<vector<int>> vp, G; // vp[x][k] = 2^k ancestor of x
  LCA(int n, int root)
      : N(n), LOGN(lg(n) + 1), ROOT(root), L(n), G(n) {
    vp = vector<vector<int>>(n, vector<int>(LOGN, root));
  }
  void addEdge(int a, int b) { G[a].pb(b), G[b].pb(a); }
  void dfs(int node, int p, int lvl) {
    vp[node][0] = p, L[node] = lvl;
    forall(it, G[node]) if (*it != p) dfs(*it, node, lvl+1);
  }
  void build() {
    dfs(ROOT, ROOT, 0);
    forn(k, LOGN-1) forn(i, N) vp[i][k+1] = vp[vp[i][k]][k];
  }
  int climb(int a, int d) {  // O(lgn)
    if (!d) return a;
    dforn(i, lg(L[a])+1) if(1<<i <= d) a=vp[a][i], d-=1<<i;
    return a;
  }
  int lca(int a, int b) {  // O(lgn)
    if (L[a] < L[b]) swap(a, b);
    a = climb(a, L[a] - L[b]);
    if (a == b) return a;
    dforn(i, lg(L[a]) + 1) if (vp[a][i] != vp[b][i])
      a = vp[a][i], b = vp[b][i];
    return vp[a][0];
  }
  int dist(int a, int b){return L[a]+L[b] - 2*L[lca(a, b)];}
};
