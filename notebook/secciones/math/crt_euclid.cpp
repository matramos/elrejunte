// ecuacion diofantica lineal
// sea d = gcd(a,b); la ecuacion a * x + b * y = c tiene soluciones enteras si
// d|c. La siguiente funcion nos sirve para esto. De forma general sera:
// x = x0 + (b/d)n			x0 = x*c/d
// y = y0 - (a/d)n			y0 = y*c/d
// la funcion devuelve d
ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

// Chinese remainder theorem (special case): find z such that
// z % m = a, z % n = b.  Here, z is unique modulo M = lcm(m, n)
// Returns -1 when there is no solution 
// CRT is associative
ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y);
  if ((a - b) % g != 0) return -1; // uncomment to get RTE when there is no solution
  assert((a - b) % g == 0);
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}
