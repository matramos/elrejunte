// Para non-increasing, cambiar comparaciones y revisar busq binaria
// Given an array, paint it in the least number of colors so that each
// color turns to a non-increasing subsequence. Solution:Min number of
// colors=Length of the longest increasing subsequence
int N, a[MAXN];  // secuencia y su longitud
ii d[MAXN + 1];  // d[i]=ultimo valor de la subsecuencia de tamanio i
int p[MAXN];     // padres
vector<int> R;   // respuesta
void rec(int i) {
  if (i == -1) return;
  R.push_back(a[i]);
  rec(p[i]);
}
int lis() {  // O(nlogn)
  d[0] = ii(-INF, -1);
  forn(i, N) d[i + 1] = ii(INF, -1);
  forn(i, N) {
    int j = upper_bound(d, d + N + 1, ii(a[i], INF)) - d;
    if (d[j - 1].first < a[i] && a[i] < d[j].first) {
      p[i] = d[j - 1].second;
      d[j] = ii(a[i], i);
    }
  }
  R.clear();
  dforn(i, N + 1) if (d[i].first != INF) {
    rec(d[i].second);  // reconstruir
    reverse(R.begin(), R.end());
    return i;  // longitud
  }
  return 0;
}
