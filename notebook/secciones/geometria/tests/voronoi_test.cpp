// https://codeforces.com/gym/104555/problem/J
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(auto it=v.begin(); it!=v.end();it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef JP


#else

#endif 

using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

typedef ll T; // double could be faster but less precise
typedef long double ld;
const T EPS = 0; // if T is integer, set to 0
const T INF = 1e18;
const ld EPSD = 1e-9; // if T is integer, set to 0
const ld INFD = 1e18;

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
	ld proj2(pto b) { return ((*this)*b)/(b*b); }
	T norm_sq(){ return x*x+y*y; }
	ld norm(){ return sqrtl(x*x+y*y); }
	ld dist(pto b){ return (b-(*this)).norm(); }
	//rotate by theta rads CCW w.r.t. origin (0,0)
	pto rotate(T theta) { 
		return pto(x*cosl(theta)-y*sinl(theta),x*sinl(theta)+y*cosl(theta));
	}
	// true if this is at the left side of line ab
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>0;}
	bool operator<(const pto &b) const {
		return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);
	}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

// Returns planar graph representing Delaunay's triangulation.
// Edges for each vertex are in ccw order.
// It can work with doubles, but also integers (replace long double in line 51)
typedef struct QuadEdge* Q;
struct QuadEdge {
	int id,used;
	pto o;
	Q rot,nxt;
	QuadEdge(int id_=-1, pto o_=pto(INF,INF)):id(id_),used(0),o(o_),rot(0),nxt(0){}
	Q rev(){return rot->rot;}
	Q next(){return nxt;}
	Q prev(){return rot->next()->rot;}
	pto dest(){return rev()->o;}
};

Q edge(pto a, pto b, int ida, int idb){
	Q e1=new QuadEdge(ida,a);
	Q e2=new QuadEdge(idb,b);
	Q e3=new QuadEdge;
	Q e4=new QuadEdge;
	tie(e1->rot,e2->rot,e3->rot,e4->rot)={e3,e4,e2,e1};
	tie(e1->nxt,e2->nxt,e3->nxt,e4->nxt)={e1,e2,e4,e3};
	return e1;
}

void splice(Q a, Q b){
	swap(a->nxt->rot->nxt,b->nxt->rot->nxt);
	swap(a->nxt,b->nxt);
}

void del_edge(Q& e, Q ne){
	splice(e,e->prev()); splice(e->rev(),e->rev()->prev());
	delete e->rev()->rot; delete e->rev();
	delete e->rot; delete e;
	e=ne;
}

Q conn(Q a, Q b){
	Q e=edge(a->dest(),b->o,a->rev()->id,b->id);
	splice(e,a->rev()->prev());
	splice(e->rev(),b);
	return e;
}

auto area(pto p, pto q, pto r){return (q-p)^(r-q);}

// is p in circunference formed by (a,b,c)?
bool in_c(pto a, pto b, pto c, pto p){
	// Warning: this number is O(max_coord^4).
	// Consider using int128 or using an alternative method for this function
	__int128 p2=p*p,A=a*a-p2,B=b*b-p2,C=c*c-p2;
	return area(p,a,b)*C+area(p,b,c)*A+area(p,c,a)*B>EPS;
}

pair<Q,Q> build_tr(vector<pto>& p, int l, int r){
	if(r-l+1<=3){
		Q a=edge(p[l],p[l+1],l,l+1),b=edge(p[l+1],p[r],l+1,r);
		if(r-l+1==2) return {a,a->rev()};
		splice(a->rev(),b);
		auto ar=area(p[l],p[l+1],p[r]);
		Q c=abs(ar)>EPS?conn(b,a):0;
		if(ar>=-EPS) return {a,b->rev()};
		return {c->rev(),c};
	}
	int m=(l+r)/2;
	Q la, ra, lb, rb;
	tie(la,ra)=build_tr(p,l,m);
	tie(lb,rb)=build_tr(p,m+1,r);
	while(1){
		if(ra->dest().left(lb->o,ra->o)) ra=ra->rev()->prev();
		else if(lb->dest().left(lb->o,ra->o)) lb=lb->rev()->next();
		else break;
	}
	Q b=conn(lb->rev(),ra);
	auto valid=[&](Q e){return b->o.left(e->dest(),b->dest());};
	if(ra->o==la->o) la=b->rev();
	if(lb->o==rb->o) rb=b;
	while(1){
		Q L=b->rev()->next();
		if(valid(L)) while(in_c(b->dest(),b->o,L->dest(),L->next()->dest())) del_edge(L,L->next());
		Q R=b->prev();
		if(valid(R)) while(in_c(b->dest(),b->o,R->dest(),R->prev()->dest())) del_edge(R,R->prev());
		if(!valid(L)&&!valid(R)) break;
		if(!valid(L)||(valid(R)&&in_c(L->dest(),L->o,R->o,R->dest()))) b=conn(R,b->rev());
		else b=conn(b->rev(),L->rev());
	}
	return {la,rb};
}

vector<vector<int>> delaunay(vector<pto> v){
	int n=sz(v); auto tmp=v;
	vector<int> id(n); iota(id.begin(),id.end(),0);
	sort(id.begin(), id.end(), [&](int l, int r){return v[l]<v[r];});
	forn(i,n) v[i]=tmp[id[i]];
	assert(unique(v.begin(),v.end())==v.end());
	vector<vector<int>> g(n);
	int col=1;
	forr(i,2,n) col&=abs(area(v[i],v[i-1],v[i-2]))<=EPS;
	if(col){
		forr(i,1,n) g[id[i-1]].pb(id[i]),g[id[i]].pb(id[i-1]);
	}
	else{
		Q e=build_tr(v,0,n-1).fst;
		vector<Q> edg={e};
		for(int i=0;i<sz(edg);e=edg[i++]){
			for(Q at=e;!at->used;at=at->next()){
				at->used=1;
				g[id[at->id]].pb(id[at->rev()->id]);
				edg.pb(at->rev());
			}
		}
	}
	return g;
}

struct pto2{
	ld x, y;
	pto2() : x(0), y(0) {}
	pto2(ld _x, ld _y) : x(_x), y(_y) {}
	pto2 operator+(pto2 b){ return pto2(x+b.x, y+b.y); }
	pto2 operator-(pto2 b){ return pto2(x-b.x, y-b.y); }
	pto2 operator+(ld k){ return pto2(x+k, y+k); }
	pto2 operator*(ld k){ return pto2(x*k, y*k); }
	pto2 operator/(ld k){ return pto2(x/k, y/k); }
	// dot product
	ld operator*(pto2 b){ return x*b.x+y*b.y; }
	// module of cross product, a^b>0 if angle_cw(u,v)<180
	ld operator^(pto2 b){ return x*b.y-y*b.x; }
	// vector projection of this above b
	pto2 proj(pto2 b) { return b*((*this)*b)/(b*b); }
	ld proj2(pto2 b) { return ((*this)*b)/(b*b); }
	ld norm_sq(){ return x*x+y*y; }
	ld norm(){ return sqrtl(x*x+y*y); }
	ld dist(pto2 b){ return (b-(*this)).norm(); }
	//rotate by theta rads CCW w.r.t. origin (0,0)
	pto2 rotate(ld theta) { 
		return pto2(x*cosl(theta)-y*sinl(theta),x*sinl(theta)+y*cosl(theta));
	}
	// true if this is at the left side of line ab
	bool left(pto2 a, pto2 b){return ((a-*this)^(b-*this))>0;}
	bool operator<(const pto2 &b) const {
		return x<b.x-EPSD || (abs(x-b.x)<=EPSD && y<b.y-EPSD);
	}
	bool operator==(pto2 b){return abs(x-b.x)<=EPSD && abs(y-b.y)<=EPSD;}
};

int sgn(ld x){return x<0? -1 : !!x;}
struct line{
	ld a,b,c; // Ax+By=C
	line() {}
	line(ld a_, ld b_, ld c_):a(a_),b(b_),c(c_){}
	// TO DO: check negative C (multiply everything by -1)
	line(pto2 u, pto2 v): a(v.y-u.y), b(u.x-v.x), c(a*u.x+b*u.y) {}
	int side(pto2 v){return sgn(a*v.x + b*v.y - c);}
	bool inside(pto2 v){ return abs(a*v.x + b*v.y - c) <= EPSD; }
	bool parallel(line v){return abs(a*v.b-v.a*b) <= EPSD;}
	pto2 inter(line v){
		ld det=a*v.b-v.a*b;
		if(fabsl(det)<=EPSD) return pto2(INFD,INFD);
		return pto2(v.b*c-b*v.c, a*v.c-v.a*c)/det;
	}
};

#define sqr(a) ((a)*(a))
pto2 perp(pto2 a){return pto2(-a.y, a.x);}
line bisector(pto2 a, pto2 b){
	line l = line(a, b); pto2 m = (a+b)/2;
	return line(-l.b, l.a, -l.b*m.x+l.a*m.y);
}
struct circle{
	pto2 o; ld r;
	circle(){}
	circle(pto2 o_, ld r_) : o(o_), r(r_) {}
	circle(pto2 a, pto2 b, pto2 c) {
		o = bisector(a, b).inter(bisector(b, c));
		r = o.dist(a);
	}
	vector<pto2> inter(line l) {
		ld a = l.a, b = l.b, c = l.c - l.a*o.x - l.b*o.y;
		pto2 xy0 = pto2(a*c/(a*a + b*b), b*c/(a*a + b*b));
		if(c*c > r*r*(a*a + b*b) + EPS) {
			return {};
		}else if(abs(c*c - r*r*(a*a + b*b)) < EPS) {
			return { xy0 + o };
		}else{
			ld m = sqrtl((r*r - c*c/(a*a + b*b))/(a*a + b*b));
			pto2 p1 = xy0 + (pto2(-b,a)*m);
			pto2 p2 = xy0 + (pto2(b,-a)*m);
			return { p1 + o, p2 + o };
		}
	}
};

int main(){
	#ifdef JP
	freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	vector<pto> court(4); ll minx = INF, maxx = -INF, miny = INF, maxy = -INF;
	forn(i,4) {
		ll x,y; cin >> x >> y;
		court[i] = pto(x,y);
		minx = min(minx, court[i].x);
		maxx = max(maxx, court[i].x);
		miny = min(miny, court[i].y);
		maxy = max(maxy, court[i].y);
		
	}
	sort(court.begin(),court.end()); 
	swap(court[2],court[3]);
	
	int n; cin >> n;
	vector<pto> player(n);
	forn(i,n) {
		ll x, y; cin >> x >> y;
		player[i] = pto(x,y);
	}
	
	forn(i,n){
		if(minx<player[i].x) player.pb(pto(2*minx-player[i].x, player[i].y));
		if(player[i].x<maxx) player.pb(pto(2*maxx-player[i].x, player[i].y));
		if(miny<player[i].y) player.pb(pto(player[i].x,2*miny-player[i].y));
		if(player[i].y<maxy) player.pb(pto(player[i].x,2*maxy-player[i].y));
	}
	
	ld ans = 0;
	vector<vector<int>> tr = delaunay(player);
	forn(i,n) {
		if(sz(tr[i])<=1) continue;
		forn(j,sz(tr[i])) {
			pto2 p1(player[i].x,player[i].y);
			pto2 p2(player[tr[i][j]].x,player[tr[i][j]].y);
			pto2 p3(player[tr[i][(j+1)%sz(tr[i])]].x,player[tr[i][(j+1)%sz(tr[i])]].y);
			circle c(p1,p2,p3);
			bool okx = c.o.x+EPS >= minx && c.o.x-EPS <= maxx; 
			bool oky = c.o.y+EPS >= miny && c.o.y-EPS <= maxy;
			if(okx && oky) ans = max(ans, c.r);
		}
	}
	
	cout <<  fixed << setprecision(12) << ans << "\n";
	
	return 0;
}
