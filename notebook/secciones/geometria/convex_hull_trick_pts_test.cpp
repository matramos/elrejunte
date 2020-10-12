//Problem: https://codeforces.com/problemset/problem/631/E
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
#else
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

typedef ll tipo;

struct pto{
	tipo x,y;
	pto operator-(pto a){return {x-a.x, y-a.y};}
	//dot product, producto interno:
	tipo operator*(pto a){return x*a.x+y*a.y;}
	//module of the cross product or vectorial product:
	//if a is less than 180 clockwise from b, a^b>0
	tipo operator^(pto a){return x*a.y-y*a.x;}
	//returns true if this is at the left side of line qr
	bool left(pto &q, pto &r){return ((q-*this)^(r-*this))>0;}
};
typedef pto vec;
struct CHT{
	deque<pto> c;
	bool mn;
	int pos;
	CHT(bool mn=0):mn(mn),pos(0){}//mn=1 si querys de min
	void add(tipo m, tipo h) {//O(1)
		//Querys max f_i, necesitamos capsula inferior
		if(mn) m*=-1, h*=-1; //min f_i(x) == max -f_i(x)
		pto p = {-m,-h}; //Line(m,h) == pto(-m,-h)
		if(c.empty()) {c.pb(p); return;}
		//el nuevo m tiene que ser el menor o el mayor (m "ordenados")
		assert(p.x <= c[0].x || p.x >= c.back().x);
		if(p.x <= c[0].x) {
			if(p.x == c[0].x) p.y = min(p.y, c[0].y), c.pop_front(), pos--;
			while(c.size() > 1 && !c[1].left(p, c[0])) c.pop_front(), pos--;
			c.push_front(p); pos++;
		}
		else {
			if(p.x == c.back().x) p.y = min(p.y, c.back().y), c.pop_back();
			while(c.size() > 1 && !p.left(c[sz(c)-2], c[sz(c)-1])) c.pop_back();
			c.pb(p);
		}
		pos = min(max(0,pos), sz(c)-1);
	}
	tipo eval(tipo x){ //max f_i(x) == max p_i*(-x,-1) (dot prod)
		vec vx = {-x,-1};
		//querys O(log), para x desordenado
		int L = 0,R = sz(c)-1, M;
		while(L < R) {
			M = (L+R)/2;
			if(c[M+1]*vx > c[M]*vx) L = M+1;
			else R = M;
		}
		return c[L]*vx*(mn?-1:1);
		//querys O(1), para x "ordenados"
		/*while(pos > 0 && c[pos-1]*vx > c[pos]*vx) pos--;
		while(pos < sz(c)-1 && c[pos+1]*vx > c[pos]*vx) pos++;
		return c[pos]*vx*(mn?-1:1);*/
	}
};


ll solve1(vector<ll> &v, vector<ll> &acum)
{
	int n = sz(v);
	CHT cht(1);
	ll ret = 0;
	forr(j,1,n)
	{
		cht.add(-j, acum[j-1]);
		ret = max(ret, acum[j-1] - j*v[j] - cht.eval(v[j]));
	}
	return ret;
}

ll solve2(vector<ll> &v, vector<ll> &acum)
{
	int n = sz(v);
	CHT cht;
	ll ret = 0;
	dforn(i,n)
	{
		if(i == 0) break;
		cht.add(i, -acum[i]);
		ret = max(ret, acum[i] - i*v[i] + cht.eval(v[i]));
	}
	return ret;
}

int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	vector<ll> v(n+1), acum(n+1);
	v[0] = acum[0] = 0;
	ll ans1 = 0;
	forr(i,1,n+1)
	{
		cin >> v[i];
		acum[i] = v[i] + acum[i-1];
		ans1 += i*v[i];
	}
	cout << ans1 + max(solve1(v, acum), solve2(v,acum)) << '\n';
	return 0;
}
