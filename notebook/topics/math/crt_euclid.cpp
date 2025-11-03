// ecuacion diofantica lineal
// sea d=gcd(a,b); la ecuacion a * x + b * y = c tiene soluciones enteras si
// d|c. La siguiente funcion nos sirve para esto. De forma general sera:
// x = x0 + (b/d)n			x0 = xx*c/d
// y = y0 - (a/d)n			y0 = yy*c/d
// la funcion devuelve d
ll euclid(ll a, ll b, ll &xx, ll &yy) {
  if (!b) return xx = 1, yy = 0, a;
  ll d = euclid(b, a % b, yy, xx);
  return yy -= a / b * xx, d;
}

// Chinese remainder theorem (special case): find z such that
// z % m = a, z % n = b.  Here, z is unique modulo M = lcm(m, n)
// Return -1 when there is no solution 
// CRT is associative and idempotent
ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y);
  if ((a - b) % g != 0) return -1; // comment to get RTE when there is no solution
  assert((a - b) % g == 0);
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}

// Chinese remainder theorem: find z such that z % m[i] = r[i] for all i.
// Note that the solution is unique modulo M = lcm_i (m[i]).
// Return z. On failure, return -1.
// Note that we do not require the m[i]'s to be relatively prime.
ll crt(const vector<ll>& r, const vector<ll>& m) {
	assert(sz(r) == sz(m));
	ll ret = r[0], l = m[0];
	forr(i, 1, sz(m)) {
		ret = crt(ret, l, r[i], m[i]);
		l = lcm(l,m[i]);
		if (ret == -1) break;
	}
	return ret;
}
