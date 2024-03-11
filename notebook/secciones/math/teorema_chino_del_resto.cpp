// Chinese remainder theorem (special case): find z such that
// z % m1 = r1, z % m2 = r2.  Here, z is unique modulo M = lcm(m1, m2).
// Return (z, M).  On failure, M = -1.
//{xx,yy,d} son variables globales usadas en extendedEuclid
ii chinese_remainder_theorem(int m1, int r1, int m2, int r2) {
  extendedEuclid(m1, m2);
  if (r1 % d != r2 % d) return make_pair(0, -1);
  return mp(sumMod(xx * r2 * m1, yy * r1 * m2, m1 * m2) / d, m1 * m2 / d);
}
// Chinese remainder theorem: find z such that z % m[i] = r[i] for all i.
// Note that the solution is unique modulo M = lcm_i (m[i]).
// Return (z, M). On failure, M = -1.
// Note that we do not require the a[i]'s to be relatively prime.
ii chinese_remainder_theorem(const vector<int>& m, const vector<int>& r) {
  ii ret = mp(r[0], m[0]);
  forr(i, 1, m.size()) {
    ret = chinese_remainder_theorem(ret.snd, ret.fst, m[i], r[i]);
    if (ret.snd == -1) break;
  }
  return ret;
}
