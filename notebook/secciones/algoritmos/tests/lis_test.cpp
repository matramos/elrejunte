// https://cses.fi/problemset/task/1145
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = a; i<b; i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i = n-1; i>-1; i--)
#define forall(i,v) for(auto i = v.begin(); i != v.end(); i++)
#define sz(v) ((int) v.size())
#define all(v) v.begin(), v.end()
#define rsz resize 
#define pb push_back
#define fst first
#define snd second
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef long long T;

// Change comparisons and binary search for non-increasing
// Given an array, paint it in the least number of colors so that each
// color turns to a non-increasing subsequence. Solution: Min number of
// colors=Length of the longest increasing subsequence
struct lis {
	T INF;
	int n; vector<T> a; // secuencia y su longitud
	vector<pair<T,int>> d; // d[i]=ultimo valor de la subsecuencia de tamanio i
	vector<int> p; // padres
	vector<T> ret; // respuesta
	
	lis(T INF_, vector<T> &a_) {
		n = sz(a_);
		INF = INF_;
		a = a_;
		d.resize(n+1);
		p.resize(n+1);
	}
	void rec(int i) {
		if(i == -1) return;
		ret.push_back(a[i]);
		rec(p[i]);
	}
	int run() {
		d[0] = {-INF,-1};
		forn(i,n) d[i+1] = {INF, -1};
		forn(i,n) {
			int j = int(upper_bound(d.begin(), d.end(), mp(a[i], n))-d.begin());
			if(d[j-1].fst<a[i] && a[i]<d[j].fst) {
				p[i] = d[j-1].snd;
				d[j] = {a[i], i};
			}
		}
		ret.clear();
		dforn(i, n+1) if(d[i].fst!=INF) {
			rec(d[i].snd);  // reconstruir
			reverse(ret.begin(), ret.end());
			return i;  // longitud
		}
		return 0;
	}
};

int main () {
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n; cin >> n;
    vector<T> a(n); forn(i,n) cin >> a[i];
    lis l(1e10, a);
    cout << l.run() << "\n";
	
	#ifdef JP
		cerr << "Time elapsed: " <<  clock() * 1000 / CLOCKS_PER_SEC << " ms\n";
	#endif
}
