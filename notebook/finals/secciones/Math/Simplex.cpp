typedef double tipo;
typedef vector<tipo> vt;
// maximize c^T x s.t. Ax<=b, x>=0,
// returns pair (max val, solution vector)
pair<tipo, vt> simplex(vector<vt> A, vt b, vt c) {
  int n = sz(b), m = sz(c);
  tipo z = 0.;
  vector<int> X(m), Y(n);
  forn(i, m) X[i] = i;
  forn(i, n) Y[i] = i + m;
  auto pivot = [&](int x, int y) {
    swap(X[y], Y[x]);
    b[x] /= A[x][y];
    forn(i, m) if (i != y) A[x][i] /= A[x][y];
    A[x][y] = 1 / A[x][y];
    forn(i, n) if (i != x && abs(A[i][y]) > EPS) {
      b[i] -= A[i][y] * b[x];
      forn(j, m) if (j != y) A[i][j] -= A[i][y] * A[x][j];
      A[i][y] *= -A[x][y];
    }
    z += c[y] * b[x];
    forn(i, m) if (i != y) c[i] -= c[y] * A[x][i];
    c[y] *= -A[x][y];
  };
  while (1) {
    int x = -1, y = -1;
    tipo mn = -EPS;
    forn(i, n) if (b[i] < mn) mn = b[i], x = i;
    if (x < 0) break;
    forn(i, m) if (A[x][i] < -EPS) { y = i; break; }
    assert(y >= 0);  // no solution to Ax<=b
    pivot(x, y);
  }
  while (1) {
    tipo mx = EPS;
    int x = -1, y = -1;
    forn(i, m) if (c[i] > mx) mx = c[i], y = i;
    if (y < 0) break;
    tipo mn = 1e200;
    forn(i, n) if (A[i][y] > EPS && b[i] / A[i][y] < mn) {
      mn = b[i] / A[i][y], x = i;
    }
    assert(x >= 0);  // c^T x is unbounded
    pivot(x, y);
  }
  vt r(m); forn(i, n) if (Y[i] < m) r[Y[i]] = b[i];
  return {z, r};
}
