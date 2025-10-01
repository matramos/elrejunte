struct frac {
  int p, q;
  frac(int p = 0, int q = 1) : p(p), q(q) { norm(); }
  void norm() {
    int a = gcd(q, p);
    if (a) p /= a, q /= a;
    else q = 1;
    if (q < 0) q = -q, p = -p;
  }
  frac operator+(const frac& o) {
    int a = gcd(o.q, q);
    return frac(p * (o.q / a) + o.p * (q / a), q * (o.q / a));
  }
  frac operator-(const frac& o) {
    int a = gcd(o.q, q);
    return frac(p * (o.q / a) - o.p * (q / a), q * (o.q / a));
  }
  frac operator*(frac o) {
    int a = gcd(o.p, q), b = gcd(p, o.q);
    return frac((p / b) * (o.p / a), (q / a) * (o.q / b));
  }
  frac operator/(frac o) {
    int a = gcd(o.q, q), b = gcd(p, o.p);
    return frac((p / b) * (o.q / a), (q / a) * (o.p / b));
  }
  bool operator<(const frac& o) const { return p * o.q < o.p * q; }
  bool operator==(frac o) { return p == o.p && q == o.q; }
};
