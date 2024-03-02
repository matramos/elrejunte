// https://codeforces.com/problemset/problem/799/G
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

typedef double T; // double could be faster but less precise
typedef double ld;
const T EPS = 1e-11; // if T is integer, set to 0
const T INF = 1e18;
const T pi = acos(ld(-1.0));

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
	ld norm(){ return sqrt(x*x+y*y); }
	ld dist(pto b){ return (b-(*this)).norm(); }
	//rotate by theta rads CCW w.r.t. origin (0,0)
	pto rotate(T theta) { 
		return pto(x*cos(theta)-y*sin(theta),x*sin(theta)+y*cos(theta));
	}
	// true if this is at the left side of line ab
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>EPS;}
	bool operator<(const pto &b) const {
		return x<b.x-EPS || (fabs(x-b.x)<=EPS && y<b.y-EPS);
	}
	bool operator==(pto b){return fabs(x-b.x)<=EPS && fabs(y-b.y)<=EPS;}
};
ld angle(pto a, pto o, pto b) {
	pto oa = a-o, ob = b-o;
	T ret = atan2(oa^ob, oa*ob);
	return ret < 0 ? ret + ld(2)*pi : ret;
}

int sgn(T x){return x<0? -1 : !!x;}
struct line{
	T a,b,c; // Ax+By=C
	line() {}
	line(T a_, T b_, T c_):a(a_),b(b_),c(c_){}
	// TO DO: check negative C (multiply everything by -1)
	line(pto u, pto v): a(v.y-u.y), b(u.x-v.x), c(a*u.x+b*u.y) {}
	int side(pto v){return sgn(a*v.x + b*v.y - c);}
	bool inside(pto v){ return fabs(a*v.x + b*v.y - c) <= EPS; }
	bool parallel(line v){return fabs(a*v.b-v.a*b) <= EPS;}
	pto inter(line v){
		T det=a*v.b-v.a*b;
		if(fabs(det)<=EPS) return pto(INF, INF);
		return pto(v.b*c-b*v.c, a*v.c-v.a*c)/det;
	}
};

struct poly{
	vector<pto> pt;
	poly(){}
	poly(vector<pto> pt_) : pt(pt_) {}
	void delete_collinears() { // delete collinear points
		deque<pto> nxt; int len = 0;
		forn(i,sz(pt)) {
			if(len>1 && abs((pt[i]-nxt[len-2])^(nxt[len-1]-nxt[len-2])) <= EPS)
				nxt.pop_back(), len--; 
			nxt.pb(pt[i]); len++;
		}
		if(len>2 && abs((nxt[1]-nxt[len-1])^(nxt[0]-nxt[len-1])) <= EPS) 
			nxt.pop_front(), len--;
		if(len>2 && abs((nxt[len-1]-nxt[len-2])^(nxt[0]-nxt[len-2])) <= EPS)
			nxt.pop_back(), len--;
		pt.clear(); forn(i,sz(nxt)) pt.pb(nxt[i]);
	}
	void normalize() {
		delete_collinears();
		if(pt[2].left(pt[0], pt[1])) reverse(pt.begin(), pt.end()); //make it CW
		int n = sz(pt), p = 0;
		forn(i, n)
			if(pt[i].x<pt[p].x || (pt[i].x==pt[p].x && pt[i].y<pt[p].y))
				p = i;
		rotate(pt.begin(), pt.begin()+p, pt.end());
	}
	int farthest(pto v) { // O(log(n)) for convex polygons
		if(sz(pt)<10) {
			int k=0;
			forr(i,1,sz(pt)) if(v * (pt[i] - pt[k]) > EPS) k = i;
			return k;
		}
		pt.pb(pt[0]);
		pto a=pt[1] - pt[0];
		int s = 0, e = sz(pt)-1, ua = v*a > EPS;
		if(!ua && v*(pt[sz(pt)-2]-pt[0]) <= EPS){ pt.pop_back(); return 0;}
		while(1) {
			int m = (s+e)/2; pto c = pt[m+1]-pt[m];
			int uc = v*c > EPS;
			if(!uc && v*(pt[m-1]-pt[m]) <= EPS){ pt.pop_back(); return m;}
			if(ua && (!uc || v*(pt[s]-pt[m]) > EPS)) e = m;
			else if(ua || uc || v*(pt[s]-pt[m]) >= -EPS) s = m, a = c, ua = uc;
			else e = m;
			assert(e > s+1);
		}
	}
	ii cut(pto u, pto v) { 
		int n = sz(pt); pto dir = v-u;
		int L = farthest(pto(dir.y,-dir.x));
		int R = farthest(pto(-dir.y,dir.x));
		if(!pt[L].left(u,v)) swap(L,R);
		if(!pt[L].left(u,v)) return mp(-1,-1); // line doesn't cut the poly
		
		ii ans;
		int l = L, r = L > R ? R+n : R;
		while(l<r) {
			int med = (l+r+1)/2;
			if(pt[med >= n ? med-n : med].left(u,v)) l = med;
			else r = med-1;
		}
		ans.snd = l >= n ? l-n : l;
		
		l = R, r = L < R ? L+n : L;
		while(l<r) {
			int med = (l+r)/2;
			if(!pt[med >= n ? med-n : med].left(u,v)) l = med+1;
			else r = med;
		}
		ans.fst = l >= n ? l-n : l;
		
		return ans;
	}
};

T f(vector<pto> &pt, poly &pol, const vector<T> &pre, pto q, const T &ang) {
	pto dir = (pt[0]-q).rotate(ang);
	pto rotated = q + dir;
	line cut(q, rotated);
	
	int lpol,rpol;
	tie(lpol,rpol) = pol.cut(q,rotated);
	lpol = sz(pt)-lpol-1;
	rpol = sz(pt)-rpol-1;
	swap(lpol,rpol);
	
	T area = 0;
	if(lpol>rpol) area +=  pre.back()-pre[lpol+1]+pre[rpol+1];
	else area += pre[rpol+1]-pre[lpol+1];
	pto ini = cut.inter(line(pt[lpol], pt[lpol-1 < 0 ? lpol-1+sz(pt) : lpol-1]));
	pto end = cut.inter(line(pt[rpol], pt[rpol+1 == sz(pt) ? 0 : rpol+1]));
	area += pt[rpol]^end;
	area += ini^pt[lpol];
	area += end^ini;
	area = fabs(area)/ld(2.0);
	return area;
}

int main () {
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, q; cin >> n >> q;
	vector<pto> pt(n); 
	forn(i,n){
		int x,y; cin >> x >> y;
		pt[i].x = x;
		pt[i].y = y;
	}
	poly pol(pt); reverse(pt.begin(),pt.end());
	vector<T> pre(n+1); forn(i,n) pre[i+1] = pre[i] + (pt[(i-1+n)%n]^pt[i]);
	
	T area = fabs(pre.back())/ld(4.);
	forn(qq,q) { 
		int x,y; cin >> x >> y; pto query(x,y);
		T l = 0, r = pi;
		if(f(pt,pol,pre,query,0) > area) swap(l,r);
		forn(i,40) {
			T m = (l+r)/ld(2.);
			if(f(pt,pol,pre,query,m) <= area)  l = m;
			else r = m;
		}
		T ans = l+angle(query+pto(1,0),query,pt[0]);
		while(ans > pi) ans -= pi;
		if(fabs(ans-pi) < EPS) ans-=EPS;
		if(fabs(ans) < EPS) ans+=EPS;
		cout << fixed << setprecision(12) << ans << "\n";
	}
	
	#ifdef JP
		cerr << "Time elapsed: " <<  clock() * 1000 / CLOCKS_PER_SEC << " ms\n";
	#endif
}
