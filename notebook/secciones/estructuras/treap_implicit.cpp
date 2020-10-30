// An array represented as a treap, where the "key" is the index.
// However, the key is not stored explicitly, but can be calculated as
// the sum of the sizes of the left child of the ancestors where the node
// is in the right subtree of it.
// (commented parts are specific to range sum queries and other problems)
// rng = random number generator, works better than rand in some cases
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef struct item *pitem;
struct item {
	int pr, cnt, val;
	bool rev;
//	int sum; // (paramters for range query)
//	int add; // (parameters for lazy prop)
	pitem l, r;
//	pitem p; // ptr to parent, for getPos
	item(int val) : pr(rng()), cnt(1), val(val), rev(false),/* sum(val),
					 add(0),*/ l(NULL), r(NULL), /*p(NULL)*/{}
};
void push(pitem node) {
	if(node){
		if(node->rev) {
			swap(node->l, node->r);
			if(node->l) node->l->rev ^= true;
			if(node->r) node->r->rev ^= true;
			node->rev = false;
		}
		/*node->val += node->add; node->sum += node->cnt * node->add;
		if(node->l) node->l->add += node->add;
		if(node->r) node->r->add += node->add;
		node->add = 0;*/
	}
}
int cnt(pitem t) {return t ? t->cnt : 0;}
// int sum(pitem t) {return t ? push(t), t->sum : 0;}
void upd_cnt(pitem t) {
	if(t) {
		t->cnt = cnt(t->l) + cnt(t->r) + 1;
		//t->sum=t->val+sum(t->l)+sum(t->r); // for range sum
		/*if(t->l) t->l->p = t; // for getPos
		if(t->r) t->r->p = t;
		t->p = NULL;*/
	}
}
void split(pitem node, pitem& L, pitem& R, int sz) {// sz: wanted size for L
	if(!node) {L = R = 0; return;}							// O(log)
	push(node);
	//If node's left child has at least sz nodes, go left
	if(sz <= cnt(node->l)) split(node->l, L, node->l, sz), R = node;
	//Else, go right changing wanted sz
	else split(node->r, node->r, R, sz-1-cnt(node->l)), L = node;
	upd_cnt(node);
}
void merge(pitem& result, pitem L, pitem R) {// O(log)
	push(L); push(R);
	if(!L || !R) result = L ? L : R;
	else if(L->pr > R->pr) merge(L->r, L->r, R), result = L;
	else merge(R->l, L, R->l), result = R;
	upd_cnt(result);
}
void insert(pitem& node, pitem x, int pos) {// 0-index O(log)
	pitem l,r;
	split(node, l, r, pos);
	merge(l, l, x);
	merge(node, l, r);
}
void erase(pitem& node, int pos) {// 0-index O(log)
	if(!node) return;
	push(node);
    if(pos == cnt(node->l)) merge(node, node->l, node->r);
    else if(pos < cnt(node->l)) erase(node->l, pos);
    else erase(node->r, pos-1-cnt(node->l));
    upd_cnt(node);
}
void reverse(pitem &node, int L, int R) {//[L, R) O(log)
    pitem t1, t2, t3;
    split(node, t1, t2, L);
    split(t2, t2, t3, R-L);
    t2->rev ^= true;
    merge(node, t1, t2);
    merge(node, node, t3);
}
/*void add(pitem &node, int L, int R, int x) {//[L, R) O(log)
	pitem t1, t2, t3;
	split(node, t1, t2, L);
	split(t2, t2, t3, R-L);
	t2->add += x;
	merge(node, t1, t2);
	merge(node, node, t3);
}*/
/*int get(pitem &node, int L, int R) {//[L, R) O(log)
	pitem t1, t2, t3;
	split(node, t1, t2, L);
	split(t2, t2, t3, R-L);
	push(t2);
	int ret = t2->sum;
	merge(node, t1, t2);
	merge(node, node, t3);
	return ret;
}*/
/*/void push_all(pitem t){
	if(t->p)push_all(t->p);
	push(t);
}
pitem getRoot(pitem t, int& pos){ // get root and position for node t
	push_all(t);
	pos=cnt(t->l);
	while(t->p){
		pitem p=t->p;
		if(t==p->r)pos+=cnt(p->l)+1;
		t=p;
	}
	return t;
}*/
void output(pitem t){ // useful for debugging
    if(!t)return;
    push(t);
    output(t->l);cout << ' ' << t->val;output(t->r);
}
