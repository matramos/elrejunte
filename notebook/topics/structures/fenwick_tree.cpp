struct FenwickTree {
  int N;            // maybe replace vector with unordered_map when "many 0s"
  vector<tipo> ft;  // for more dimensions, make ft multi-dimensional
  FenwickTree(int n) : N(n), ft(n + 1) {}
  void upd(int i0, tipo v) {  // add v to i0th element (0-based)
    // add extra fors for more dimensions
    for (int i = i0 + 1; i <= N; i += i & -i) ft[i] += v;
  }
  tipo get(int i0) {  // get sum of range [0,i0)
    tipo r = 0;       // add extra fors for more dimensions
    for (int i = i0; i; i -= i & -i) r += ft[i];
    return r;
  }
  tipo get_sum(int i0, int i1) {  // get sum of range [i0,i1) (0-based)
    return get(i1) - get(i0);
  }
};
