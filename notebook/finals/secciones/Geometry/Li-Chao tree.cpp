struct line {
  T m, b;
  line() {}
  line(T m_, T b_) : m(m_), b(b_) {}
  T f(T x) { return m * x + b; }
  line operator+(line l) { return line(m + l.m, b + l.b); }
  line operator*(T k) { return line(m * k, b * k); }
};
struct li_chao {
  vector<line> cur, add; vector<int> L, R;
  T f, minx, maxx; line identity; int cnt;
  void new_node(line cur_, int l = -1, int r = -1) {
    cur.pb(cur_); add.pb(line(0, 0)); L.pb(l),R.pb(r),cnt++;
  }
  li_chao(bool min_, T minx_, T maxx_) { // for max: min_=0
    f = min_ ? 1 : -1; identity = line(0, INF);
    minx = minx_; maxx = maxx_; cnt = 0;
    new_node(identity);  // root id is 0
  }
  // only when "adding" lines lazily
  void apply(int id, line to_add_) {
    add[id] = add[id] + to_add_;
    cur[id] = cur[id] + to_add_;
  }
  void push_lazy(int id) { // MUST use (even when not lazy)
    if (L[id] == -1) new_node(identity), L[id] = cnt - 1;
    if (R[id] == -1) new_node(identity), R[id] = cnt - 1;
    // code below only needed when lazy ops are needed
    apply(L[id], add[id]); apply(R[id], add[id]);
    add[id] = line(0, 0);
  }
  // only when "adding" lines lazily
  void push_line(int id, T tl, T tr) {
    T m = (tl + tr) / 2;
    insert_line(L[id], cur[id], tl, m);
    insert_line(R[id], cur[id], m, tr);
    cur[id] = identity;
  }
  // O(log), for persistent return int
  void insert_line(int id, line new_line, T l, T r) {
    T m = (l + r) / 2;
    bool lef = new_line.f(l) < cur[id].f(l);
    bool mid = new_line.f(m) < cur[id].f(m);
    // line to_push = new_line, to_keep = cur[id]; //persist
    // if(mid) swap(to_push,to_keep);              //persist
    if (mid) swap(new_line, cur[id]);        // NOT persist?
    if (r - l == 1) {
      // new_node(to_keep); return cnt-1;         // persist
      return;                                 // NOT persist
    }
    push_lazy(id);
    if (lef != mid) {
      // int lid = insert_line(L[id],to_push,l,m); //persist
      // new_node(to_keep, lid, R[id]);            //persist
      // return cnt-1;                             //persist
      insert_line(L[id], new_line, l, m);     // NOT persist
    } else {
      // int rid = insert_line(R[id],to_push,m,r); //persist
      // new_node(to_keep, L[id], rid);            //persist
      // return cnt-1;                             //persist
      insert_line(R[id], new_line, m, r);     // NOT persist
    }
  }
  void insert_line( int id, line new_line){//persist ret int
    insert_line(id, new_line * f, minx, maxx);
  }
  // O(log^2) doesn't support persistence
  void insert_segm(int id,line new_line,T l,T r,T tl,T tr) {
    if (tr <= l || tl >= r || tl >= tr || l >= r) return;
    if (tl >= l && tr <= r) {
      insert_line(id, new_line, tl, tr); return;
    }
    push_lazy(id); T m = (tl + tr) / 2;
    insert_segm(L[id], new_line, l, r, tl, m);
    insert_segm(R[id], new_line, l, r, m, tr);
  }
  void insert_segm(int id, line new_line, T l, T r) {//[l,r)
    insert_segm(id, new_line * f, l, r, minx, maxx);
  }
  // O(log^2) doesn't support persistence
  void add_line(int id, line to_add_, T l, T r, T tl, T tr){
    if (tr <= l || tl >= r || tl >= tr || l >= r) return;
    if (tl >= l && tr <= r) { apply(id, to_add_); return; }
    push_lazy(id);
    push_line(id, tl, tr);  // comment if insert isn't used
    T m = (tl + tr) / 2;
    add_line(L[id], to_add_, l, r, tl, m);
    add_line(R[id], to_add_, l, r, m, tr);
  }
  void add_line(int id, line to_add_, T l, T r) {
    add_line(id, to_add_ * f, l, r, minx, maxx);
  }
  T get(int id, T x, T tl, T tr) {  // O(log)
    if (tl + 1 == tr) return cur[id].f(x);
    push_lazy(id); T m = (tl + tr) / 2;
    if(x<m) return min(cur[id].f(x), get(L[id], x, tl, m));
    else return min(cur[id].f(x), get(R[id], x, m, tr));
  }
  T get(int id, T x) { return get(id, x, minx, maxx) * f; }
};
