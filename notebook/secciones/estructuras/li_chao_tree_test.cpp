// https://codeforces.com/group/XrhoJtxCjm/contest/422715/problem/I
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back

#ifdef FRUTA_FRESCA
	const int MAXN = 10000;
#else
	const int MAXN = 1000010;
#endif

using namespace std;

typedef unsigned long long ll;
typedef pair<int,int> ii;
typedef __int128 T;
const unsigned long long INF = 15000000000000000000ULL;

struct line{
	T m, b, pl;
	
	line(){}
	line(T newM, T newB){
		m = newM;
		b = newB;
	}
	line(T newM, T newB, T newPl){
		m = newM;
		b = newB;
		pl = newPl;
	}
	
	T y (T x){
		return m*x + b;
	}
};

struct liChaoTree{
	int sz;
	line neutro = line(0,INF,-1);
	line t[MAXN*4];
	unordered_map<ll,ll> getTime;
	
	void init(int n){
		sz = 1 << (32 - __builtin_clz(n)); 
		forn(i,2*sz) t[i] =  neutro;
	}
	
	void add(line newLine){
		add(newLine,1,0,sz);
	}
	
	void add(line newLine, int v, int l, int r){
		int m = (l + r) / 2;
		
		bool lef = newLine.y(getTime[l]) < t[v].y(getTime[l]);
		bool mid = newLine.y(getTime[m]) < t[v].y(getTime[m]);
		
		if(mid) swap(t[v],newLine);
		if(newLine.y(getTime[m]) == t[v].y(getTime[m]) && newLine.m == t[v].m) t[v].pl = max(newLine.pl,t[v].pl);
		
		if(r - l == 1) return;
		else if(lef != mid) add(newLine, v*2, l, m);
		else add(newLine, v*2 + 1, m, r);
	}
	
	line get(int x){
		return get(x,1,0,sz);
	}
	
	line getMin(line a, line b, T x){
		if(a.y(x) < b.y(x)){
			return a;
		}else if(a.y(x) == b.y(x)){
			return line(a.m,a.b,max(a.pl,b.pl));
		}else{
			return b;
		}
	}
	
	line get(T x, int v, int l, int r){
		int m = (l + r)/2;
		if(r - l == 1) return t[v];
		else if(x < getTime[m]){
			return getMin(t[v], get(x, v*2, l, m), x);
		}else{
			return getMin(t[v], get(x, v*2 + 1, m, r), x);
		}
	}
	
	
};

int main()
{
	#ifdef FRUTA_FRESCA
		freopen("input.txt", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n,q; cin >> n >> q;
	vector<T> v(n),d(n),lt(n);
	
	vector<line> lines;
	forn(i,n){ 
		ll vi; cin >> vi; v[i] = vi;
		lines.pb(line(vi,0,i));
	}
	
	vector<T> queries;
	forn(i,q){
		ll pl, tl, vl; 
		cin >> pl >> tl >> vl;
		pl--;
		
		__int128 ti = tl, vi = vl;
		queries.pb(ti);
		d[pl] += v[pl] * (ti - lt[pl]);
		v[pl] -= vi;
		lt[pl] = ti;
		
		lines.pb(line(v[pl],d[pl]-ti*v[pl],pl));
	}
	
	int id = 0;
	
	liChaoTree lct; ll inft = 10000000000;
	forn(i,sz(queries)) lct.getTime[id++] = queries[i];
	lct.init(id);
	forr(i,sz(queries),lct.sz) lct.getTime[i] = inft++;
	forn(i,sz(lines)) lct.add(lines[i]);
	
	forn(i,sz(queries)){
		line ans = lct.get(queries[i]);
		cout << ll(ans.pl+1) << " " << ll(ans.y(queries[i])) << "\n"; 
	}
	
	return 0;
}

