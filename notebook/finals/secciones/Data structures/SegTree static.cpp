struct RMQ { // LVL such that 2^LVL>n
  tipo vec[LVL][1 << (LVL + 1)];
  tipo& operator[](int p) { return vec[0][p]; }
  tipo get(int i, int j) {  // intervalo [i,j) - O(1)
    int p = 31 - __builtin_clz(j - i);
    return min(vec[p][i], vec[p][j - (1 << p)]);
  }
  void build(int n) {  // O(nlogn)
    int mp = 31 - __builtin_clz(n);
    forn(p, mp) forn(x, n - (1 << p)) vec[p + 1][x] =
        min(vec[p][x], vec[p][x + (1 << p)]);
  }
};  // insert data with []; call build; answer queries
