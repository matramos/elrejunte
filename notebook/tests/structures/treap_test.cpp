//Problem: https://acm.timus.ru/problem.aspx?space=1&num=1439
#include <bits/stdc++.h>
#define sqr(a) ((a)*(a))
#define rsz resize
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

typedef struct item *pitem;
struct item {
    //pr = randomized priority, key = BST value, cnt = size of subtree
    int pr, key, cnt;
    pitem l, r;
    item(int key) : key(key), pr(rand()), cnt(1), l(NULL), r(NULL) {}
};
int cnt(pitem node) {return node ? node->cnt : 0;}
void upd_cnt(pitem node) {if(node) node->cnt = cnt(node->l) + cnt(node->r) + 1;}
//splits t in l and r - l: <= key, r: > key
void split(pitem node, int key, pitem& L, pitem& R){ // O(log)
    if(!node) L = R = 0;
    // if cur > key, go left to split and cur is part of R
    else if(key < node->key) split(node->l, key, L, node->l), R = node;
    // if cur <= key, go right to split and cur is part of L
    else split(node->r, key, node->r, R), L = node;
    upd_cnt(node);
}
//1) go down the BST following the key of the new node (x), until
// you reach NULL or a node with lower pr than the new one.
//2.1) if you reach NULL, then put the new node there
//2.2) if you reach a node with lower pr, then split the subtree rooted at that
// node and put the new node there, using the split result as new node children
void insert(pitem& node, pitem x) { // O(log)
    if(!node) node = x;
    else if(x->pr > node->pr) split(node, x->key, x->l, x->r), node = x;
    else insert(x->key <= node->key ? node->l : node->r, x);
    upd_cnt(node);
}
//Assumes that the key of every element in L <= to the key of every element in R
void merge(pitem& result, pitem L, pitem R) { // O(log)
    //If one of the nodes is NULL, the merge result is the other node
    if(!L || !R) result = L ? L : R;
    //if L has higher priority than R, put L and update it's right child
    //with the merge result of L->r and R
    else if(L->pr > R->pr) merge(L->r, L->r, R), result = L;
    //if R has higher priority than L, put R and update it's left child
    //with the merge result of L and R->l
    else merge(R->l, L, R->l), result = R;
    upd_cnt(result);
}
//go down the BST following the key to erase. When the key is found,
//replace that node with the result of merging it children
void erase(pitem& node, int key) {// O(log), (erases only 1 repetition of key)
    if(node->key == key) merge(node, node->l, node->r);
    else erase(key < node->key ? node->l : node->r, key);
    upd_cnt(node);
}
//union of two treaps
void unite(pitem &t, pitem L, pitem R) { // O(M*log(N/M))
    if(!L || !R) {t = L ? L : R; return;}
    if(L->pr < R->pr) swap(L, R);
    pitem p1, p2; split(R, L->key, p1, p2);
    unite(L->l, L->l, p1); unite(L->r, L->r, p2);
    t = L; upd_cnt(t);
}
pitem kth(pitem t, int k) { // element at "position" k
    if(!t) return 0;
    if(k == cnt(t->l)) return t;
    return k < cnt(t->l) ? kth(t->l, k) : kth(t->r, k - cnt(t->l) - 1);
}
pair<int,int> lb(pitem t, int key) { // position and value of lower_bound
    if(!t) return {0,1<<30}; // (special value)
    if(key > t->key){
        auto w = lb(t->r,key); w.fst += cnt(t->l)+1; return w;
    }
    auto w = lb(t->l,key);
    if(w.fst == cnt(t->l)) w.snd = t->key;
    return w;
}

int main()
{
	#ifdef REJUNTE
	freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,q;
	pitem root = NULL;
	cin >> n >> q;
	forn(i,q)
	{
		char t;
		ll x,L,R,M;
		cin >> t >> x;
		L = x; R = 2e9;
		while(L<R)
		{
			M = (L+R)/2;
			if(M - lb(root, M+1).fst < x) L = M+1;
			else R = M;
		}
		if(t=='D') insert(root, new item(L));
		else cout << L << '\n';
	}
	return 0;
}