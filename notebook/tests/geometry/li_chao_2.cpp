#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = a; i<b; i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i = n-1; i>-1; i--)
#define forall(i,v) for(auto i = v.begin(); i != v.end(); i++)
#define sz(v) ((int) v.size()) 
#define pb push_back
#define fst first
#define snd second
#define lb lower_bound
#define ub upper_bound
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef ll T;
const T INF = -1e18;

struct line{
	T m, b;
	line(){}
	line(T m_, T b_){ m = m_; b = b_; }
	T f(T x){ return m*x + b; }
	line operator+(line l) { return line(m+l.m, b+l.b); }
	line operator*(T k) { return line(m*k, b*k); }
};

struct li_chao {
	vector<line> cur, add;
	vector<int> L, R;
	T f, minx, maxx;
	line identity;
	int cnt;
	
	void clear(){
		cur.clear();
		add.clear();
		L.clear();
		R.clear();
	}
	
	void new_node(line cur_, int l=-1, int r=-1){
		cur.pb(cur_);
		add.pb(line(0,0));
		L.pb(l); R.pb(r);
		cnt++;
	}
	
	li_chao(bool min_, T minx_, T maxx_){ // for min, min_=1 otherwise min_0
		f = min_ ? 1 : -1;
		identity = line(0,0);
		minx = minx_;
		maxx = maxx_;
		cnt = 0;
		new_node(identity);
	}
	
	void apply(int id, line to_add_) {
		add[id] = add[id]+to_add_;
		cur[id] = cur[id]+to_add_;
	}
	
	void push_lazy(int id){
		if(L[id] == -1){
			new_node(identity);
			L[id] = cnt-1;
		}
		if(R[id] == -1){
			new_node(identity);
			R[id] = cnt-1;
		}
		apply(L[id], add[id]);
		apply(R[id], add[id]);
		add[id] = line(0,0);
	}
	
	void push_line(int id, T tl, T tr) {
		T m = (tl+tr)/2;
		insert_line(L[id],cur[id],tl,m);
		insert_line(R[id],cur[id],m,tr);
		cur[id] = identity;
	}
	
	// O(log)
	void insert_line(int id, line new_line, T l, T r){ // for persistent use int instead of void
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
	void insert_line(int id, line new_line) { // for persistent, use int instead of void
		insert_line(id,new_line*f,minx,maxx);
	}
	
	// O(log^2) doesn't support persistence
	void insert_segm(int id, line new_line, T l, T r, T tl, T tr){
		if(tr<=l || tl>=r || tl>=tr || l>=r) return;
		if(tl>=l && tr<=r){
			insert_segm(id,new_line,tl,tr);
			return;
		}
		push_lazy(id);
		T m = (tl+tr)/2;
		insert_segm(L[id],new_line,l,r,tl,m);
		insert_segm(R[id],new_line,l,r,m,tr);
	}
	void insert_segm(int id, line new_line, T l, T r) {
		insert_segm(id,new_line*f,l,r,minx,maxx);
	}
	
	// O(log^2) doesn't support persistence
	void add_line(int id, line to_add_, T l, T r, T tl, T tr) {
		if(tr<=l || tl>=r || tl>=tr || l>=r) return;
		if(tl>=l && tr<=r){
			apply(id,to_add_);
			return;
		}
		push_lazy(id);
		//~ push_line(id,tl,tr);
		T m = (tl+tr)/2;
		add_line(L[id],to_add_,l,r,tl,m);
		add_line(R[id],to_add_,l,r,m,tr);
	}
	void add_line(int id, line to_add_, T l, T r) {
		add_line(id,to_add_*f,l,r,minx,maxx);
	}
	
	// O(log) 
	T get(int id, T x, T tl, T tr){
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

void update(li_chao &li, T l, T k) {
	if(max(0LL,l-(k-1)) < l) li.add_line(0,line(1,k-l), max(0LL,l-(k-1)), l);
	if(l+1 < min(200000LL,l+k)) li.add_line(0,line(-1,k+l), l+1, min(200000LL,l+k));
	li.add_line(0,line(0,k), l, l+1);
}

int main () {
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	T h;
	li_chao sum(false,0,200000), cur(false,0,200000);
	T q; cin >> q;
	forn(i,q) {
		char ope; cin >> ope;
		if(ope == 'A') {
			T l, k; cin >> l >> k;
			update(sum,l,k);
			update(cur,l,k);
		}else if(ope == 'B') {
			T l; cin >> l;
			
			T ft = sum.get(0,l);
			T fc = cur.get(0,l);
			cout << min(h,ft-fc) + fc << "\n";
		}else{
			cin >> h;
			cur.clear();
			cur = li_chao(false,0,200000);
		}
	}
	
	#ifdef JP
		cerr << "Time elapsed: " <<  clock() * 1000 / CLOCKS_PER_SEC << " ms\n";
	#endif
}
