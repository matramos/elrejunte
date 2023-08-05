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
//Can solve systems of "difference inequalities":
//1. for each inequality x_i - x_j <= k add an edge j->i with weight k
//2. create an extra node Z and add an edge Z->i with weigth 0 for
// each variable x_i in the inequalities
//3. run(Z): if negcycle, no solution, otherwise "dist" is a solution
struct BellmanFord {
	vector<vector<ii>> G;//ady. list with pairs (weight, dst)
	vector<ll> dist;
	int N;
	BellmanFord(int n) { N = n; G.rsz(n); dist.rsz(n); }
	void addEdge(int a, int b, long long w) { G[a].pb(mp(w, b)); }
	void run(int src){//O(VE)
		dist[src] = 0;
		forn(i, N-1) forn(j, N) if(dist[j] != INF) forall(it, G[j])
			dist[it->snd] = min(dist[it->snd], dist[j] + it->fst);
	}

	bool hasNegCycle(){
		forn(j, N) if(dist[j] != INF) forall(it, G[j])
			if(dist[it->snd] > dist[j] + it->fst) return true;
		//inside if: all points reachable from it->snd will have -INF distance(do bfs)
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
