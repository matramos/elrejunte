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
