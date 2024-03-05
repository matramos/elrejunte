// https://www.spoj.com/problems/DYNACON1/
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = a; i<b; i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i = n-1; i>-1; i--)
#define forall(i,v) for(auto i = v.begin(); i != v.end(); i++)
#define sz(v) int(v.size()) 
#define pb push_back
#define fst first
#define snd second
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

const int N_DEL = 0, N_VAL = 0; // neutral elem for delta, value
inline int update(int x, int y){ return x+y; } // update 
inline int get(int lval, int rval){ return lval + rval; } // query
inline int segm_delta(int d, int len){ return d==N_DEL ? N_DEL : d*len; } // how to calc the delta on a segment
inline int update_delta(int d1, int d2){ // update delta
	if(d1==N_DEL) return d2; 
	if(d2==N_DEL) return d1;
	return update(d1, d2);
}
inline int update_node(int v, int d){ // update node value
	return d==N_DEL ? v : update(v, d);
}

// splay tree
struct Node_t {
	int sz, n_val, t_val, d;
	bool rev;
	Node_t *c[2], *p;
	Node_t(int v_) : n_val(v_), t_val(v_), d(N_DEL), rev(0), p(0){
		sz = 1;
		c[0]=c[1]=0;
	}
	bool is_root(){ return !p || (p->c[0] != this && p->c[1] != this); }
	void push(){
		if(rev){
			rev=0; swap(c[0], c[1]);
			forr(x,0,2) if(c[x]) c[x]->rev ^= 1;
		}
		n_val = update_node(n_val, d); t_val = update_node(t_val, segm_delta(d, sz));
		forr(x,0,2) if(c[x]) c[x]->d = update_delta(c[x]->d, d);
		d = N_DEL;
	}
	void upd();
};
typedef Node_t* Node;
int get_sz(Node r){ return r ? r->sz : 0; }
int get_tree_val(Node r){
	return r ? update_node(r->t_val, segm_delta(r->d, r->sz)) : N_VAL;
}
void Node_t::upd(){
  t_val = get(get(get_tree_val(c[0]), update_node(n_val, d)), get_tree_val(c[1]));
  sz = 1 + get_sz(c[0]) + get_sz(c[1]);
}
void conn(Node c, Node p, int is_left) { 
	if(c) c->p = p;
	if(is_left>=0) p->c[!is_left] = c;
}
void rotate(Node x){
	Node p = x->p, g = p->p;
	bool gCh = p->is_root(), is_left = x==p->c[0];
	conn(x->c[is_left],p,is_left); 
	conn(p,x,!is_left);
	conn(x,g,gCh?-1:(p==g->c[0])); 
	p->upd();
}
void splay(Node x){
	while(!x->is_root()){
		Node p = x->p, g = p->p;
		if(!p->is_root()) g->push();
		p->push(); x->push();
		if(!p->is_root()) rotate((x==p->c[0])==(p==g->c[0]) ? p : x);
		rotate(x);
	}
	x->push(); x->upd();
}

// link cut tree
Node expose(Node x){
	Node last=0;
	for(Node y=x; y; y = y->p)
		splay(y), y->c[0]=last, y->upd(), last=y;
	splay(x);
	return last;
}
void make_root(Node x){ expose(x); x->rev^=1; }
Node get_root(Node x) {
	expose(x); 
	while(x->c[1]) x = x->c[1]; 
	splay(x);
	return x;
}
Node lca(Node x, Node y){ expose(x); return expose(y); }
bool connected(Node x, Node y){
	expose(x); expose(y); 
	return x==y ? 1 : x->p != 0;
}
void link(Node x, Node y){ make_root(x); x->p=y; } // make x son of y
void cut(Node x, Node y){
	make_root(x); expose(y); 
	y->c[1]->p = 0; y->c[1] = 0;
}
Node father(Node x){
	expose(x);
	Node r=x->c[1];
	if(!r) return 0;
	while(r->c[0]) r = r->c[0];
	return r;
}
// cuts x from father keeping tree root
void cut(Node x){ expose(father(x)); x->p = 0;  }
int query(Node x, Node y) { 
	make_root(x); expose(y); 
	return get_tree_val(y); 
}
void update(Node x, Node y, int d){
	make_root(x); expose(y);
	y->d = update_delta(y->d,d);
}
Node lift_rec(Node x, int k){
	if(!x)return 0;
	if(k == get_sz(x->c[0])){ splay(x); return x; }
	if(k < get_sz(x->c[0])) return lift_rec(x->c[0], k);
	return lift_rec(x->c[1], k-get_sz(x->c[0])-1);
}
// k-th ancestor of x (lift(x,1) is x's father)
Node lift(Node x, int k){ expose(x); return lift_rec(x,k); }
// distance from x to its tree root
int depth(Node x){ expose(x); return get_sz(x)-1; }


int main () {
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, q; cin >> n >> q;
	vector<Node> tree; forn(i,n) tree.pb(new Node_t(i));
	forn(i,q) {
		string op; cin >> op;
		int u,v; cin >> u >> v; u--,v--;
		if(op == "conn") {
			cout << (connected(tree[u], tree[v]) ? "YES" : "NO") << "\n";
		}else if(op == "add") {
			link(tree[u],tree[v]);
		}else {
			cut(tree[u],tree[v]);
		}
	}
	
	#ifdef JP
		cerr << "Time elapsed: " <<  clock() * 1000 / CLOCKS_PER_SEC << " ms\n";
	#endif
}
