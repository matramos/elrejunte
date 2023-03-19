// https://codeforces.com/group/XrhoJtxCjm/contest/422715/problem/I
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back

#ifdef FRUTA_FRESCA
#else
#endif

using namespace std;

typedef unsigned long long ll;
typedef pair<int,int> ii;
typedef __int128 T;
const unsigned long long INF = 15'000'000'000'000'000'000ULL;
const unsigned long long MAXT = 1000'000'010;

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
	
	T f (T x){
		return m*x + b;
	}
};

struct li_chao{
	line cur_line;
	li_chao* lnode;
	li_chao* rnode;
	
	li_chao(line nline, li_chao* nlnode = nullptr, li_chao* nrnode = nullptr){
		lnode = nlnode; 
		rnode = nrnode; 
		cur_line = nline;
	}
	
	void add(line new_line, T l, T r){ // for persistent, use li_chao* instead of void
		T m = (l+r) / 2;
		
		bool lef = new_line.f(l) < cur_line.f(l); // for max, use >
		bool mid = new_line.f(m) < cur_line.f(m); // for max, use >
		
		//~ uncomment for persistent
		//~ line to_push = new_line, to_keep = cur_line; 
		//~ if(mid) swap(to_push,to_keep);
		if(mid) swap(new_line,cur_line);
		if(new_line.f(m) == cur_line.f(m) && new_line.m == cur_line.m) cur_line.pl = max(new_line.pl,cur_line.pl);
		
		if(r - l == 1){
			//~ uncomment for persistent
			//~ return new li_chao(to_keep);
			return;
		}else if(lef != mid){
			//~ uncomment for persistent
			//~ return new li_chao(lnode->add(to_push, l, m), rnode, to_keep);
			if(lnode == nullptr) lnode = new li_chao(line(0,INF,-1));
			lnode->add(new_line,l,m);
		}else{
			//~ uncomment for persistent
			//~ return new li_chao(lnode, rnode->add(to_push, m, r), to_keep);
			if(rnode == nullptr) rnode = new li_chao(line(0,INF,-1)); 
			rnode->add(new_line,m,r);
		}
	}
	
	line get(T x){
		return get(x,0,MAXT);
	}
	
	line get_min(line a, line b, T x){
		if(a.f(x) < b.f(x)){
			return a;
		}else if(a.f(x) == b.f(x)){
			return line(a.m,a.b,max(a.pl,b.pl));
		}else{
			return b;
		}
	}
	
	line get(T x, T l, T r){
		T m = (r+l)/2;
		
		if(r - l == 1) return cur_line;
		else if(x < m) 
			return get_min(cur_line, lnode == nullptr ? line(0,INF,-1) : lnode->get(x, l, m), x);	// for max, use max
		else 
			return get_min(cur_line, rnode == nullptr ? line(0,INF,-1) : rnode->get(x, m, r), x);  // for max, use max
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
	
	li_chao lc = li_chao(line(0,INF,-1));
	forn(i,n){ 
		ll vi; cin >> vi; v[i] = vi;
		lc.add(line(vi,0,i), 0, MAXT);
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
		
		lc.add(line(v[pl],d[pl]-ti*v[pl],pl),0,MAXT);
	}
		
	forn(i,sz(queries)){
		line ans = lc.get(queries[i]);
		cout << ll(ans.pl+1) << " " << ll(ans.f(queries[i])) << "\n"; 
	}
	
	return 0;
}
