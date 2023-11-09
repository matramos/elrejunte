// Problem: https://codeforces.com/gym/104736/problem/A
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
//local
#else
//judge
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

vector<ii> v;

typedef long long T;
const T INF = 0;

// Li-Chao works for any function such that any pair of the functions
// inserted intersect at most once with each other. Most problems are
// about lines, but you may want to adapt this struct to your function
struct line{
	T e,r;
	line(){}
	line(T e_, T r_){ e = e_; r = r_; }
	T f(T x){ return -max(0LL, r-v[x].snd) * max(0LL, e-v[x].fst+1); }
	//line operator+(line l) { return line(m+l.m, b+l.b); }
	line operator*(T k) { return *this; }
};

struct li_chao {
	vector<line> cur, add;
	vector<int> L, R;
	T f, minx, maxx;
	line identity;
	int cnt;
	
	void new_node(line cur_, int l=-1, int r=-1){
		cur.pb(cur_);
		add.pb(line(0,0));
		L.pb(l); R.pb(r);
		cnt++;
	}
	
	li_chao(bool min_, T minx_, T maxx_){ // for min: min_=1, for max: min_=0
		f = min_ ? 1 : -1;
		identity = line(0,INF);
		minx = minx_;
		maxx = maxx_;
		cnt = 0;
		new_node(identity); // root id is 0
	}
	// only needed when "adding" lines lazily
	/*void apply(int id, line to_add_) {
		add[id] = add[id]+to_add_;
		cur[id] = cur[id]+to_add_;
	}*/
	// this method is needed even when no lazy is used, to avoid
	// null pointers and other problems in the code
	void push_lazy(int id) {
		if(L[id] == -1){
			new_node(identity);
			L[id] = cnt-1;
		}
		if(R[id] == -1){
			new_node(identity);
			R[id] = cnt-1;
		}
		// code below only needed when lazy ops are needed
		/*apply(L[id], add[id]);
		apply(R[id], add[id]);
		add[id] = line(0,0);*/
	}
	// only needed when "adding" lines lazily
	/*void push_line(int id, T tl, T tr) {
		T m = (tl+tr)/2;
		insert_line(L[id],cur[id],tl,m);
		insert_line(R[id],cur[id],m,tr);
		cur[id] = identity;
	}*/
	// O(log), or persistent return int instead of void
	void insert_line(int id, line new_line, T l, T r) {
		T m = (l+r) / 2;
		bool lef = new_line.f(l) < cur[id].f(l);
		bool mid = new_line.f(m) < cur[id].f(m);
		//~ uncomment for persistent
		//~ line to_push = new_line, to_keep = cur[id]; 
		//~ if(mid) swap(to_push,to_keep);
		if(mid) swap(new_line,cur[id]);
		
		if(r-l == 1){
			//~ uncomment for persistent
			//~ new_node(to_keep);
			//~ return cnt-1;
			return;
		}
		push_lazy(id);
		if(lef != mid){
			//~ uncomment for persistent
			//~ int lid = insert_line(L[id],to_push, l, m);
			//~ new_node(to_keep, lid, R[id]);
			//~ return cnt-1;
			insert_line(L[id],new_line,l,m);
		}else{
			//~ uncomment for persistent
			//~ int rid = insert_line(R[id],to_push, m, r);
			//~ new_node(to_keep, L[id], rid);
			//~ return cnt-1;
			insert_line(R[id],new_line,m,r);
		}
	}
	// for persistent, return int instead of void
	void insert_line(int id, line new_line) {
		insert_line(id,new_line*f,minx,maxx);
	}
	// O(log^2) doesn't support persistence
	void insert_segm(int id, line new_line, T l, T r, T tl, T tr){
		if(tr<=l || tl>=r || tl>=tr || l>=r) return;
		if(tl>=l && tr<=r){
			insert_line(id,new_line,tl,tr);
			return;
		}
		push_lazy(id);
		T m = (tl+tr)/2;
		insert_segm(L[id],new_line,l,r,tl,m);
		insert_segm(R[id],new_line,l,r,m,tr);
	}
	// [l,r)
	void insert_segm(int id, line new_line, T l, T r) {
		insert_segm(id,new_line*f,l,r,minx,maxx);
	}
	// O(log^2) doesn't support persistence
	/*void add_line(int id, line to_add_, T l, T r, T tl, T tr) {
		if(tr<=l || tl>=r || tl>=tr || l>=r) return;
		if(tl>=l && tr<=r){
			apply(id,to_add_);
			return;
		}
		push_lazy(id);
		push_line(id,tl,tr); // comment if insert isn't used
		T m = (tl+tr)/2;
		add_line(L[id],to_add_,l,r,tl,m);
		add_line(R[id],to_add_,l,r,m,tr);
	}
	void add_line(int id, line to_add_, T l, T r) {
		add_line(id,to_add_*f,l,r,minx,maxx);
	}*/
	// O(log) 
	T get(int id, T x, T tl, T tr) {
 		if(tl+1==tr) return cur[id].f(x);
		push_lazy(id); 
		T m = (tl+tr)/2;
		if(x < m) return min(cur[id].f(x), get(L[id], x, tl, m));
		else return min(cur[id].f(x), get(R[id], x, m, tr));
	}
	T get(int id, T x) {
		return get(id,x,minx,maxx)*f;
	}
};


int findfrom(int e, int r) {
	int L = 0, R = sz(v);
	while(L < R)
	{
		int M = (L+R)/2;
		if(v[M].snd >= r) L = M+1;
		else R = M;
	}
	return L;
}

int findto(int e, int r)
{
	if(v[0].fst > e) return 0;
	int L = 0, R = sz(v)-1;
	while(L < R)
	{
		int M = (L+R+1)/2;
		if(v[M].fst > e) R = M-1;
		else L = M;
	}
	return L+1;
}

int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	v.rsz(n);
	forn(i,n) cin >> v[i].fst >> v[i].snd;
	int q;
	cin >> q;
	li_chao lichao(false, 0, n);
	forn(asd,q) {
		char c;
		cin >> c;
		if(c == 's') {
			int idx;
			cin >> idx;
			cout << lichao.get(0, idx-1) << endl;
		}
		else {
			int e,r;
			cin >> e >> r;
			int from = findfrom(e,r);
			int to = findto(e,r);
			if(from < to) lichao.insert_segm(0, line(e,r), from, to);
		}
	}
	return 0;
}
