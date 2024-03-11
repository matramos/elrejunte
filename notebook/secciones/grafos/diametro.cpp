vector<int> G[MAXN];
int n, m, p[MAXN], d[MAXN], d2[MAXN];
int bfs(int r, int* d) {
  queue<int> q;
  d[r] = 0, q.push(r);
  int v;
  while (sz(q)) {
    v = q.front();
    q.pop();
    forall(it, G[v]) if (d[*it] == -1) {
      d[*it] = d[v] + 1, p[*it] = v, q.push(*it);
    }
  }
  return v;  // ultimo nodo visitado
}
vector<int> diams;
vector<ii> centros;
void diametros() {
  memset(d, -1, sizeof(d));
  memset(d2, -1, sizeof(d2));
  diams.clear(), centros.clear();
  forn(i, n) if (d[i] == -1) {
    int v, c;
    c = v = bfs(bfs(i, d2), d);
    forn(_, d[v] / 2) c = p[c];
    diams.pb(d[v]);
    if (d[v] & 1) centros.pb(ii(c, p[c]));
    else centros.pb(ii(c, c));
  }
}
