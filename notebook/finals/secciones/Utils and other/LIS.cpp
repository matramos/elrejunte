/* Change comparisons and binary search for non-increasing
Given an array, paint it in the least number of colors so 
that each color turns to a non-increasing subsequence. 
Solution: Min number of colors=Length of the longest 
increasing subsequence */
struct lis {
  T INF; int n; 
  vector<T> a, ret; // secuencia y respuesta
  vector<int> p; // padres
  // d[i]=ultimo valor de la subsecuencia de tamanio i
  vector<pair<T,int>> d; 
  lis(T INF_, vector<T> &a_) {
    INF = INF_; n = sz(a_); a = a_; 
    d.resize(n+1); p.resize(n+1);
  }
  void rec(int i) {
    if(i == -1) return;
    ret.push_back(a[i]); rec(p[i]);
  }
  int run() {
    d[0] = {-INF,-1};
    forn(i,n) d[i+1] = {INF, -1};
    forn(i,n) {
      int j = int(upper_bound(d.begin(), d.end(), mp(a[i], n))-d.begin());
      if(d[j-1].fst<a[i] && a[i]<d[j].fst) {
        p[i] = d[j-1].snd; d[j] = {a[i], i};
      }
    }
    ret.clear();
    dforn(i, n+1) if(d[i].fst!=INF) {
      rec(d[i].snd);  // reconstruir
      reverse(ret.begin(), ret.end());
      return i;  // longitud
    }
    return 0;
  }
};
