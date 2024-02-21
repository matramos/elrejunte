// https://codeforces.com/problemset/problem/730/I
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = (a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define    dforn(i,n) for(int i = n-1; i>=0; i--)
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

typedef ll tf;
typedef ll tc;
const tf INF_FLOW = 1e14;
const tc INF_COST = 1e14;
struct edge {
	int u, v;
	tf cap, flow;
	tc cost;
	tf rem() { return cap - flow; }
};
struct MCMF {
	vector<edge> e;
	vector<vector<int>> g;
	vector<tf> vcap;
	vector<tc> dist;
	vector<int> pre;
	tc minCost;
	tf maxFlow;
	// tf wantedFlow; // Use it for fixed flow instead of max flow
	MCMF(int n): g(n), vcap(n), dist(n), pre(n) {}
	void addEdge(int u, int v, tf cap, tc cost) {
		g[u].pb(sz(e)); e.pb({u, v, cap, 0, cost});
		g[v].pb(sz(e)); e.pb({v, u, 0, 0, -cost});
	}
	// O(n*m * min(flow, n*m)), sometimes faster in practice
	void run(int s, int t) { 
		vector<bool> inq(sz(g));
		maxFlow = minCost = 0; // result will be in these variables
		while(1) {
			fill(vcap.begin(), vcap.end(), 0); vcap[s] = INF_FLOW;
			fill(dist.begin(), dist.end(), INF_COST); dist[s] = 0;
			fill(pre.begin(), pre.end(), -1); pre[s] = 0;
			queue<int> q; q.push(s); inq[s] = true;
			while(sz(q)) { // Fast bellman-ford
				int u = q.front(); q.pop(); inq[u] = false;
				for(auto eid : g[u]) {
					edge &E = e[eid];
					if(E.rem() && dist[E.v] > dist[u] + E.cost) {
						dist[E.v] = dist[u] + E.cost;
						pre[E.v] = eid;
						vcap[E.v] = min(vcap[u], E.rem());
						if(!inq[E.v]) q.push(E.v), inq[E.v] = true;
					}
				}
			}
			if (pre[t] == -1) break;
			tf flow = vcap[t];
			// flow = min(flow, wantedFlow - maxFlow); //For fixed flow
			maxFlow += flow;
			minCost += flow*dist[t];
			for (int v = t; v != s; v = e[pre[v]].u) {
				e[pre[v]].flow += flow;
				e[pre[v]^1].flow -= flow;
			}
			// if(maxFlow == wantedFlow) break; //For fixed flow
		}
	}
};

int main(){
    #ifdef ANARAP
        freopen("input.in","r",stdin);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int n,p,s;
	cin >> n >> p >> s;
	MCMF mcmf(n+4);
	int SRC = n+2, SNK = n+3;
	mcmf.addEdge(n, SNK, p, 0);
	mcmf.addEdge(n+1, SNK, s, 0);
	forn(i,n) mcmf.addEdge(SRC, i, 1, 0);
	forn(i,n)
	{
		int x;
		cin >> x;
		mcmf.addEdge(i, n, 1, -x);
	}
	forn(i,n)
	{
		int x;
		cin >> x;
		mcmf.addEdge(i, n+1, 1, -x);
	}
	mcmf.run(SRC, SNK);
	cout << -mcmf.minCost << '\n';
	forall(it, mcmf.e) if(it->v == n && it->u != SNK && it->flow == 1) cout << it->u+1 << ' ';
	cout << '\n';
	forall(it, mcmf.e) if(it->v == n+1 && it->u != SNK && it->flow == 1) cout << it->u+1 << ' ';
	cout << '\n';
    return 0;
}
