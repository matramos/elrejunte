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

struct UnionFind{
	vector<int> f, setSize; //the array f contains the parent of each node
	int cantSets;
	void init(int n)
	{
		f.clear(); setSize.clear();
		cantSets = n;
		f.rsz(n, -1);
		setSize.rsz(n, 1);
	}
	int comp(int x) {return (f[x]==-1? x : f[x]=comp(f[x]));}//O(1)
	bool join(int i,int j) //devuelve true si ya estaban juntos
	{
		int a = comp(i), b = comp(j);
		if(a != b)
		{
			cantSets--;
			if(setSize[a] > setSize[b]) swap(a,b);
			setSize[b] += setSize[a];
			f[a] = b; //el grupo mas grande (b) pasa a representar al mas chico (a)
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
	UnionFind dsu;
	cin >> n;
	dsu.init(n);
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
	forall(it, representantes) sum += dsu.setSize[*it];
	assert(sum == n);
	assert(dsu.cantSets == representantes.size());
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