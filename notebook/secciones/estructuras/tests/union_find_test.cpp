//Problem: https://codeforces.com/contest/25/problem/D
#include <bits/stdc++.h>
#define sqr(a) ((a)*(a))
#define rsz resize
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second
#define PI 3.1415926535897932384626

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct UnionFind {
	int nsets;
	vector<int> f, setsz; // f[i] = parent of node i
	UnionFind(int n) : nsets(n), f(n, -1), setsz(n, 1) {}
	int comp(int x) { return (f[x] == -1 ? x : f[x]=comp(f[x])); } //O(1)
	bool join(int i,int j) { // returns true if already in the same set
		int a = comp(i), b = comp(j);
		if(a != b) {
			if(setsz[a] > setsz[b]) swap(a,b);
			setsz[b] += setsz[a];
			f[a] = b; // the bigger group (b) now represents the smaller (a)
			nsets--;
		}
		return a == b;
	}
};

int main()
{
	#ifdef REJUNTE
	freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	vector<ii> badEdges;
	cin >> n;
	UnionFind dsu(n);
	forn(i,n-1)
	{
		int a,b;
		cin >> a >> b;
		a--;b--;
		if(dsu.join(a,b)) badEdges.pb(mp(a+1, b+1));
	}
	set<int> representantes;
	forn(i,n) representantes.insert(dsu.comp(i));
	int sum = 0;
	forall(it, representantes) sum += dsu.setsz[*it];
	assert(sum == n);
	assert(dsu.nsets == representantes.size());
	assert(badEdges.size() == representantes.size()-1);
	cout << badEdges.size() << '\n';
	set<int>::iterator ite = representantes.begin();
	forall(it, badEdges)
	{
		cout << it->fst << ' ' << it->snd << ' ' << *ite+1 << ' ' << *next(ite)+1 << '\n';
		ite++;
	}
	return 0;
}
