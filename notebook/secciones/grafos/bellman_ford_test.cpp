// https://codeforces.com/gym/104207/problem/J
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a); i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0; i--)
#define forall(it,v) for(auto it=v.begin(); it!=v.end(); it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef ANARAP

#else 

#endif 

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

const ll INF = 1000100100100100100LL;

//Mas lento que Dijsktra, pero maneja arcos con peso negativo
//
//Can solve systems of "difference inequalities":
//1. for each inequality x_i - x_j <= k add an edge j->i with weight k
//2. create an extra node Z and add an edge Z->i with weigth 0 for
// each variable x_i in the inequalities
//3. run(Z): if negcycle, no solution, otherwise "dist" is a solution
//
//Can transform a graph to get all edges of positive weight
//("Jhonson algorightm"):
//1. Create an extra node Z and add edge Z->i with weight 0 for all
//  nodes i
//2. Run bellman ford from Z
//3. For each original edge a->b (with weight w), change its weigt to
//  be w+dist[a]-dist[b] (where dist is the result of step 2)
//4. The shortest paths in the old and new graph are the same (their
//  weight result may differ, but the paths are the same)
//Note that this doesn't work well with negative cycles, but you can
//identify them before step 3 and then ignore all new weights that
//result in a negative value when executing step 3.
struct BellmanFord {
	vector<vector<ii>> G;//ady. list with pairs (weight, dst)
	vector<ll> dist;
	int N;
	BellmanFord(int n): G(n), N(n) {}
	void addEdge(int a, int b, ll w) { G[a].pb(mp(w, b)); }
	void run(int src){//O(VE)
		dist = vector<ll>(N, INF);
		dist[src] = 0;
		forn(i, N-1) forn(j, N) if(dist[j] != INF) forall(it, G[j])
			dist[it->snd] = min(dist[it->snd], dist[j] + it->fst);
	}

	bool hasNegCycle(){
		forn(j, N) if(dist[j] != INF) forall(it, G[j])
			if(dist[it->snd] > dist[j] + it->fst) return true;
		// inside if: all points reachable from it->snd will have -INF
		// distance. However this is not enough to identify which exact
		// nodes belong to a neg cycle, nor even which can reach a neg
		// cycle. To do so, you need to run SCC (kosaraju) and check
		// whether each SCC hasNegCycle independently. For those that
		// do hasNegCycle, then all of its nodes are part of a (not
		// necessarily simple) neg cycle.
		return false;
	}
};

int main(){
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
	#endif 
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	forn(T,t)
	{
		cout << "Case #" << T+1 << ":";
		int n,m,x;
		cin >> n >> m >> x;
		BellmanFord bf(n+1);
		forn(i,m)
		{
			int a,b,c,d;
			cin >> a >> b >> c >> d;
			if(a==b && c==d)
			{
				bf.addEdge(a,d,x);
				bf.addEdge(d,a,-x);
			}
			else if(a==b)
			{
				bf.addEdge(a,c,x-1);
				bf.addEdge(d,a,-x-1);
			}
			else if(c==d)
			{
				bf.addEdge(b,d,x-1);
				bf.addEdge(d,a,-x-1);
			}
			else
			{
				bf.addEdge(b,c,x-1);
				bf.addEdge(d,a,-x-1);
			}
		}
		forn(i,n) bf.addEdge(0, i+1, 0);
		forr(i,1,n) bf.addEdge(i+1,i,-1);
		bf.run(0);
		if(bf.hasNegCycle()) cout << " IMPOSSIBLE\n";
		else
		{
			forr(i,1,n) cout << ' ' << bf.dist[i+1]-bf.dist[i];
			cout << '\n';
		}
	}
	return 0;
} 
