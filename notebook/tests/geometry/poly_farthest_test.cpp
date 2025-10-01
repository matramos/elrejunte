// https://codeforces.com/gym/104945/problem/G
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = (a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define    dforn(i,n) for(int i = n-1; i>=0; i--)
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
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>0;}
	bool left2(pto a, pto b){return ((a-*this)^(b-*this))>=0;}
	bool operator<(const pto &b) const {
		return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);
	}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

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

// returns convex hull of p in CCW order
// left must return >=0 to delete collinear points
vector<pto> CH2(vector<pto>& p) {
	vector<pto> ch;
	sort(p.begin(), p.end());
	forn(i, sz(p)) { // lower hull
		while(sz(ch)>=2 && ch[sz(ch)-1].left2(ch[sz(ch)-2], p[i])) ch.pop_back();
		ch.pb(p[i]);
	}
	ch.pop_back();
	int k = sz(ch);
	dforn(i, sz(p)) { // upper hull
		while(sz(ch)>=k+2 && ch[sz(ch)-1].left2(ch[sz(ch)-2],p[i]))ch.pop_back();
		ch.pb(p[i]);
	}
	ch.pop_back();
	return ch;
}

pto normalize(pto p)
{
	if(p == pto(0,0)) return p;
	if(p.x == 0) return pto(0, p.y/abs(p.y));
	if(p.y == 0) return pto(p.x/abs(p.x), 0);
	int aux = __gcd(abs(p.x), abs(p.y));
	return pto(p.x/aux, p.y/aux);
}

int main(){
    #ifdef ANARAP
        freopen("input.in","r",stdin);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,m;
    cin >> n >> m;
    vector<pto> v(n);
    forn(i,n) cin >> v[i].x >> v[i].y;
    map<pto,int> mm;
    
    forn(i,n) mm[v[i]] = i;
    vector<pto> vwith = CH(v);
    vector<pto> vwithout = CH2(v);
    int posw = 0;
    map<pto, map<pto, int>> mvec;
    forn(i,sz(vwithout))
    {
		assert(vwith[posw] == vwithout[i]);
		pto a = vwith[posw];
		int best = mm[vwith[posw]];
		while(!(vwith[posw] == vwithout[(i+1)%sz(vwithout)]))
		{
			posw = (posw+1)%sz(vwith);
			best = min(best, mm[vwith[posw]]);
		}
		pto b = vwith[posw];
		mvec[a][normalize(b-a)] = best;
		mvec[b][normalize(a-b)] = best;
	}
    poly pol(CH(vwithout));
    forn(i,m)
    {
		pto p;
		cin >> p.x >> p.y;
		pto pf = pol.farthest(p);
		int ans = mm[pf];
		p = normalize(pto(-p.y, p.x));
		if(mvec[pf].count(p)) ans = min(ans, mvec[pf][p]);
		p = normalize(p*-1);
		if(mvec[pf].count(p)) ans = min(ans, mvec[pf][p]);
		cout << 1+ans << '\n';
	}
    return 0;
}
