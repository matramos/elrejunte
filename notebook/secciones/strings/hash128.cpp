typedef __int128 bint;  // needs gcc compiler?
const bint MOD = 212345678987654321LL, P = 1777771, PI = 106955741089659571LL;
struct Hash {
  vector<bint> h, pi;
  Hash(string& s) {
    assert((P * PI) % MOD == 1);
    h.resize(s.size() + 1), pi.resize(s.size() + 1);
    h[0] = 0, pi[0] = 1;
    bint p = 1;
    forr(i, 1, sz(s) + 1) {
      h[i] = (h[i - 1] + p * s[i - 1]) % MOD;
      pi[i] = (pi[i - 1] * PI) % MOD;
      p = (p * P) % MOD;
    }
  }
  ll get(int s, int e) {  // get hash value of the substring [s, e)
    return (((h[e] - h[s] + MOD) % MOD) * pi[s]) % MOD;
  }
};
