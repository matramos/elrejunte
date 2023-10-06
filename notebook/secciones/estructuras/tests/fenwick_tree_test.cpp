// https://codeforces.com/contest/597/problem/C
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
typedef pair<int,int> ii;

typedef ll tipo;

struct FenwickTree {
	int N;
	// Could be useful to replace for unordered_map when "many 0s"
	vector<tipo> ft; // for more dimensions, make ft multi-dimensional
	FenwickTree(int n): N(n), ft(n+1) {}
	void upd(int i0, tipo v) { // add v to i0th element (0-based)
		// add extra fors for more dimensions
		for(int i = i0+1; i <= N; i += i&-i) ft[i] += v;
	}
	tipo get(int i0) { // get sum of range [0,i0)
		tipo r = 0;
		// add extra fors for more dimensions
		for(int i = i0; i; i -= i&-i) r += ft[i];
		return r;
	}
	tipo get_sum(int i0, int i1) { // get sum of range [i0,i1) (0-based)
		return get(i1) - get(i0);
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
	int n,k;
	cin >> n >> k;
	k++;
	vector<FenwickTree> v(k+1, FenwickTree(n+1));
	v[0].upd(0,1);
	forn(i,n)
	{
		int x;
		cin >> x;
		dforn(j,k) v[j+1].upd(x, v[j].get_sum(0,x));
	}
	cout << v[k].get_sum(0, n+1) << '\n';
	return 0;
}
