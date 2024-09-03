/* Can solve cyclic expected values: given a matrix Pij 
(probability of moving from node i to node j), then the 
expected number of steps to reach node T from i is 
E(i) = 1 + sum(Pij*E(j)) or E(i) - sum(Pij*E(j)) = 1 
Then, each i generates a row in the system of equations. 
Note that the row and column corresponding to T must be 
removed before applying Gauss-Jordan. */
// comments useful for MOD version
const double EPS = 1e-9; // remove for MOD version
const int INF = 2; // a value to indicate infinite solutions
// int instead of double for MOD
int gauss(vector<vector<double>> a, vector<double>& ans) {
  int n = sz(s), m = sz(a[0]) - 1;
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for (int i = row; i < n; ++i)
      // remove abs for MOD
      if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
    // remove abs, and check == 0 for MOD
    if (abs(a[sel][col]) < EPS) continue;
    for (int i=col; i <= m; ++i) swap(a[sel][i], a[row][i]);
    where[col] = row;
    for (int i = 0; i < n; ++i) if (i != row) {
      double c = a[i][col] / a[row][col]; // inverse for MOD
      for(int j=col; j <= m; ++j) a[i][j]-=a[row][j]*c;//MOD
    }
    ++row;
  }
  ans.assign(m, 0);
  for (int i = 0; i < m; ++i)
    // use inverse for MOD
    if(where[i]!=-1) ans[i] = a[where[i]][m]/a[where[i]][i];
  for (int i = 0; i < n; ++i) {
    double sum = 0;
    for (int j=0; j < m; ++j) sum += ans[j] * a[i][j];//MOD
    // remove abs, and check != 0 for MOD
    if (abs(sum - a[i][m]) > EPS) return 0; 
  }
  for (int i=0; i < m; ++i) if (where[i] == -1) return INF;
  return 1;
}

// Gauss Jordan with bitsets version, for MOD = 2
// finds lexicograhically minimal solution (0<1, False<True)
// for maximal change your solution model accordingly
int gauss(vector<bitset<N>> a, int n,int m, bitset<N>& ans){
  vector<int> where(m, -1);
  for (int col = m-1, row = 0; col >= 0 && row < n; --col) {
    for (int i = row; i < n; ++i) if (a[i][col]) {
      swap(a[i], a[row]); break;
    }
    if (!a[row][col]) continue;
    where[col] = row;
    for (int i = 0; i < n; ++i)
      if (i != row && a[i][col]) a[i] ^= a[row];
    ++row;
  }
  ans.reset();
  forn(i, m) if (where[i] != -1) {
    ans[i] = a[where[i]][m] & a[where[i]][i];
  }
  forn(i, n) if((ans & a[i]).count()%2 != a[i][m]) return 0;
  forn(i, m) if(where[i] == -1) return INF;
  return 1;
}
