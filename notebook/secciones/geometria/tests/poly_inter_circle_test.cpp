// Problem: http://codeforces.com/gym/101208/problem/J
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
//local
#else
//judge
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
	// vector projection of this above b
	pto proj(pto b) { return b*((*this)*b)/(b*b); }

	T norm_sq(){ return x*x+y*y; }
	ld norm(){ return sqrtl(x*x+y*y); }
	ld dist(pto b){ return (b-(*this)).norm(); }

	//rotate by theta rads CCW w.r.t. origin (0,0)
	pto rotate(T theta) { return pto(x*cosl(theta)-y*sinl(theta),x*sinl(theta)+y*cosl(theta)); }
	
	// true if this is at the left side of line ab
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>0;}
	bool operator<(const pto &b) const{return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

ld angle(pto a, pto o, pto b){
	pto oa=a-o, ob=b-o;
	return atan2l(oa^ob, oa*ob);
}

ld angle(pto a, pto b){ // smallest angle bewteen a and b
	ld cost = (a*b)/a.norm()/b.norm();
	return acosl(max(ld(-1.), min(ld(1.), cost)));
}

int sgn(T x){return x<0? -1 : !!x;}

struct line{
	T a,b,c; // Ax+By=C
	
	line() {}
	line(T a_, T b_, T c_):a(a_),b(b_),c(c_){}
	// TO DO: check negative C (multiply everything by -1)
	line(pto u, pto v): a(v.y-u.y), b(u.x-v.x), c(a*u.x+b*u.y) {}

	int side(pto v){return sgn(a*v.x + b*v.y - c);}
	bool inside(pto v){ return abs(a*v.x + b*v.y - c) <= EPS; }
	bool parallel(line v){return abs(a*v.b-v.a*b) <= EPS;}
	pto inter(line v){
		T det=a*v.b-v.a*b;
		if(abs(det)<=EPS) return pto(INF, INF);
		return pto(v.b*c-b*v.c, a*v.c-v.a*c)/det;
	}
};

#define sqr(a) ((a)*(a))

pto perp(pto a){return pto(-a.y, a.x);}

line bisector(pto a, pto b){
	line l=line(a, b); pto m=(a+b)/2;
	return line(-l.b, l.a, -l.b*m.x+l.a*m.y);
}

struct circle{
	pto o; T r;
	
	circle(){}
	circle(pto a, pto b, pto c){
		o=bisector(a, b).inter(bisector(b, c));
		r=o.dist(a);
	}
	bool inside(pto p) { return (o-p).norm_sq() <= r*r+EPS; }
	bool inside(circle c){ // this inside of c
		T d=(o-c.o).norm_sq();
		return d<=(c.r-r)*(c.r-r)+EPS;
	}
	// circle containing p1 and p2 with radius r
	// swap p1, p2 to get snd solution
	circle* circle2PtoR(pto a, pto b, T r_){
        ld d2=(a-b).norm_sq(), det=r_*r_/d2-ld(0.25);
        if(det<0) return nullptr;
		circle *ret = new circle();
        ret->o=(a+b)/ld(2)+perp(b-a)*sqrt(det);
        ret->r=r_;
		return ret;
	}
	
	pair<pto, pto> tang(pto p){
		pto m=(p+o)/2;
		ld d=o.dist(m);
		ld a=r*r/(2*d);
		ld h=sqrtl(r*r-a*a);
		pto m2=o+(m-o)*a/d;
		pto per=perp(m-o)/d;
		return make_pair(m2-per*h, m2+per*h);
	}
	
	vector<pto> inter(line l){
		ld a = l.a, b = l.b, c = l.c - l.a*o.x - l.b*o.y;
		
		pto xy0 = pto(a*c/(a*a+b*b),b*c/(a*a+b*b));
		if(c*c > r*r*(a*a+b*b)+EPS){
			return {};
		}else if(abs(c*c-r*r*(a*a+b*b))<EPS){
			return {xy0+o};
		}else{
			ld m = sqrtl((r*r - c*c/(a*a+b*b))/(a*a+b*b));
			pto p1 = xy0 + (pto(-b,a)*m);
			pto p2 = xy0 + (pto(b,-a)*m);
			return {p1+o,p2+o};
		}
	}
	
	vector<pto> inter(circle c){
		line l;
		l.a = o.x-c.o.x;
		l.b = o.y-c.o.y;
		l.c = (sqr(c.r)-sqr(r)+sqr(o.x)-sqr(c.o.x)+sqr(o.y)
		-sqr(c.o.y))/ld(2.0);
		return (*this).inter(l);
	}
	
	ld inter_triangle(pto a, pto b){ // area of intersection with oab
		if(abs((o-a)^(o-b))<=EPS)return 0.;
		vector<pto> q={a}, w=inter(line(a,b));
		if(sz(w)==2) forn(i,sz(w)) if((a-w[i])*(b-w[i])<-EPS) q.pb(w[i]);
		q.pb(b);
		if(sz(q)==4 && (q[0]-q[1])*(q[2]-q[1])>EPS) swap(q[1],q[2]);
		ld s=0;
		forn(i,sz(q)-1){
			if(!inside(q[i]) || !inside(q[i+1])) s += r*r*angle((q[i]-o),q[i+1]-o)/T(2);
			else s += abs((q[i]-o)^(q[i+1]-o)/2);
		}
		return s;
	}
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
		if(len>2 && abs((pt.back()-pt[len-2])^(pt[0]-pt.back())) <= EPS) nxt.pop_back(), len--;
		pt.clear(); forn(i,sz(nxt)) pt.pb(nxt[i]);
	}
	
	void normalize(){
		delete_collinears();
		if(pt[2].left(pt[0], pt[1])) reverse(pt.begin(), pt.end()); // this makes it clockwise
		int n=sz(pt), pi=0;
		forn(i, n)
			if(pt[i].x<pt[pi].x || (pt[i].x==pt[pi].x && pt[i].y<pt[pi].y))
				pi=i;
		rotate(pt.begin(), pt.begin()+pi, pt.end());
	}
		
	bool is_convex(){ // delete collinear points first
		int N = sz(pt);
		if(N<3) return false;
		bool isLeft=pt[0].left(pt[1], pt[2]);
		forr(i, 1, sz(pt))
			if(pt[i].left(pt[(i+1)%N], pt[(i+2)%N]) != isLeft)
				return false;
		return true; 
	}
	
	// for convex or concave polygons
	// excludes boundaries, check it manually
	bool inside(pto p) { // O(n)  
		bool c = false;
		forn(i, sz(pt)){
			int j=(i+1)%sz(pt);
			if((pt[j].y>p.y) != (pt[i].y > p.y) && 
			(p.x < (pt[i].x - pt[j].x) * (p.y-pt[j].y) / (pt[i].y - pt[j].y) + pt[j].x))
				c = !c;
		}
		return c;
	}
	
	bool inside_convex(pto p){ // O(lg(n)) normalize first
		if(p.left(pt[0], pt[1]) || p.left(pt[sz(pt)-1], pt[0])) return false;
		int a=1, b=sz(pt)-1;
		while(b-a>1){
			int c=(a+b)/2;
			if(!p.left(pt[0], pt[c])) a=c;
			else b=c;
		}
		return !p.left(pt[a], pt[a+1]);
	}
	
	// cuts this along line ab and return the left side 
	// (swap a, b for the right one)
	poly cut(pto a, pto b){ // O(n)
		vector<pto> ret;
		forn(i, sz(pt)){
			ld left1=(b-a)^(pt[i]-a), left2=(b-a)^(pt[(i+1)%sz(pt)]-a);
			if(left1>=0) ret.pb(pt[i]);
			if(left1*left2<0)
				ret.pb(line(pt[i], pt[(i+1)%sz(pt)]).inter(line(a, b)));
		}
		return poly(ret);
	}

	// addition of convex polygons
	poly minkowski(poly p) { // O(n+m) n=|this|,m=|p| 
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
	
	pto farthest(pto v){ // O(log(n)) for convex polygons
		if(sz(pt)<10){
			int k=0;
			forr(i,1,sz(pt)) if(v*(pt[i]-pt[k])>EPS) k=i;
			return pt[k];
		}
		pt.pb(pt[0]);
		pto a=pt[1]-pt[0];
		int s=0, e=sz(pt)-1, ua=v*a>EPS;
		if(!ua && v*(pt[sz(pt)-2]-pt[0]) <= EPS){ pt.pop_back(); return pt[0];}
		while(1){
			int m = (s+e)/2; pto c=pt[m+1]-pt[m];
			int uc=v*c > EPS;
			if(!uc && v*(pt[m-1]-pt[m]) <= EPS){ pt.pop_back(); return pt[m];}
			if(ua && (!uc || v*(pt[s]-pt[m])>EPS)) e=m;
			else if(ua || uc || v*(pt[s]-pt[m]) >= -EPS) s=m, a=c, ua=uc;
			else e=m;
			assert(e>s+1);
		}
	}
	
	ld inter_circle(circle c){ // area of intersection with circle
		ld r = 0.;
		forn(i,sz(pt)){
			int j=(i+1)%sz(pt); ld w = c.inter_triangle(pt[i], pt[j]);
			if(((pt[j]-c.o)^(pt[i]-c.o)) > 0) r += w;
			else r -= w;
		}
		return abs(r);
	}
	
	// area ellipse = M_PI*a*b where a and b are the semi axis lengths
	// area triangle = sqrt(s*(s-a)(s-b)(s-c)) where s=(a+b+c)/2
	ld area(){ // O(n)
		ld area=0;
		forn(i, sz(pt)) area+=pt[i]^pt[(i+1)%sz(pt)];
		return abs(area)/ld(2);
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

int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,r;
	cin >> n >> r;
	poly p;
	forn(i,n)
	{
		int x,y;
		cin >> x >> y;
		p.pt.pb(pto(x,y));
	}
	circle c;
	c.o = pto(0,0);
	c.r = r;
	cout << fixed << setprecision(10) << p.inter_circle(c);
	return 0;
}
