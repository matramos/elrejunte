struct segm {
  pto s, e;
  segm(pto s_, pto e_) : s(s_), e(e_) {}
  pto closest(pto b) {
    pto bs = b - s, es = e - s;
    ld l = es * es;
    if (abs(l) <= EPS) return s;
    ld t = (bs * es) / l;
    if (t < 0.) return s;       // comment for lines
    else if (t > 1.) return e;  // comment for lines
    return s + (es * t);
  }
  bool inside(pto b) { return abs(s.dist(b) + e.dist(b) - s.dist(e)) < EPS; }
  pto inter(segm b) {  // if a and b are collinear, returns one point
    if ((*this).inside(b.s)) return b.s;
    if ((*this).inside(b.e)) return b.e;
    pto in = line(s, e).inter(line(b.s, b.e));
    if ((*this).inside(in) && b.inside(in)) return in;
    return pto(INF, INF);
  }
};
