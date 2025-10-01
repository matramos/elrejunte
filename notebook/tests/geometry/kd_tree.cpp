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
typedef long long T;
typedef long long ld;
const T EPS = 0; // if T is integer, set to 0
const T INF = 1e9;

struct pto{
	T x, y, id;
	
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
	bool operator==(const pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

bool cmpx(pto a, pto b) { return a.x+EPS<b.x; }
bool cmpy(pto a, pto b) { return a.y+EPS<b.y; }
struct kd_tree{
	pto p; T x0=INF, x1=-INF, y0=INF, y1=-INF;
	kd_tree *l, *r;
	
	T distance(pto q){
		T x = min(max(x0, q.x), x1);
		T y = min(max(y0, q.y), y1);
		return (pto(x,y)-q).norm_sq();
	}
	
	kd_tree(vector<pto> &&pts) : p(pts[0]) {
		l = nullptr, r = nullptr;
		forn(i,sz(pts)) {
			x0 = min(x0, pts[i].x), x1 = max(x1, pts[i].x);
			y0 = min(y0, pts[i].y), y1 = max(y1, pts[i].y);
		}
		if(sz(pts) > 1){
			sort(pts.begin(), pts.end(), x1-x0>=y1-y0? cmpx : cmpy);
			int m = sz(pts)/2;
			l = new kd_tree({pts.begin(), pts.begin()+m});
			r = new kd_tree({pts.begin()+m, pts.end()});
		}
	}
	
	void nearest(pto q, int k, priority_queue<pair<T,pto>> &ret) {
		if(l == nullptr) {
			// avoid query point as answer
			// if(p == q) return;
			ret.push({(q-p).norm_sq(), p});
			while(sz(ret)>k) ret.pop();
			return;
		}
		kd_tree *al = l, *ar = r;
		T bl = l->distance(q), br = r->distance(q);
		if(bl>br) swap(al,ar), swap(bl,br);
		al->nearest(q,k,ret);
		if(br<ret.top().fst) ar->nearest(q,k,ret);
		while(sz(ret)>k) ret.pop();
	}
	
	priority_queue<pair<T,pto>> nearest(pto q, int k){
		priority_queue<pair<T,pto>> ret;
		forn(i,k) ret.push({INF*INF,pto(INF,INF)});
		nearest(q,k,ret);
		return ret;
	}
};

vector<pair<pto,int>> solve(vector<pair<pto,int>> &v){
	if(sz(v)<=1) return v;
	int m=sz(v)/2;

	//left
	auto lef=vector<pair<pto,int>>(v.begin(),v.begin()+m);
	lef=solve(lef);
	vector<pto> now; for(auto x:lef) now.pb(x.fst);
	kd_tree kd({now.begin(), now.end()});

	//right
	vector<pair<pto,int>> rig;
	forr(i,m,sz(v)){
		pto mid=v[i].fst/2;
		auto pq = kd.nearest(mid,1); 
		pto now=pq.top().snd;
		if((now-mid).norm_sq() > (v[i].fst-mid).norm_sq()) rig.pb(v[i]);
	}
	rig=solve(rig);
	
	for(auto x:rig) lef.pb(x);
	return lef;
}


int main(){
	freopen("nothingontv.in", "r", stdin);
	freopen("nothingontv.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n; cin >> n;
	vector<pair<pto,int>> pub(n);
	forn(i,n){
		cin >> pub[i].fst.x >> pub[i].fst.y;
		pub[i].fst = pub[i].fst*2;
		pub[i].snd = i;
	}
	
	sort(pub.begin(), pub.end(),[](pair<pto,int> a, pair<pto,int> b) { return a.fst.norm_sq()<b.fst.norm_sq(); });
	vector<pair<pto,int>> ans = solve(pub);
	sort(ans.begin(), ans.end(),[](pair<pto,int> a, pair<pto,int> b) { return a.snd<b.snd; });
	cout << sz(ans) << "\n";
	forn(i,sz(ans)) cout << ++ans[i].snd << " ";
	cout << "\n";
	
	return 0;
}
