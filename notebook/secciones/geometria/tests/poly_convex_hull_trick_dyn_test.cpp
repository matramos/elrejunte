//https://codeforces.com/group/3qadGzUdR4/contest/101707/problem/I
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

typedef long long T; // double could be faster but less precise
typedef long double ld;
const T EPS = 0; // if T is integer, set to 0
const T INF = 5e18;
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
	// vector projection of this above b
	pto proj(pto b) { return b*((*this)*b)/(b*b); }
	T norm_sq(){ return x*x+y*y; }
	ld norm(){ return sqrtl(x*x+y*y); }
	ld dist(pto b){ return (b-(*this)).norm(); }
	//rotate by theta rads CCW w.r.t. origin (0,0)
	pto rotate(T theta) { 
		return pto(x*cosl(theta)-y*sinl(theta),x*sinl(theta)+y*cosl(theta));
	}
	// true if this is at the left side of line ab
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>=0;}
	bool operator<(const pto &b) const {
		return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);
	}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};
ld angle(pto a, pto o, pto b) {
	pto oa = a-o, ob = b-o;
	return atan2l(oa^ob, oa*ob);
}
ld angle(pto a, pto b) { // smallest angle bewteen a and b
	ld cost = (a*b) / a.norm() / b.norm();
	return acosl(max(ld(-1.), min(ld(1.), cost)));
}


struct poly{
	vector<pto> pt;
	poly(){}
	poly(vector<pto> pt_) : pt(pt_) {}
	pto farthest(pto v) { // O(log(n)) for convex polygons
		if(sz(pt)<10) {
			int k=0;
			forr(i,1,sz(pt)) if(v * (pt[i] - pt[k]) > EPS) k = i;
			return pt[k];
		}
		pt.pb(pt[0]);
		pto a=pt[1] - pt[0];
		int s = 0, e = sz(pt)-1, ua = v*a > EPS;
		if(!ua && v*(pt[sz(pt)-2]-pt[0]) <= EPS){ pt.pop_back(); return pt[0];}
		while(1) {
			int m = (s+e)/2; pto c = pt[m+1]-pt[m];
			int uc = v*c > EPS;
			if(!uc && v*(pt[m-1]-pt[m]) <= EPS){ pt.pop_back(); return pt[m];}
			if(ua && (!uc || v*(pt[s]-pt[m]) > EPS)) e = m;
			else if(ua || uc || v*(pt[s]-pt[m]) >= -EPS) s = m, a = c, ua = uc;
			else e = m;
			assert(e > s+1);
		}
	}
};

// returns convex hull of p in CCW order
// left must return >=0 to delete collinear points
vector<pto> CH(vector<pto>& p) {
	if(sz(p) < 3) return p; // edge case, keep line or point
	vector<pto> ch;
	sort(p.begin(), p.end());
	forn(i, sz(p)) { // lower hull
		while(sz(ch)>=2 && ch[sz(ch)-1].left(ch[sz(ch)-2], p[i])) ch.pop_back();
		ch.pb(p[i]);
	}
	ch.pop_back();
	int k = sz(ch);
	dforn(i, sz(p)) { // upper hull
		while(sz(ch)>=k+2 && ch[sz(ch)-1].left(ch[sz(ch)-2],p[i]))ch.pop_back();
		ch.pb(p[i]);
	}
	ch.pop_back();
	return ch;
}



// Dynamic convex hull trick (based on poly struct)
vector<poly> w;
void add(pto q) { // add(q), O(log^2(n))
	vector<pto> p = {q};
	while(!w.empty() && sz(w.back().pt) < 2*sz(p)){
		for(pto v : w.back().pt) p.pb(v);
		w.pop_back();
	}
	w.pb(poly(CH(p))); // CH = convex hull, must delete collinears
}
T query(pto v) { // max(q*v:q in w), O(log^2(n))
	T r = -INF;
	for(auto& p : w) r = max(r, p.farthest(v)*v);
	return r;
}

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
    forn(i,n) cin >> v[i].x >> v[i].y;
    w.pb(poly(CH(v)));
    int m;
    cin >> m;
    forn(i,m)
    {
		string s;
		int x,y;
		cin >> s >> x >> y;
		if(s == "get") cout << query(pto(x,y)) << '\n';
		else add(pto(x,y));
	}
    return 0;
}
