#define MAXMOD 15485867
ll inv[MAXMOD];     // inv[i]*i=1 mod MOD
void calc(int p) {  // O(p)
  inv[1] = 1; forr(i,2,p) inv[i] = p - ((p/i) * inv[p%i])%p;
}
int inverso(int x) {                    // O(log MOD)
  return expMod(x, MOD - 2);            // if mod prime
  return expMod(x, eulerPhi(MOD) - 1);  // if not prime
}
// fact[i] = i!%MOD and ifact[i] = 1/(i!)%MOD
// inv is modular inverse function
ll fact[MAXN], ifact[MAXN];
void build_facts() {  // O(MAXN)
  fact[0] = 1; forr(i,1,MAXN) fact[i] = fact[i-1] * i % MOD;
  ifact[MAXN-1] = inverso(fact[MAXN-1]);
  dforn(i, MAXN-1) ifact[i] = ifact[i+1] * (i+1) % MOD;
  return;
}

// Only needed for MOD >= 2^31 (or 2^63)
// For 2^31 < MOD < 2^63 it's usually better to use __int128
// and normal multiplication (* operator) instead of mulMod
// returns (a*b) %c, and minimize overfloor
ll mulMod(ll a, ll b, ll m = MOD) {  // O(log b)
  ll x = 0, y = a % m;
  while (b > 0) {
    if (b % 2 == 1) x = (x + y) % m;
    y = (y * 2) % m;
    b /= 2;
  }
  return x % m;
}
ll expMod(ll b, ll e, ll m = MOD) {  // O(log e)
  if (e < 0) return 0;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * b % m; // ret = mulMod(ret,b,m);
    b = b * b % m;                // b = mulMod(b,b,m);
    e >>= 1;
  }
  return ret;
}
