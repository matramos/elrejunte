//Problem: https://codeforces.com/contest/1416/problem/D
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
#else
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

struct dsu_save {
    int v, rnkv, u, rnku;

    dsu_save() {}

    dsu_save(int _v, int _rnkv, int _u, int _rnku)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};

struct dsu_with_rollbacks {
    vector<int> p, rnk;
    vector<set<ii>> vs;
    vector<bool> used;
    int comps;
    stack<dsu_save> op;

    dsu_with_rollbacks() {}

    dsu_with_rollbacks(int n, vector<int> &v) {
        p.resize(n);
        rnk.resize(n);
        vs.rsz(n);
        used.rsz(n, false);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            rnk[i] = 0;
            vs[i].insert(mp(v[i], i));
        }
        comps = n;
    }

    int find_set(int v) {
        return (v == p[v]) ? v : find_set(p[v]);
    }

    bool unite(int v, int u) {
        v = find_set(v);
        u = find_set(u);
        if (v == u)
            return false;
        comps--;
        if (rnk[v] > rnk[u])
            swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        forall(it, vs[v]) vs[u].insert(*it);
        if (rnk[u] == rnk[v])
            rnk[u]++;
        return true;
    }

    void rollback() {
        if (op.empty())
            return;
        dsu_save x = op.top();
        op.pop();
        comps++;
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
        forall(it, vs[x.v]) vs[x.u].erase(*it);
    }
    
    int solve(int x) {
		x = find_set(x);
		while(!vs[x].empty() && used[vs[x].rbegin()->snd]) vs[x].erase(prev(vs[x].end()));
		if(vs[x].empty()) return 0;
		int ans = vs[x].rbegin()->fst;
		used[vs[x].rbegin()->snd] = true;
		return ans;
	}
};


int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m,q;
	cin >> n >> m >> q;
	vector<int> v(n);
	vector<ii> edges(m);
	vector<bool> deleted(m, false);
	vector<bool> doRollback(q, false);
	vector<ii> queries(q);
	forn(i,n) cin >> v[i];
	forn(i,m)
	{
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[i] = mp(a,b);
	}
	forn(i,q)
	{
		int t,x;
		cin >> t >> x;
		x--;
		queries[i] = mp(t,x);
		if(t == 2) deleted[x] = true;
	}
	dsu_with_rollbacks dsu(n, v);
	forn(i,m) if(!deleted[i]) dsu.unite(edges[i].fst, edges[i].snd);
	dforn(i,q)
	{
		int t = queries[i].fst, x = queries[i].snd;
		if(t == 2 && dsu.unite(edges[x].fst, edges[x].snd))
		{
			doRollback[i] = true;
			//cout << "should rollback: " << edges[x].fst << ' ' << edges[x].snd << '\n';
		}
	}
	/*forn(i,n)
	{
		cout << i+1 << ' ' << dsu.find_set(i) << ": ";
		forall(it, dsu.vs[dsu.find_set(i)]) cout << it->fst << ' ';
		cout << '\n';
	}*/
	forn(i,q)
	{
		int t = queries[i].fst, x = queries[i].snd;
		if(t == 2)
		{
			if(doRollback[i])
			{
				//cout << "rolled back: " << edges[x].fst << ' ' << edges[x].snd << '\n';
				dsu.rollback();
			}
		}
		else
		{
			//cout << "ans: ";
			cout << dsu.solve(x) << '\n';
		}
		/*forn(i,n)
		{
			cout << i+1 << ' ' << dsu.find_set(i) << ": ";
			forall(it, dsu.vs[dsu.find_set(i)]) cout << it->fst << ' ';
			cout << '\n';
		}*/
	}
	return 0;
}