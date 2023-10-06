// problem: https://www.spoj.com/problems/TAP2015A/
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
#define sqr(a) ((a)*(a))
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef long double T;
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

ld angle(pto a, pto o, pto b){
	pto oa=a-o, ob=b-o;
	return atan2l(oa^ob, oa*ob);
}

ld angle(pto a, pto b){
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
};


int main(){
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n;
	while(cin>>n) {
		vector<circle> c(n);
		forn(i,n){
			T x,y,r; cin >> x >> y >> r;
			c[i].o = pto(x,y);
			c[i].r = r;
		}
		
		int ans = 0;
		forn(i,n) {
			forr(j,i+1,n) {
				vector<pto> in = c[i].inter(c[j]);
				forn(k,sz(in)) {
					int r = 0;
					forn(ci,sz(c)) {
						r += c[ci].o.dist(in[k]) <= c[ci].r + EPS;
					}
					ans = max(ans,r);
				}
			}
			int r = 1;
			forn(j,n) {
				if (i == j) continue;
				r += c[i].o.dist(c[j].o) <= c[j].r + EPS;
			}
			ans = max(ans,r);
		}
		
		cout << ans << "\n";
	}
	
	return 0;
}
