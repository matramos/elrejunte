struct UnionFind {
  int nsets;
  vector<int> f, setsz;  // f[i] = parent of node i
  UnionFind(int n) : nsets(n), f(n, -1), setsz(n, 1) {}
  int comp(int x){return (f[x]==-1 ? x : f[x]=comp(f[x]));}
  bool join(int i, int j) {//returns true if already in same
    int a = comp(i), b = comp(j);
    if (a != b) {
      if (setsz[a] > setsz[b]) swap(a, b);
      f[a] = b; // big group (b) now represents small (a) 
      nsets--, setsz[b] += setsz[a];
    }
    return a == b;
  }
};

struct dsu_save {
  int v, rnkv, u, rnku;
  dsu_save() {}
  dsu_save(int _v, int _rnkv, int _u, int _rnku)
      : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};
struct dsu_with_rollbacks {
  vector<int> p, rnk;
  int comps;
  stack<dsu_save> op;
  dsu_with_rollbacks() {}
  dsu_with_rollbacks(int n) {
    p.rsz(n), rnk.rsz(n);
    forn(i, n) { p[i] = i, rnk[i] = 0; }
    comps = n;
  }
  int find_set(int v){return(v==p[v]) ? v : find_set(p[v]);}
  bool unite(int v, int u) {
    v = find_set(v), u = find_set(u);
    if (v == u) return false;
    comps--;
    if (rnk[v] > rnk[u]) swap(v, u);
    op.push(dsu_save(v, rnk[v], u, rnk[u]));
    p[v] = u;
    if (rnk[u] == rnk[v]) rnk[u]++;
    return true;
  }
  void rollback() {
    if (op.empty()) return;
    dsu_save x = op.top();
    op.pop(), comps++;
    p[x.v] = x.v, rnk[x.v] = x.rnkv;
    p[x.u] = x.u, rnk[x.u] = x.rnku;
  }
};
