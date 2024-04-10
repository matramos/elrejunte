struct CHT {
  deque<pto> h; T f = 1, pos;
   // min_=1 for min queries
  CHT(bool min_ = 0) : f(min_ ? 1 : -1), pos(0) {}
  void add(pto p) {  // O(1), pto(m,b) <=> y = mx + b
    p = p * f;
    if (h.empty()) { h.pb(p); return; }
    // p.x should be the lower/greater hull x
    assert(p.x <= h[0].x || p.x >= h.back().x);
    if (p.x <= h[0].x) {
      while(sz(h)>1&&h[0].left(p,h[1])) h.pop_front(),pos--;
      h.push_front(p), pos++;
    } else {
      while(sz(h) > 1 && h[sz(h)-1].left(h[sz(h)-2], p))
        h.pop_back();
      h.pb(p);
    }
    pos = min(max(T(0), pos), T(sz(h) - 1));
  }
  T get(T x) {
    pto q = {x, 1};
    // O(log) query for unordered x
    int L = 0, R = sz(h) - 1, M;
    while (L < R) {
      M = (L + R) / 2;
      if (h[M + 1] * q <= h[M] * q) L = M + 1;
      else R = M;
    }
    return h[L] * q * f;
    // O(1) query for ordered x
    while (pos > 0 && h[pos-1]*q < h[pos]*q) pos--;
    while (pos < sz(h)-1 && h[pos+1]*q < h[pos]*q) pos++;
    return h[pos] * q * f;
  }
};
