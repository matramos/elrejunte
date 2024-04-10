void cargarComb() { // O(MAXN^2)
  forn(i, MAXN) { // comb[i][k] = i!/(k!*(i-k)!)
    comb[0][i] = 0; comb[i][0] = comb[i][i] = 1;
    forr(k, 1, i)
      comb[i][k] = (comb[i-1][k-1] + comb[i-1][k]) % MOD;
  }
}
// returns comb(n,k)%p, needs comb[0..p][0..p] precalculated
ll lucas(ll n, ll k, int p) {
  ll aux = 1;
  while (n + k) {
    aux = (aux * comb[n % p][k % p]) % p; n /= p, k /= p;
  }
  return aux;
}
