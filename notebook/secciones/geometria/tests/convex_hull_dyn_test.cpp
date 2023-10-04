// https://open.kattis.com/problems/hiringhelp
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
//prueba
#else
//real
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,pair<long double,long double>> query;
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

 
struct semi_chull {
    set<pto> pt; // maintains semi chull without collinears points
    // in case we want them on the set, make the changes commented below
    bool check(pto p) {
        if(pt.empty()) return false;
        if(*pt.rbegin() < p) return false;
        if(p < *pt.begin()) return false;
        auto it = pt.lower_bound(p);
        if(it->x == p.x) return p.y <= it->y; // ignore it to take in count collinears points too
        pto b = *it;
        pto a = *prev(it);
        return ((b-p)^(a-p))+EPS >= 0; // > 0 to take in count collinears points too
    }
 
    void add(pto p) {
        if(check(p)) return;
        pt.erase(p); pt.insert(p);
        auto it = pt.find(p);
 
        while(true) {
            if(next(it) == pt.end() || next(next(it)) == pt.end()) break;
            pto a = *next(it);
            pto b = *next(next(it));
            if(((b-a)^(p-a))+EPS >= 0) { // > 0 to take in count collinears points too
                pt.erase(next(it));
            } else break;
        }
 
        it = pt.find(p);
        while(true) {
            if(it == pt.begin() || prev(it) == pt.begin()) break;
            pto a = *prev(it);
            pto b = *prev(prev(it));
            if(((b-a)^(p-a))-EPS <=0) { // < 0 to take in count collinears points too
                pt.erase(prev(it));
            } else break;
        }
    }
};

struct CHD{
    semi_chull sup, inf;
    void add(pto p) {
        sup.add(p); inf.add(p*(-1));
    }
    bool check(pto p) {
        return sup.check(p) && inf.check(p*(-1));
    }
};


int main(){
	#ifdef JP
		freopen("input.in", "r", stdin);
		//~ freopen("output.txt", "w", stdout);
		unsigned t0, t1; t0=clock();
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n; cin >> n;
	vector<pto> emp(n);
	forn(i,n) cin >> emp[i].x >> emp[i].y;
	int nq; cin >> nq;
	vector<query> q(nq);
	vector<bool> used(n);
	//~ if(n==2 && nq==2 && emp[0].x==1 && emp[0].y==26 && emp[1].x == 2 && emp[1].y == 1) assert(0);
	forn(i,nq){
		char x; cin >> x;
		if(x == 'c'){
			double a,b,c; cin >> a >> b >> c;
			q[i].fst.fst = 1;
			q[i].fst.snd = -1;
			q[i].snd.fst = b/a;
			q[i].snd.snd = c/a;
		}
		else{
			int kick; cin >> kick; kick--;
			used[kick]=1;
			q[i].fst.fst = 0;
			q[i].fst.snd = kick;
		}
	}
	CHD chull;
	long double maxx = 0.0, maxy=0.0;
	vector<bool> ans;
	forn(i,n) if(!used[i]){chull.add(emp[i]); maxx = max(maxx,emp[i].x); maxy = max(maxy,emp[i].y);}
	chull.add({maxx,0}); 
	chull.add({0,maxy});
	chull.add({0,0});
	dforn(i,nq){
		if(q[i].fst.fst == 1) ans.pb(chull.check({q[i].snd.fst, q[i].snd.snd})); 
		else{
			chull.add(emp[q[i].fst.snd]);
			if(maxx < emp[q[i].fst.snd].x){
				maxx = emp[q[i].fst.snd].x;
				chull.add({maxx,0});
			}
			if(maxy < emp[q[i].fst.snd].y){
				maxy = emp[q[i].fst.snd].y;
				chull.add({0,maxy});
			}
		}
	}
	dforn(i,sz(ans)) cout << (ans[i]? "no":"yes") << '\n';
	
	
	#ifdef ANARAP
	t1 = clock();double time = (double(t1-t0)/CLOCKS_PER_SEC); cout << "Execution Time: " << time << endl;
	#endif
	return 0;
}

