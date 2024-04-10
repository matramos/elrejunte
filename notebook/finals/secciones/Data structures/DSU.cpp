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
