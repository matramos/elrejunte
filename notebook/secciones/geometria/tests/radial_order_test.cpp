// problem: https://codeforces.com/gym/104373/problem/C 
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i = n-1; i>=0; i--)
#define forall(it,v) for(auto it=v.begin(); it!=v.end(); it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef JP

#else

#endif

using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef long long T;

struct pto {
	ll x,y;
	pto (ll nx = 0LL, ll ny = 0LL): x(nx), y(ny){}
	pto operator+(pto a) { return pto(x+a.x, y+a.y); }
	pto operator-(pto a) { return pto(x-a.x, y-a.y); }
	pto operator*(ll a) { return pto(x*a, y*a); }
	ll operator*(pto a) { return x*a.x+y*a.y; }
	ll operator^(pto a) { return x*a.y-y*a.x; }
};

struct cmp { // radial sort around point O in counter-clockwise direction starting from vector v
	pto o, v;
	cmp (pto no, pto nv) : o(no), v(nv) {}
	bool half(pto p) {
		assert(!(p.x == 0 && p.y == 0)); // (0,0) isn't well defined
		return (v^p) < 0 || ((v^p) == 0 && (v*p) < 0); 
	}
	
	bool operator() (pto & p1, pto & p2) {
		return mp(half(p1-o), T(0)) < mp(half(p2-o), ((p1-o)^(p2-o)));
	}
};


int main(){
	#ifdef JP
		freopen("input.txt", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int t; cin >> t;
	forn (T,t) {
		int n; cin >> n;
		
		vector<pto> ptos(n); ptos.reserve(2*n);
		ll x,y;
		forn (i,n) {
			cin >> x >> y;
			ptos[i] = {x,y};
		}
		
		sort(ptos.begin(), ptos.end(), cmp(pto(0LL,0LL),pto(1LL,0LL)));
		forn(i,n) ptos.pb(ptos[i]);
		
		int ans = n;
		
		pto c = pto(0LL,0LL);
		int r = 0;
		forn(l,n) {
			r = max(r, l);
			while(r < 2*n && r-l<n && ((ptos[l]-c)^(ptos[r]-c)) >= 0LL ) r++;
			ans = min(ans, n-(r-l));
		}
		
		cout << ans << "\n";
	}
	
}
