// problem: https://codeforces.com/gym/104252/problem/G
#include <bits/stdc++.h>
#define dbg(x) cerr<<#x<<"="<<(x)<<endl;
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
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef long long T;
typedef long double ld;
const T EPS = 0;
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

struct poly{
	vector<pto> pt;
	
	poly(){}
	poly(vector<pto> pt_) : pt(pt_) {}
	
	poly operator*(T k) {
		poly ret = (*this);
		forn(i,sz(ret.pt)) ret.pt[i] = ret.pt[i]*k;
		return ret;
	}
	
	void normalize(){ // delete collinear points first
		// this makes it clockwise
		if(pt[2].left(pt[0], pt[1])) reverse(pt.begin(), pt.end());
		int n=sz(pt), pi=0;
		forn(i, n)
			if(pt[i].x<pt[pi].x || (pt[i].x==pt[pi].x && pt[i].y<pt[pi].y))
				pi=i;
		rotate(pt.begin(), pt.begin()+pi, pt.end());
	}
	
	bool inside_convex(pto p){ // normalize first
		if(p.left(pt[0], pt[1]) || p.left(pt[sz(pt)-1], pt[0])) return false;
		int a=1, b=sz(pt)-1;
		while(b-a>1){
			int c=(a+b)/2;
			if(!p.left(pt[0], pt[c])) a=c;
			else b=c;
		}
		return !p.left(pt[a], pt[a+1]);
	}

	poly minkowski(poly p) {
		this->normalize(); p.normalize();
		vector<pto> a = (*this).pt, b = p.pt;
		a.pb(a[0]); a.pb(a[1]);
		b.pb(b[0]); b.pb(b[1]);
		vector<pto> sum;
		int i = 0, j = 0;
		while(i<sz(a)-2 || j<sz(b)-2) {
			sum.pb(a[i]+b[j]);
			T cross = (a[i+1]-a[i])^(b[j+1]-b[j]);
			if(cross <= 0 && i < sz(a)-2) i++;
			if(cross >= 0 && j < sz(b)-2) j++;
		}
		return poly(sum);
	}
	
};

int main()
{
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int m1; cin >> m1;
	vector<pto> pa(m1);
	forn(i,m1) cin >> pa[i].x >> pa[i].y;
	
	int m2; cin >> m2;
	vector<pto> pb(m2);
	forn(i,m2) cin >> pb[i].x >> pb[i].y; 
	
	poly a = poly(pa), b=poly(pb);
	
	vector<poly> minkowski;
	int k1[3] = {1,2,-1};
	int k2[3] = {1,-1,2};
	int k3[3] = {2,1,1};
	forn(i,3){
		minkowski.pb((a*k1[i]).minkowski(b*k2[i]));
	}
	
	int n; cin >> n;
	forn(i,n){
		pto q; cin >> q.x >> q.y;
		bool ok = false;
		forn(j,3) ok |= minkowski[j].inside_convex(q*k3[j]);
		cout << (ok ? "Y" : "N");
	}
	cout << "\n";
	
	return 0;
}
