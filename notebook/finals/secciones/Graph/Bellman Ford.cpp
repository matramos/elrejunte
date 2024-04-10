// Can solve systems of "difference inequalities":
// 1. for each inequality x_i - x_j <= k add an edge j->i
// with weight k; 2. create an extra node Z and add an edge
// Z->i with weigth 0 for each variable x_i in the
// inequalities; 3. run(Z): if negcycle, no solution,
// otherwise "dist" is a solution
//
// Can transform a graph to get edges of positive weight
// (Jhonson algo): 1. Create an extra node Z and add edge
// Z->i with weight 0 for all nodes i; 2. Run bellman ford
// from Z; 3. For each original edge a->b (with weight w),
// change its weigt to be w+dist[a]-dist[b] (where dist is
// the result of step 2); 4. The shortest paths in the old
// and new graph are the same (their weight result may
// differ, but the paths are the same).
// This doesn't work well with neg cycles, but you can find
// them before step 3 and ignore all new weights that result
// in a neg value when executing step 3
struct BellmanFord {
  vector<vector<ii>> G; // pair = (weight, node)
  vector<ll> dist; int N;
  BellmanFord(int n) : G(n), N(n) {}
  void addEdge(int a, int b, ll w) { G[a].pb(mp(w, b)); }
  void run(int src) {  // O(VE)
    dist = vector<ll>(N, INF); dist[src] = 0;
    forn(i, N - 1) forn(j, N) if (dist[j] != INF)
        forall(it, G[j]) dist[it->snd] =
            min(dist[it->snd], dist[j] + it->fst);
  }

  bool hasNegCycle() {
    forn(j, N) if (dist[j] != INF) forall(it, G[j])
      if (dist[it->snd] > dist[j] + it->fst) return true;
    // inside if: all points reachable from it->snd will
    // have -INF distance. But this is not enough to
    // identify which exact nodes belong to a neg cycle, nor
    // which can reach a neg cycle. To do so, you need to
    // run SCC and check whether each SCC hasNegCycle
    // independently. All nodes in a SCC that hasNegCycle
    // are part of a (not necessarily simple) neg cycle.
    return false;
  }
};
