// problem: https://codeforces.com/gym/104555/problem/G
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

using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef long long T;
typedef long double ld;
const T EPS = 0;

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
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

// returns convex hull of p in CCW order
// left must return >=0 to delete collinear points
vector<pto> CH(vector<pto>& p) {
  if (sz(p) < 3) return p;  // edge case, keep line or point
  vector<pto> ch;
  sort(p.begin(), p.end());
  forn(i, sz(p)) {  // lower hull
    while (sz(ch) >= 2 && ch[sz(ch) - 1].left(ch[sz(ch) - 2], p[i]))
      ch.pop_back();
    ch.pb(p[i]);
  }
  ch.pop_back();
  int k = sz(ch);
  dforn(i, sz(p)) {  // upper hull
    while (sz(ch) >= k + 2 && ch[sz(ch) - 1].left(ch[sz(ch) - 2], p[i]))
      ch.pop_back();
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
	
	int n; cin >> n;
	vector<pto> ptos(n);
	forn(i,n) {
		cin >> ptos[i].x >> ptos[i].y;
		ptos[i].id = i+1;
	}
	
	vector<pto> ch = CH(ptos);
	set<T> ids; forn(i,sz(ch)) ids.insert(ch[i].id);
	forall(i,ids) cout << *i << " ";
	cout << "\n";
	
	return 0;
}
