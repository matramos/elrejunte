void cargarComb() {  // O(MAXN^2)
  forn(i, MAXN) {    // comb[i][k]=i tomados de a k = i!/(k!*(i-k)!)
    comb[0][i] = 0;
    comb[i][0] = comb[i][i] = 1;
    forr(k, 1, i) comb[i][k] = (comb[i - 1][k - 1] + comb[i - 1][k]) % MOD;
  }
}
ll lucas(ll n, ll k, int p) {  // (n,k)%p, needs comb[p][p] precalculated
  ll aux = 1;
  while (n + k) {
    aux = (aux * comb[n % p][k % p]) % p;
    n /= p, k /= p;
  }
  return aux;
}
