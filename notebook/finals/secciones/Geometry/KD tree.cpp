bool cmpx(pto a, pto b) { return a.x + EPS < b.x; }
bool cmpy(pto a, pto b) { return a.y + EPS < b.y; }
struct kd_tree {
  pto p; T x0 = INF, x1 = -INF, y0 = INF, y1 = -INF;
  kd_tree *l, *r;
  T distance(pto q) {
    T x = min(max(x0, q.x), x1), y = min(max(y0, q.y), y1);
    return (pto(x, y) - q).norm_sq();
  }
  kd_tree(vector<pto>&& pts) : p(pts[0]) {
    l = nullptr, r = nullptr;
    forn(i, sz(pts)) {
      x0 = min(x0, pts[i].x), x1 = max(x1, pts[i].x);
      y0 = min(y0, pts[i].y), y1 = max(y1, pts[i].y);
    }
    if (sz(pts) > 1) {
      sort(pts.begin(), pts.end(), x1-x0>=y1-y0?cmpx:cmpy);
      int m = sz(pts) / 2;
      l = new kd_tree({pts.begin(), pts.begin() + m});
      r = new kd_tree({pts.begin() + m, pts.end()});
    }
  }
  void nearest(pto q,int k,priority_queue<pair<T,pto>>&ret){
    if (l == nullptr) {
      // if(p == q) return; // avoid query point as answer
      ret.push({(q - p).norm_sq(), p});
      while (sz(ret) > k) ret.pop();
      return;
    }
    kd_tree *al = l, *ar = r;
    T bl = l->distance(q), br = r->distance(q);
    if (bl > br) swap(al, ar), swap(bl, br);
    al->nearest(q, k, ret);
    if (br < ret.top().fst) ar->nearest(q, k, ret);
    while (sz(ret) > k) ret.pop();
  }
  priority_queue<pair<T, pto>> nearest(pto q, int k) {
    priority_queue<pair<T, pto>> ret;
    forn(i, k) ret.push({INF * INF, pto(INF, INF)});
    nearest(q, k, ret);
    return ret;
  }
};
