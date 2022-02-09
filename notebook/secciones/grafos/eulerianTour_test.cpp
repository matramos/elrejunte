//Problem: https://codeforces.com/contest/1634/problem/E
// ANARAP 💙💛💙
// 💧🙌🏻
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef ANARAP
//prueba
#else
//real
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

map<int,int> f;
vector<vector<int>> mx;


//In a connected graph where all the nodes have even degree
//finds a path that start and finish in the same node (SRC)
// and uses every edge once.
struct EulerianTour {
  int N, M = 0, odd = 0;
  std::vector<std::vector<std::pair<int, int>>> E;
  std::vector<int> deg;
  std::vector<bool> vis;
  EulerianTour(int N) : N(N), E(N), deg(N), vis(N) {}
  void add_edge(int u, int v) {
    int V[2] = {u, v};
    for (auto t : {0, 1}) {
      int v = V[t];
      E[v].emplace_back(V[t ^ 1], M << 1 | t);
      deg[v] += 1;
      odd += (deg[v] % 2 ? +1 : -1);
    }
    ++M;
  }
  // returns eulerian tour by vertices and edges (reversed if first bit is 1)
  pair<vector<int>, vector<int>> find(int src) {
	  //run for every component if graph isn't connected
    assert(odd == 0);
    auto d = deg;
    vector<bool> dead(M, false);
    vector<int> ptr(N, 0), p, e;
    stack<ii> stk;
    stk.emplace(src, -1);
    while (!stk.empty()) {
	  ii aux = stk.top();
	  int u=aux.fst, i = aux.snd;
      vis[u] = true;
      if (d[u] == 0) {
        stk.pop();
        p.push_back(u);
        if (i != -1) e.push_back(i);
      } else {
        for (int& l = ptr[u]; l < deg[u]; ++l) {
          ii aux2 = E[u][l];
          int v=aux2.fst, j=aux2.snd;
          if (!dead[j >> 1]) {
            stk.emplace(v, j);
            --d[u], --d[v], dead[j >> 1] = true;
            break;
          }
        }
      }
    }
    return {p, e};
  }
};


int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
		unsigned t0, t1; t0=clock();
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n; cin >> n;
	vector<ii> edges;
	mx.resize(n);
	forn(i,n){
		int m; cin >> m;
		mx[i].resize(m);
		forn(j,m){
			int v; cin >> v;
			mx[i][j]=v;
			f[v]++;
			edges.pb(mp(v,i));
		}
	}
	int st = n;
	forall(it, f){
		if(it->snd%2){
			cout << "NO\n";
			return 0;
		}
		f[it->fst]=st++;
	}
	forn(i,sz(edges)) edges[i].fst = f[edges[i].fst];
	forn(i,n){
		forn(j,sz(mx[i])){
			mx[i][j] = f[mx[i][j]];
		}
	}
	
	
	EulerianTour et(sz(f)+n);
	forall(it,edges)  et.add_edge(it->fst, it->snd);
	vector<int> did(n,0);
	multiset<ii> used;
	forn(i,n){
		if(did[i] == 0){
			vector<int> path = et.find(i).fst;
			forr(j,1,sz(path)){
				used.insert(mp(path[j-1], path[j]));
				did[path[j-1]]=1;
				j++; 
			}
		}
	}
	cout << "YES\n";
	forn(i,n){
		forn(j,sz(mx[i])){
			auto it = used.lb(mp(i, mx[i][j]));
			if(it!=used.end() && *it == mp(i,mx[i][j])){
				cout << 'R';
				used.erase(it);
			}
			else cout << 'L';
		}
		cout << '\n';
	}
	//~ assert(contR>=cont/2);

	
	
	#ifdef ANARAP
	t1 = clock();double time = (double(t1-t0)/CLOCKS_PER_SEC); cout << "Execution Time: " << time << endl;
	#endif
	return 0;
}


