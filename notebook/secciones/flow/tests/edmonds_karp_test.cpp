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

struct EdmondsKarp {
  int N;
  vector<unordered_map<int, ll>> g;
  vector<int> p;
  ll f;
  EdmondsKarp(int n) : N(n), g(n), p(n) {}
  void addEdge(int a, int b, int w) { g[a][b] = w; }
  void augment(int v, int SRC, ll minE) {
    if (v == SRC) f = minE;
    else if (p[v] != -1) {
      augment(p[v], SRC, min(minE, g[p[v]][v]));
      g[p[v]][v] -= f, g[v][p[v]] += f;
    }
  }
  ll maxflow(int SRC, int SNK) {  // O(min(VE^2,Mf*E))
    ll ret = 0;
    do {
      queue<int> q;
      q.push(SRC);
      fill(p.begin(), p.end(), -1);
      f = 0;
      while (sz(q)) {
        int node = q.front();
        q.pop();
        if (node == SNK) break;
        forall(it, g[node]) if (it->snd > 0 && p[it->fst] == -1) {
          q.push(it->fst), p[it->fst] = node;
        }
      }
      augment(SNK, SRC, INF);  // INF > max possible flow
      ret += f;
    } while (f);
    return ret;
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
    EdmondsKarp flow(n+m+2);
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
	cout << flow.maxflow(SRC, SNK) << '\n';
    return 0;
}
