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

const int N_DEL = 0, N_VAL = 0; // neutral elements for delta & values
inline int u_oper(int x, int y){ return x + y; } // update operation
inline int q_oper(int lval, int rval){ return lval + rval; } // query operation
inline int u_segm(int d, int len){ return d==N_DEL ? N_DEL : d*len; } // update segment
inline int u_delta(int d1, int d2){ // update delta
  if(d1==N_DEL) return d2;
  if(d2==N_DEL) return d1;
  return u_oper(d1, d2);
}
inline int a_delta(int v, int d){ // apply delta
	return d==N_DEL ? v : u_oper(d, v);
}

struct node_t{
  int szi, n_val, t_val, d;
  bool rev;
  node_t *c[2], *p;
  node_t(int v) : szi(1), n_val(v), t_val(v), d(N_DEL), rev(0), p(0){
    c[0]=c[1]=0;
  }
  bool is_root(){return !p || (p->c[0] != this && p->c[1] != this);}
  void push(){
    if(rev){
      rev=0; swap(c[0], c[1]);
      forr(x,0,2) if(c[x]) c[x]->rev^=1;
    }
    n_val = a_delta(n_val, d); t_val=a_delta(t_val, u_segm(d, szi));
    forr(x,0,2) if(c[x]) 
		c[x]->d = u_delta(d, c[x]->d);
    d=N_DEL;
  }
  void upd();
};
typedef node_t* node;
int get_sz(node r){return r ? r->szi : 0;}
int get_tree_val(node r){
  return r ? a_delta(r->t_val, u_segm(r->d,r->szi)) : N_VAL;
}
void node_t::upd(){
  t_val = q_oper(q_oper(get_tree_val(c[0]), a_delta(n_val, d)), get_tree_val(c[1]));
  szi = 1 + get_sz(c[0]) + get_sz(c[1]);
}
void conn(node c, node p, int is_left){ 
	if(c) c->p = p; 
	if(is_left>=0) p->c[!is_left] = c; 
}
void rotate(node x){
  node p = x->p, g = p->p;
  bool gCh=p->is_root(), is_left = x==p->c[0];
  conn(x->c[is_left],p,is_left); 
  conn(p,x,!is_left);
  conn(x,g,gCh?-1:(p==g->c[0])); 
  p->upd();
}
void splay(node x){ 
  while(!x->is_root()){
    node p = x->p, g = p->p;
    if(!p->is_root()) g->push();
    p->push(); x->push();
    if(!p->is_root()) rotate((x==p->c[0])==(p==g->c[0])? p : x);
    rotate(x);
  }
  x->push(); x->upd();
}

/* Link Cut Tree
Keep information of a tree (or forest) and allow to make many types of operations 
(see them below) in an efficient way. Internally, each node of the tree will have 
at most 1 "preferred" child, and as a consequence, the tree can be seen as a set 
of independent "preferred" paths. Each of this paths is basically a list, represented
with a splay tree, where the "implicit key" (for the BST) of each element is the depth 
of the corresponding node in the original tree (or forest). Also, each of these preferred 
paths (except one of them), will know who its "father path" is, i.e. will know the 
preferred path of the father of the top-most node of this path.
*/

// Make the path from the root to x to be an "preferred path", and also make x 
// to be the root of its splay tree (not the root of the original tree).
node expose(node x){ 
  node last = 0;
  for(node y=x; y; y=y->p) 
	splay(y), y->c[0] = last, y->upd(), last = y;
  splay(x);
  return last;
}
void make_root(node x){expose(x);x->rev^=1;}
node get_root(node x){
	expose(x); 
	while(x->c[1]) x = x->c[1]; 
	splay(x); 
	return x;
}
node lca(node x, node y){expose(x); return expose(y);}
bool connected(node x, node y){
	expose(x); expose(y); 
	return x==y ? 1 : x->p!=0; 
}
// makes x son of y
void link(node x, node y){ make_root(x); x->p=y; }
void cut(node x, node y){ make_root(x); expose(y); y->c[1]->p=0; y->c[1]=0; }
node father(node x){
	expose(x);
	node r = x->c[1];
	if(!r) return 0;
	while(r->c[0]) r = r->c[0];
	return r;
}
// cuts x from its father keeping tree root
void cut(node x){ expose(father(x)); x->p = 0; }
int query(node x, node y){
	make_root(x); expose(y); 
	return get_tree_val(y);
}
void update(node x, node y, int d){
	make_root(x); expose(y); y->d=u_delta(y->d,d);
}
node lift_rec(node x, int k){
	if(!x) return 0;
	if(k == get_sz(x->c[0])){ splay(x); return x; }
	if(k < get_sz(x->c[0])) return lift_rec(x->c[0],k);
	return lift_rec(x->c[1], k-get_sz(x->c[0])-1);
}
// k-th ancestor of x (lift(x,1) is x's father)
node lift(node x, int k){ expose(x);return lift_rec(x,k); }
// distance from x to its tree root
int depth(node x){ expose(x);return get_sz(x)-1; }

int main () {
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, q; cin >> n >> q;
	vector<node> tree; forn(i,n) tree.pb(new node_t(i));
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
