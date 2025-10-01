// https://codeforces.com/gym/104945/problem/B
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = (a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define    dforn(i,n) for(int i = n-1; i>=0; i++)
#define forall(it,v) for(auto it = v.begin(); it != v.end(); it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound 
#define up upper_bound
#define fst first
#define snd second

#ifdef ANARAP

#else

#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

const int INF = 200;

struct Edge {
  int u, v;
  ll cap, flow;
  Edge() {}
  Edge(int uu, int vv, ll c) : u(uu), v(vv), cap(c), flow(0) {}
};
struct Dinic {
  int N;
  vector<Edge> E;
  vector<vector<int>> g;
  vector<int> d, pt;
  Dinic(int n) : N(n), g(n), d(n), pt(n) {}  // clear and init
  void addEdge(int u, int v, ll cap) {
    if (u != v) {
      g[u].pb(sz(E));
      E.pb({u, v, cap});
      g[v].pb(sz(E));
      E.pb({v, u, 0});
    }
  }
  bool BFS(int S, int T) {
    queue<int> q({S});
    fill(d.begin(), d.end(), N + 1);
    d[S] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == T) break;
      for (int k : g[u]) {
        Edge& e = E[k];
        if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
          d[e.v] = d[e.u] + 1;
          q.push(e.v);
        }
      }
    }
    return d[T] != N + 1;
  }
  ll DFS(int u, int T, ll flow = -1) {
    if (u == T || flow == 0) return flow;
    for (int& i = pt[u]; i < sz(g[u]); ++i) {
      Edge& e = E[g[u][i]];
      Edge& oe = E[g[u][i] ^ 1];
      if (d[e.v] == d[e.u] + 1) {
        ll amt = e.cap - e.flow;
        if (flow != -1 && amt > flow) amt = flow;
        if (ll pushed = DFS(e.v, T, amt)) {
          e.flow += pushed;
          oe.flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }
  ll maxFlow(int S, int T) {  // O(V^2*E), unit nets: O(sqrt(V)*E)
    ll total = 0;
    while (BFS(S, T)) {
      fill(pt.begin(), pt.end(), 0);
      while (ll flow = DFS(S, T)) total += flow;
    }
    return total;
  }
};
// Dinic wrapper to allow setting demands of min flow on edges
// If an edge with a min flow demand is part of a cycle, then the result
// is not guaranteed to be correct, it could result in false positives
struct DinicWithDemands {
  int N;
  vector<pair<Edge, ll>> E;  // (normal dinic edge, min flow)
  Dinic dinic;
  DinicWithDemands(int n) : N(n), E(0), dinic(n + 2) {}
  void addEdge(int u, int v, ll cap, ll minFlow) {
    assert(minFlow <= cap);
    if (u != v) E.pb(mp(Edge(u, v, cap), minFlow));
  }
  ll maxFlow(int S, int T) {  // Same complexity as normal Dinic
    int SRC = N, SNK = N + 1;
    ll minFlowSum = 0;
    forall(e, E) {  // force the min flow
      minFlowSum += e->snd;
      dinic.addEdge(SRC, e->fst.v, e->snd);
      dinic.addEdge(e->fst.u, SNK, e->snd);
      dinic.addEdge(e->fst.u, e->fst.v, e->fst.cap - e->snd);
    }
    dinic.addEdge(T, S, INF);  // INF >= max possible flow
    ll flow = dinic.maxFlow(SRC, SNK);
    if (flow < minFlowSum) return -1;  // no valid flow exists
    assert(flow == minFlowSum);
    // Now go back to the original network, to a valid
    // state where all min flow values are satisfied.
    forn(i, sz(E)) {
      forn(j, 4) {
        assert(j % 2 || dinic.E[6 * i + j].flow == E[i].snd);
        dinic.E[6 * i + j].cap = dinic.E[6 * i + j].flow = 0;
      }
      dinic.E[6 * i + 4].cap += E[i].snd;
      dinic.E[6 * i + 4].flow += E[i].snd;
      // don't change edge [6*i+5] to keep forcing the mins
    }
    forn(i, 2) dinic.E[6 * sz(E) + i].cap = dinic.E[6 * sz(E) + i].flow = 0;
    // Just finish the maxFlow now
    dinic.maxFlow(S, T);
    flow = 0;  // get the result manually
    forall(e, dinic.g[S]) flow += dinic.E[*e].flow;
    return flow;
  }
};


int main(){
    #ifdef ANARAP
        freopen("input.in","r",stdin);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,m;
    cin >> n >> m;
    Dinic flow(n+m+2);
    int SRC = n+m, SNK = n+m+1;
    forn(i,n) flow.addEdge(SRC, i, 1);
    forn(i,m) flow.addEdge(n+i, SNK, 1);
    forn(i,n)
    {
		int k;
		cin >> k;
		forn(_,k)
		{
			int x;
			cin >> x;
			x--;
			flow.addEdge(i, n+x, INF);
		}
	}
	cout << flow.maxFlow(SRC, SNK) << '\n';
    return 0;
}
