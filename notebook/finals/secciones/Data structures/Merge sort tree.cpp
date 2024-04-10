typedef ii datain;     // data that goes into the DS
typedef int query;     // info related to a query
typedef bool dataout;  // data that results from a query
struct DS {
  set<datain> s; // replace set with what you need
  void insert(const datain& x) {
    // modify this method according to problem
    // example below is disjoint intervals (union of ranges)
    datain xx = x;  // copy to avoid changing original
    if (xx.fst >= xx.snd) return;
    auto at = s.lower_bound(xx);
    auto it = at;
    if (at != s.begin() && (--at)->snd >= xx.fst)
      xx.fst = at->fst, --it;
    for (;it!=s.end() && it->fst <= xx.snd; s.erase(it++))
      xx.snd = max(xx.snd, it->snd);
    s.insert(xx);
  }
  void get(const query& q, dataout& ans) {
    // modify this method according to problem
    // example below is "is there any range covering q?"
    set<datain>::iterator ite = s.ub(mp(q + 1, 0));
    if (ite != s.begin() && prev(ite)->snd > q) ans = true;
  }
};
struct MST {
  int sz;
  vector<DS> t;
  MST(int n) {
    sz = 1 << (32 - __builtin_clz(n));
    t = vector<DS>(2 * sz);
  }
  void insert(int i,int j, datain& x){insert(i,j,x,1,0,sz);}
  void insert(int i, int j, datain& x, int n, int a, int b){
    if (j <= a || b <= i) return;
    if (i <= a && b <= j) {
      t[n].insert(x);
      return;
    }
    // when want to update ranges that intersec with [i,j)
    // usually only on range-query + point-update problem
    // t[n].insert(x);
    int c = (a + b) / 2;
    insert(i, j, x, 2 * n, a, c);
    insert(i, j, x, 2 * n + 1, c, b);
  }
  void get(int i, int j, query& q, dataout& ans) {
    return get(i, j, q, ans, 1, 0, sz);
  }
  void get(int i, int j, query& q, dataout& ans,
           int n, int a, int b) {
    if (j <= a || b <= i) return;
    if (i <= a && b <= j) {
      t[n].get(q, ans);
      return;
    }
    // when want to get from ranges that intersec with [i,j)
    // usually only on point-query + range-update problem
    // t[n].get(q, ans);
    int c = (a + b) / 2;
    get(i, j, q, ans, 2 * n, a, c);
    get(i, j, q, ans, 2 * n + 1, c, b);
  }
};  // Use: 1- definir todo lo necesario en DS, 2- usar
