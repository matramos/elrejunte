// problem: https://open.kattis.com/problems/roberthood
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

typedef long double T;
typedef long double ld;
const T EPS = 1e-9; // if T is integer, set to 0
const T INF = 1e18;

void wassert(bool exp) {
	if(!exp) exit(0);
	return;
}

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
	ld norm(){ return sqrt(x*x+y*y); }
	ld dist(pto b){ return (b-(*this)).norm(); }

	//rotate by theta rads CCW w.r.t. origin (0,0)
	pto rotate(T theta) { return pto(x*cos(theta)-y*sin(theta),x*sin(theta)+y*cos(theta)); }
	
	// true if this is at the left side of line qr
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>0;}
	bool operator<(const pto &b) const{return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

struct poly{
	vector<pto> pt;
	
	poly(){}
	poly(vector<pto> pt_) : pt(pt_) {}
	
	void delete_collinears(){ // delete collinear points
		deque<pto> nxt; int len = 0;
		forn(i,sz(pt)) {
			if(len>1 && abs((pt[i]-pt[len-1])^(pt[len-1]-pt[len-2])) <= EPS) nxt.pop_back(), len--;
			nxt.pb(pt[i]); len++;
		}
		if(len>2 && abs((pt[1]-pt[0])^(pt[0]-pt.back())) <= EPS) nxt.pop_front(), len--;
		pt.clear(); forn(i,sz(nxt)) pt.pb(nxt[i]);
	}
	
	void normalize(){ // |this| should be greater than 2
		delete_collinears();
		if(pt[2].left(pt[0], pt[1])) reverse(pt.begin(), pt.end()); // this makes it clockwise
		int n=sz(pt), pi=0;
		forn(i, n)
			if(pt[i].x<pt[pi].x || (pt[i].x==pt[pi].x && pt[i].y<pt[pi].y))
				pi=i;
		rotate(pt.begin(), pt.begin()+pi, pt.end());
	}
	
	// returns one pair of most distant points
	pair<pto,pto> callipers() { // O(n), for convex  poly, normalize first
		int n = sz(pt);
		if(n<=2) return {pt[0],pt[1%n]};
		pair<pto,pto> ret = {pt[0],pt[1]};
		T maxi = 0; int j = 1;
		forn(i,sz(pt)) {
			while(((pt[(i+1)%n]-pt[i])^(pt[(j+1)%n]-pt[j])) < -EPS) j=(j+1)%sz(pt);
			if(pt[i].dist(pt[j]) > maxi+EPS)
				ret = {pt[i],pt[j]}, maxi = pt[i].dist(pt[j]);
		}
		return ret;
	}
};

vector<pto> CH(vector<pto>& p){
	vector<pto> ch;
	sort(p.begin(), p.end());
	forn(i, sz(p)){ // lower hull
		while(sz(ch)>= 2 && ch[sz(ch)-1].left(ch[sz(ch)-2], p[i])) ch.pop_back();
		ch.pb(p[i]);
	}
	ch.pop_back();
	int k=sz(ch);
	dforn(i, sz(p)){ // upper hull
		while(sz(ch) >= k+2 && ch[sz(ch)-1].left(ch[sz(ch)-2], p[i])) ch.pop_back();
		ch.pb(p[i]);
	}
	ch.pop_back();
	return ch;
}

int main(){
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int c; cin >> c;
	set<pto> s;
	forn(i,c){
		pto p;
		cin >> p.x >> p.y;
		s.insert(p);
	}
	vector<pto> pts;
	forall(it,s) pts.pb(*it);
	
	if(sz(pts)<=2) {
		cout << fixed << setprecision(9) << pts[0].dist(pts[1%sz(pts)]) << "\n";
		return 0;
	}
	
	poly pol(CH(pts));
	if(sz(pol.pt)<=2) {
		cout << fixed << setprecision(9) << pol.pt[0].dist(pol.pt[1%sz(pol.pt)]) << "\n";
		return 0;
	}
	
	pol.normalize();
	pair<pto,pto> ans = pol.callipers();
	cout << fixed << setprecision(9) << ans.fst.dist(ans.snd) << "\n";
	
	
	#ifdef JP
		cerr << "Time elapsed: " <<  clock() * 1000 / CLOCKS_PER_SEC << " ms\n";
	#endif
}
