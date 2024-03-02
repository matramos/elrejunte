// https://codeforces.com/group/AOLjpHeTiB/contest/496424/problem/C
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = a; i<b; i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i = n-1; i>-1; i--)
#define forall(i,v) for(auto i = v.begin(); i != v.end(); i++)
#define sz(v) ((int) v.size()) 
#define pb push_back
#define fst first
#define snd second
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef ll T; // double could be faster but less precise
typedef long double ld;
const T EPS = 0; // if T is integer, set to 0
const T INF = 1e18;

struct pto{
	T x, y; int u, v, id;
	pto() : x(0), y(0) {}
	pto(T _x, T _y) : x(_x), y(_y) {}
	pto operator+(pto b){ return pto(x+b.x, y+b.y); }
	pto operator-(pto b){ return pto(x-b.x, y-b.y); }
	pto operator+(T k){ return pto(x+k, y+k); }
	pto operator*(T k){ return pto(x*k, y*k); }
	pto operator/(T k){ return pto(x/k, y/k); }
	// dot product
	T operator*(pto b){ return x*b.x+y*b.y; }
	// module of cross product, a^b>0 if angle_cw(u,v)<180
	T operator^(pto b){ return x*b.y-y*b.x; }
	// vector projection of this above b
	pto proj(pto b) { return b*((*this)*b)/(b*b); }
	T norm_sq(){ return x*x+y*y; }
	ld norm(){ return sqrtl(x*x+y*y); }
	ld dist(pto b){ return (b-(*this)).norm(); }
	// true if this is at the left side of line ab
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>0;}
	bool operator<(const pto &b) const {
		return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);
	}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

struct cmp {
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

void print_ans(pto a1, pto a2, pto a3) {
	cout << "Yes\n";
	cout << a1.x << " " << a1.y << "\n";
	cout << a2.x << " " << a2.y << "\n";
	cout << a3.x << " " << a3.y << "\n";
} 

bool solve_down (ll r, vector<pto> &pts, pto u, pto v, ll x, pto &ans) {
	ll l = 0;
	while(l<r) {
		ll m = (l+r)/2;
		
		if(abs((u-v)^(pts[m]-v)) > 2LL*x) l = m+1;
		else r = m; 
	}
	
	if(abs((u-v)^(pts[l]-v)) == 2LL*x) {
		ans = pts[l];
		return true;
	}
	
	return false;
}

struct all_point_pairs {
	vector<pto> pt, ev; 
	vector<int> idx;
	int cur_step;
	
	all_point_pairs(vector<pto> pt_): pt(pt_) { 
		idx = vector<int>(sz(pt));
		forn(i,sz(pt)) forn(j,sz(pt)) if(i!=j) { 
			pto p = pt[j]-pt[i]; p.u = pt[i].id, p.v = pt[j].id; ev.pb(p); 
		}
		sort(ev.begin(),ev.end(),cmp(pto(0,0),pto(1,0))); 
		pto start(ev[0].y,-ev[0].x); 
		sort(pt.begin(), pt.end(), [&](pto &u, pto &v) { return u*start < v*start; });
		forn(i,sz(idx)) idx[pt[i].id] = i;
		cur_step = 0;
	}
	
	bool step() {
		if(cur_step>=sz(ev)) return false;
		int u = ev[cur_step].u, v = ev[cur_step].v;
		swap(pt[idx[u]],pt[idx[v]]);
		swap(idx[u],idx[v]);
		cur_step++;
		return true;
	}
	
};

int main () {
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	ll n, s; cin >> n >> s;
	vector<pto> pts(n);
	forn(i,n){
		cin >> pts[i].x >> pts[i].y;
		pts[i].id = i;
	}
	
	all_point_pairs app(pts); pto ans;
	while(app.step()){
		int u = app.idx[app.ev[app.cur_step-1].u] , v = app.idx[app.ev[app.cur_step-1].v];
		if(solve_down(u, app.pt, app.pt[u], app.pt[v], s, ans)){
			print_ans(ans, app.pt[u], app.pt[v]);
			return 0;
		}
	} 
	
	cout << "No\n";
	
	#ifdef JP
		cerr << "Time elapsed: " <<  clock() * 1000 / CLOCKS_PER_SEC << " ms\n";
	#endif
}

