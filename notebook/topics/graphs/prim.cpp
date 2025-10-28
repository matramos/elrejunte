vector<ii> G[MAXN];
bool taken[MAXN];
priority_queue<ii, vector<ii>, greater<ii> > pq;  // min heap
void process(int v) {
  taken[v] = true;
  forall(e, G[v]) if (!taken[e->second]) pq.push(*e);
}
// Minimun Spanning Tree in O(n^2)
ll prim() {
  zero(taken);
  process(0);
  ll cost = 0;
  while (sz(pq)) {
    ii e = pq.top();
    pq.pop();
    if (!taken[e.second]) cost += e.first, process(e.second);
  }
  return cost;
}