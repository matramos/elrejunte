// https://codeforces.com/gym/104945/problem/H
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = (a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i = n-1; i>=0; i--)
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

typedef long double T; // double could be faster but less precise
typedef long double ld;
const T EPS = 1e-9; // if T is integer, set to 0
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
	// dot product
	T operator*(pto b){ return x*b.x+y*b.y; }
	// module of cross product, a^b>0 if angle_cw(u,v)<180
	T operator^(pto b){ return x*b.y-y*b.x; }


	// true if this is at the left side of line ab
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>EPS;}
	bool operator<(const pto &b) const {
		return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);
	}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

struct poly{
	vector<pto> pt;
	poly(){}
	poly(vector<pto> pt_) : pt(pt_) {}
	pto centroid(){ // (barycenter, mass center, needs float points)
		int n = sz(pt);
		pto r(0,0); ld t=0;
		forn(i,n) {
			r = r + (pt[i] + pt[(i+1)%n]) * (pt[i] ^ pt[(i+1)%n]);
			t += pt[i] ^ pt[(i+1)%n];
		}
		return r/t/3;
	}
};

struct Event {
	pto p;
	bool in;
};

// radial sort around point O in CCW direction starting from vector v
struct cmp {
	pto o, v;
	cmp (pto no, pto nv) : o(no), v(nv) {}
	bool half(pto p) {
		assert(!(p.x == 0 && p.y == 0)); // (0,0) isn't well defined
		return (v^p) < 0 || ((v^p) == 0 && (v*p) < 0); 
	}
	bool operator() (Event & e1, Event & e2) {
		pto p1 = e1.p;
		pto p2 = e2.p;
		pair<bool, T> a = mp(half(p1-o), T(0));
		pair<bool, T> b = mp(half(p2-o), ((p1-o)^(p2-o)));
		return a < b || (a.fst == b.fst && abs(a.snd-b.snd) <= EPS && e1.in && !e2.in);
	}
};

int main(){
    #ifdef ANARAP
        freopen("input.in","r",stdin);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<pto> v(n);
    forn(i,n)
    {
		int x,y;
		cin >> x >> y;
		v[i] = pto(x,y);
	}
	poly pol(v);
	pto c = pol.centroid();
	bool cisv = false;
	vector<Event> ve;
	pto magic = pto(3.148458566315e10,7.896514896453e10);
	forn(i,n)
	{
		//bool initiallyin = (v[i]-c).left(c, magic);
		//cout << (v[i]-c).x << ' ' << (v[i]-c).y << ' ' << initiallyin << '\n';
		if(c == v[i]) cisv = true;
		else ve.pb({v[i]-c, false}), ve.pb({(v[i]-c)*-1, true});
	}
	cmp comp(pto(0,0), magic);
	sort(ve.begin(), ve.end(), comp);
	ll cnt = cisv;
	forn(i,n) if(!(c == v[i]) && v[i].left(c, magic)) cnt++;
	ll ans = 0;
	//cout << c.x << ' ' << c.y << '\n';
	//cout << cnt << '\n';
	forall(it,ve)
	{
		if(it->in)
		{
			ans += cnt*(cnt-1)/2;
			//cout << it->p.x << ' ' << it->p.y << ' ' << cnt << ' ' << cnt*(cnt-1)/2 << '\n';
			cnt++;
		}
		else
		{
			//cout << "out " << it->p.x << ' ' << it->p.y << '\n';
			cnt--;
		}
	}
	cout << n*(n-1LL)*(n-2)/6-ans << '\n';
    return 0;
}
