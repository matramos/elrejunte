// problem: https://codeforces.com/problemset/problem/631/E
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
typedef long long T;
typedef long double ld;
const T EPS = 0; // if T is integer, set to 0
const T INF = 1e18;

struct pto{
	T x, y;
	
	pto() : x(0), y(0) {}
	pto(T _x, T _y) : x(_x), y(_y) {}
	
	pto operator+(pto b){ return pto(x+b.x, y+b.y); }
	pto operator-(pto b){ return pto(x-b.x, y-b.y); }
	pto operator+(T k){ return pto(x+k, y+k); }
	pto operator*(T k){ return pto(x*k, y*k); }
	pto operator/(T k){ return pto(x/k, y/k); }
	
	//dot product
	T operator*(pto b){ return x*b.x+y*b.y; }
	//cross product, a^b>0 if angle_cw(u,v)<180
	T operator^(pto b){ return x*b.y-y*b.x; }
	pto proy(pto b) { return b*((*this)*b)/(b*b); }

	T norm_sq(){ return x*x+y*y; }
	ld norm(){ return sqrtl(x*x+y*y); }
	ld dist(pto b){ return (b-(*this)).norm(); }

	//rotate by theta rads CCW w.r.t. origin (0,0)
	pto rotate(T theta) { return pto(x*cosl(theta)-y*sinl(theta),x*sinl(theta)+y*cosl(theta)); }
	
	// true if this is at the left side of line qr
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>0;}
	bool operator<(const pto &b) const{return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

struct CHT{
	deque<pto> h;
	T f = 1, pos;
	CHT(bool min_=0): f(min_ ? 1 : -1), pos(0){} // min_=1 for min queries
	void add(pto p) { // O(1), pto(m,b) <=> y = mx + b 
		p = p*f;
		if(h.empty()) { h.pb(p); return; }
		
		// p.x should be the lower/greater hull x
		assert(p.x <= h[0].x || p.x >= h.back().x);
		if(p.x <= h[0].x) {
			while(sz(h) > 1 && h[0].left(p,h[1])) h.pop_front(), pos--;
			h.push_front(p); pos++;
		}else{
			while(sz(h) > 1 && h[sz(h)-1].left(h[sz(h)-2], p)) h.pop_back();
			h.pb(p);
		}
		pos = min(max(T(0),pos), T(sz(h)-1));
	}
	T get(T x){ 
		pto q = {x,1};
		// O(log) query for unordered x
		int L = 0,R = sz(h)-1, M;
		while(L < R) {
			M = (L+R)/2;
			if(h[M+1]*q <= h[M]*q) L = M+1;
			else R = M;
		}
		return h[L]*q*f;
		// O(1) query for ordered x
		while(pos > 0 && h[pos-1]*q < h[pos]*q) pos--;
		while(pos < sz(h)-1 && h[pos+1]*q < h[pos]*q) pos++;
		return h[pos]*q*f;
	}
};


ll solve1(vector<ll> &v, vector<ll> &acum)
{
	int n = sz(v);
	CHT cht(1);
	ll ret = 0;
	forr(j,1,n)
	{
		cht.add(pto(-j, acum[j-1]));
		ret = max(ret, acum[j-1] - j*v[j] - cht.get(v[j]));
	}
	return ret;
}

ll solve2(vector<ll> &v, vector<ll> &acum)
{
	int n = sz(v);
	CHT cht;
	ll ret = 0;
	dforn(i,n)
	{
		if(i == 0) break;
		cht.add(pto(i, -acum[i]));
		ret = max(ret, acum[i] - i*v[i] + cht.get(v[i]));
	}
	return ret;
}

int main()
{
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	vector<ll> v(n+1), acum(n+1);
	v[0] = acum[0] = 0;
	ll ans1 = 0;
	forr(i,1,n+1)
	{
		cin >> v[i];
		acum[i] = v[i] + acum[i-1];
		ans1 += i*v[i];
	}
	cout << ans1 + max(solve1(v, acum), solve2(v,acum)) << '\n';
	return 0;
}
