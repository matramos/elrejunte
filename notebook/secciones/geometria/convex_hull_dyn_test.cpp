// ANARAP 💙💛💙
//NCPC 2021 Problem H: Hiring Help
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
#define EPS 1e-7
struct pto{
	long double x, y;
	pto(long double x=0, long double y=0):x(x),y(y){}
	pto operator+(pto a){return pto(x+a.x, y+a.y);}
	pto operator-(pto a){return pto(x-a.x, y-a.y);}
	pto operator+(long double a){return pto(x+a, y+a);}
	pto operator*(long double a){return pto(x*a, y*a);}
	pto operator/(long double a){return pto(x/a, y/a);}
	//dot product, producto interno:
	long double operator*(pto a){return x*a.x+y*a.y;}
	//module of the cross product or vectorial product:
	//if a is less than 180 clockwise from b, a^b>0
	long double operator^(pto a){return x*a.y-y*a.x;}
	//returns true if this is at the left side of line qr
	bool left(pto q, pto r){return ((q-*this)^(r-*this))>0;}
	bool operator<(const pto &a) const{return x<a.x-EPS || (abs(x-a.x)<EPS && y<a.y-EPS);}
bool operator==(pto a){return abs(x-a.x)<EPS && abs(y-a.y)<EPS;}
	long double norm(){return sqrt(x*x+y*y);}
	long double norm_sq(){return x*x+y*y;}
};
long double dist(pto a, pto b){return (b-a).norm();}
typedef pto vec;

long double angle(pto a, pto o, pto b){
	pto oa=a-o, ob=b-o;
	return atan2(oa^ob, oa*ob);}

//rotate p by theta rads CCW w.r.t. origin (0,0)
pto rotate(pto p, double theta){
	return pto(p.x*cos(theta)-p.y*sin(theta),
     p.x*sin(theta)+p.y*cos(theta));
}
 
// Superior
struct Semi_Chull {
    set<pto> pts;
    bool check(pto p) {
        if(pts.empty()) return false;
        if(*pts.rbegin() < p) return false;
        if(p < *pts.begin()) return false;
        auto it = pts.lower_bound(p);
        if(it->x == p.x) return p.y <= it->y;
        pto b = *it;
        pto a = *prev(it);
        return ((b-p)^(a-p))+EPS >= 0;
    }
 
    void add(pto p) {
        if(check(p)) return;
        pts.erase(p); pts.insert(p);
        auto it = pts.find(p);
 
        while(true) {
            if(next(it) == pts.end() || next(next(it)) == pts.end()) break;
            pto a = *next(it);
            pto b = *next(next(it));
            if(((b-a)^(p-a))+EPS >= 0) {
                pts.erase(next(it));
            } else break;
        }
 
        it = pts.find(p);
 
        while(true) {
            if(it == pts.begin() || prev(it) == pts.begin()) break;
            pto a = *prev(it);
            pto b = *prev(prev(it));
            if(((b-a)^(p-a))-EPS <=0) {
                pts.erase(prev(it));
            } else break;
        }
    }
};
 
struct Chull {
    Semi_Chull sup, inf;
    void add(pto p) {
        sup.add(p);
        pto np = {-1*p.x, -1*p.y};
        inf.add(np);
    }
    bool check(pto p) {
		pto np = {-1*p.x, -1*p.y};
        return sup.check(p) && inf.check(np);
    }
};
 



int main()
{
	#ifdef ANARAP
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
	Chull chull;
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

