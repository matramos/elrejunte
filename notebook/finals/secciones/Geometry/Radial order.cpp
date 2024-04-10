struct cmp {//sort around O in CCW direction starting from v
  pto o, v; // center point and starting vector
  cmp(pto no, pto nv) : o(no), v(nv) {}
  bool half(pto p) {
    assert(!(p.x == 0 && p.y == 0));//(0,0) not well defined
    return (v ^ p) < 0 || ((v ^ p) == 0 && (v * p) < 0);
  }
  bool operator()(pto& p1, pto& p2) {
    return mp(half(p1 - o), T(0)) <
           mp(half(p2 - o), ((p1 - o) ^ (p2 - o)));
  }
};
