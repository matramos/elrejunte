const int P = 1777771, MOD[2] = {999727999, 1070777777};
const int PI[2]={325255434,10018302};//PI[i] = P^-1 % MOD[i]
struct Hash {
  vector<int> h[2], pi[2];
  vector<ll> vp[2]; // Only for getChanged
  Hash(string& s) {
    forn(k, 2)
      h[k].rsz(sz(s)+1), pi[k].rsz(sz(s)+1),
      vp[k].rsz(sz(s)+1);
    forn(k, 2) {
      ll p = 1; h[k][0] = 0; vp[k][0] = pi[k][0] = 1;
      forr(i, 1, sz(s) + 1) {
        h[k][i] = (h[k][i - 1] + p * s[i - 1]) % MOD[k];
        pi[k][i] = (1LL * pi[k][i - 1] * PI[k]) % MOD[k];
        vp[k][i] = p = (p * P) % MOD[k];
      }
    }
  }
  ll get(int s, int e) {//get hash value of substring [s, e)
    ll H[2];
    forn(i, 2) {
      H[i] = (h[i][e] - h[i][s] + MOD[i]) % MOD[i];
      H[i] = (1LL * H[i] * pi[i][s]) % MOD[i];
    }
    return (H[0] << 32) | H[1];
  }
  // get hash value of [s, e) if origVal in pos is changed
  // to val. For multiple changes, do what is done in the
  // for loop for each change
  ll getChanged(int s,int e,int pos,int val,int origVal) {
    ll hv = get(s, e), hh[2];
    hh[1] = hv & ((1LL << 32) - 1); hh[0] = hv >> 32;
    forn(i, 2)
      hh[i]=(hh[i]+vp[i][pos]*(val-origVal+MOD[i]))%MOD[i];
    return (hh[0] << 32) | hh[1];
  }
};
