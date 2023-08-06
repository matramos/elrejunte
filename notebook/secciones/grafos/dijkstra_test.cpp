// https://codeforces.com/problemset/problem/20/C
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
//local
#else
//judge
#endif

using namespace std;

typedef long long ll;
typedef pair<ll,int> ii;

const ll INF = 1e12;

struct Dijkstra {
	vector<vector<ii>> G;//ady. list with pairs (weight, dst)
	vector<ll> dist;
	vector<int> vp; // for path reconstruction (parent of each node)
	int N;
	Dijkstra(int n): G(n), N(n) {}
	void addEdge(int a, int b, ll w) { G[a].pb(mp(w, b)); }
	void run(int src) { //O(|E| log |V|)
		dist = vector<ll>(N, INF);
		vp = vector<int>(N, -1);
		priority_queue<ii, vector<ii>, greater<ii>> Q;
		Q.push(make_pair(0, src)); dist[src] = 0;
		while(sz(Q)) {
			int node = Q.top().snd;
			ll d = Q.top().fst;
			Q.pop();
			if(d > dist[node]) continue;
			forall(it, G[node]) if(d + it->fst < dist[it->snd]) {
				dist[it->snd] = d + it->fst;
				vp[it->snd] = node;
				Q.push(mp(dist[it->snd], it->snd));
			}
		}
	}
};


int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m;
	cin >> n >> m;
	Dijkstra djk(n);
	forn(_,m)
	{
		int a,b,w;
		cin >> a >> b >> w;
		a--;b--;
		djk.addEdge(a,b,w);
		djk.addEdge(b,a,w);
	}
	djk.run(0);
	if(djk.dist[n-1] == INF) cout << "-1\n";
	else
	{
		vector<int> path;
		int node = n-1;
		while(node != -1)
		{
			path.pb(node);
			node = djk.vp[node];
		}
		dforn(i,sz(path)) cout << path[i]+1 << ' ';
		cout << '\n';
	}
	return 0;
}
