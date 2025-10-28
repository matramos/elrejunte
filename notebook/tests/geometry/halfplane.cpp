// problem: https://open.kattis.com/problems/bigbrother
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
const T INF = 1e9;

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

struct halfplane {  // left half plane
  pto u, uv;
  int id;
  ld angle;
  halfplane() {}
  halfplane(pto u_, pto v_) : u(u_), uv(v_ - u_), angle(atan2l(uv.y, uv.x)) {}
  bool operator<(halfplane h) const { return angle < h.angle; }
  bool out(pto p) { return (uv ^ (p - u)) < -EPS; }
  pto inter(halfplane& h) {
    T alpha = ((h.u - u) ^ h.uv) / (uv ^ h.uv);
    return u + (uv * alpha);
  }
};
vector<pto> intersect(vector<halfplane> h) {
  pto box[4] = {{INF, INF}, {-INF, INF}, {-INF, -INF}, {INF, -INF}};
  forn(i, 4) h.pb(halfplane(box[i], box[(i + 1) % 4]));
  sort(h.begin(), h.end());
  deque<halfplane> dq;
  int len = 0;
  forn(i, sz(h)) {
    while (len > 1 && h[i].out(dq[len - 1].inter(dq[len - 2]))) {
      dq.pop_back(), len--;
    }
    while (len > 1 && h[i].out(dq[0].inter(dq[1]))) { dq.pop_front(), len--; }
    if (len > 0 && abs(h[i].uv ^ dq[len - 1].uv) <= EPS) {
      if (h[i].uv * dq[len - 1].uv < 0.) { return vector<pto>(); }
      if (h[i].out(dq[len - 1].u)) {
        dq.pop_back(), len--;
      } else continue;
    }
    dq.pb(h[i]);
    len++;
  }
  while (len > 2 && dq[0].out(dq[len - 1].inter(dq[len - 2]))) {
    dq.pop_back(), len--;
  }
  while (len > 2 && dq[len - 1].out(dq[0].inter(dq[1]))) {
    dq.pop_front(), len--;
  }
  if (len < 3) return vector<pto>();
  vector<pto> inter;
  forn(i, len) inter.pb(dq[i].inter(dq[(i + 1) % len]));
  return inter;
}


struct poly{
	vector<pto> pt;
	
	poly(){}
	poly(vector<pto> pt_) : pt(pt_) {}
	
	// area ellipse = M_PI*a*b where a and b are the semi axis lengths
	// area triangle = sqrt(s*(s-a)(s-b)(s-c)) where s=(a+b+c)/2
	ld area(){
		ld area=0;
		forn(i, sz(pt)) area+=pt[i]^pt[(i+1)%sz(pt)];
		return abs(area)/ld(2);
	}
};



int main(){
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n; cin >> n; 
	vector<pto> p(n);
	forn(i,n) cin >> p[i].x >> p[i].y;
	
	vector<halfplane> h(n);
	forn(i,n){
		h[i] = halfplane(p[(i+1)%n],p[i]);
		h[i].id=i;
	}
	
	vector<pto> inter = intersect(h);
	poly ans = poly(inter);
	cout << fixed << setprecision(9)<< ans.area() << "\n";
	
	return 0;
}
