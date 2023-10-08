// https://codeforces.com/contest/61/problem/E
#include<bits/stdc++.h>
#define forr(i,a,b) for(int i = a; i<b; i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i = n-1; i>-1; i--)
#define pb push_back
#define sz(v) v.size()

using namespace std;

typedef long long ll;

const int MAXN = 1<<30;

typedef int tipo;
const tipo neutro = 0;
tipo oper(const tipo& a, const tipo& b) { return a+b; }
// Compressed segtree, it works for any range (even negative indexes)
struct ST {
	ST *lc, *rc;
	tipo val;
	int L, R;
	ST(int l, int r, tipo x = neutro) {
		lc = rc = nullptr;
		L = l; R = r; val = x;
	}
	ST(int l, int r, ST* lp, ST* rp) {
		if(lp != nullptr && rp != nullptr && lp->L > rp->L) swap(lp, rp);
		lc = lp; rc = rp;
		L = l; R = r;
		val = oper(lp==nullptr?neutro : lp->val, rp==nullptr?neutro : rp->val);
	}
	// O(log(R-L))
	// This operation inserts at most 2 nodes to the tree, i.e. the
	// total memory used by the tree is O(N), where N is the number
	// of times this 'set' function is called. (2*log nodes when persistent)
	// parameter 'isnew' only needed when persistent
	void set(int p, tipo x, bool isnew = false) { // return ST* for persistent
		// uncomment for persistent
		/*if(!isnew) {
			ST* newnode = new ST(L, R, lc, rc);
			return newnode->set(p, x, true);
		}*/
		// might need to CHANGE val = x with something else
		if(L + 1 == R) { val = x; return; } // 'return this;' for persistent
		int m = (L+R) / 2;
		ST** c = p < m ? &lc : &rc;
		if(!*c) *c = new ST(p, p+1, x);
		else if((*c)->L <= p && p < (*c)->R) {
			// replace by comment for persistent
			(*c)->set(p,x);
			//*c = (*c)->set(p,x);
		}
		else {
			int l = L, r = R;
			while((p < m) == ((*c)->L < m)) {
				if(p < m) r = m;
				else l = m;
				m = (l+r)/2;
			}
			*c = new ST(l, r, *c, new ST(p, p+1, x));
			// The code above, inside this else block, could be
			// replaced by the following 2 lines when the complete
			// range has the form [0, 2^k)
			//int rm = (1<<(32-__builtin_clz(p^(*c)->L)))-1;
			//*c = new ST(p & ~rm, (p | rm)+1, *c, new ST(p, p+1, x));
		}
		val = oper(lc ? lc->val : neutro, rc ? rc->val : neutro);
		//return this; // uncomment for persistent
	}
	// O(log(R-L))
	tipo get(int ql, int qr) {
		if(qr <= L || R <= ql) return neutro;
		if(ql <= L && R <= qr) return val;
		return oper(lc ? lc->get(ql,qr) : neutro, rc ? rc->get(ql,qr) : neutro);
	}
};
// Usage: 1- RMQ st(MIN_INDEX, MAX_INDEX) 2- normally use set/get

int main(){
	#ifdef ANARAP
		freopen("input.in","r",stdin);
	#endif
	ios::sync_with_stdio();
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int n; cin >> n;
	vector<int> arr(n); forn(i,n) cin >> arr[i];
	
	ST st(0, MAXN);
	vector<ll> pre(n);
	forn(i,n){
		pre[i] = st.get(arr[i]+1,MAXN);
		st.set(arr[i],st.get(arr[i],arr[i]+1)+1);
	}

	st = ST(0, MAXN);
	
	ll ans = 0;
	dforn(i,n){
		ans += pre[i]*st.get(0,arr[i]);
		st.set(arr[i],st.get(arr[i],arr[i]+1)+1);
	}
	cout << ans << "\n";
	
	return 0;
}

