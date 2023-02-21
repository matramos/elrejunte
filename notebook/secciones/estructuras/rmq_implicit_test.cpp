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

typedef int T;

T ope (T a, T b) {
	return a+b;
}

const T neut = 0;

// Compressed segtree, it works for any range (even negative indexes)
struct RMQ {
	RMQ *lc, *rc;
	T ret;
	int L, R;
	RMQ(int l, int r, T x = neut) {
		lc = rc = nullptr;
		L = l; R = r; ret = x;
	}
	RMQ(int l, int r, RMQ* lp, RMQ* rp) {
		if(lp->L > rp->L) swap(lp, rp);
		lc = lp; rc = rp;
		L = l; R = r;
		ret = ope(lp->ret, rp->ret);
	}
	// O(log(R-L))
	// This operation inserts at most 2 nodes to the tree, i.e. the
	// total memory used by the tree is O(N), where N is the number
	// of times this 'set' function is called.
	void set(int p, T x) {
		if(L + 1 == R) { ret = x; return; }
		int m = (L+R) / 2;
		RMQ** c = p < m ? &lc : &rc;
		if(!*c) *c = new RMQ(p, p+1, x);
		else if((*c)->L <= p && p < (*c)->R) (*c)->set(p,x);
		else {
			int l = L, r = R;
			while((p < m) == ((*c)->L < m)) {
				if(p < m) r = m;
				else l = m;
				m = (l+r)/2;
			}
			*c = new RMQ(l, r, *c, new RMQ(p, p+1, x));
			// The code above, inside this else block, could be
			// replaced by the following 2 lines when the complete
			// range has the form [0, 2^k)
			//int rm = (1<<(32-__builtin_clz(p^(*c)->L)))-1;
			//*c = new RMQ(p & ~rm, (p | rm)+1, *c, new RMQ(p, p+1, x));
		}
		ret = ope(lc ? lc->ret : neut, rc ? rc->ret : neut);
	}
	// O(log(R-L))
	T get(int ql, int qr) {
		if(L >= qr || R <= ql) return neut;
		if(L >= ql && R <= qr) return ret;
		return ope(lc ? lc->get(ql,qr) : neut, rc ? rc->get(ql,qr) : neut);
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
	
	RMQ st(0, MAXN);
	vector<ll> pre(n);
	forn(i,n){
		pre[i] = st.get(arr[i]+1,MAXN);
		st.set(arr[i],st.get(arr[i],arr[i]+1)+1);
	}

	st = RMQ(0, MAXN);
	
	ll ans = 0;
	dforn(i,n){
		ans += pre[i]*st.get(0,arr[i]);
		st.set(arr[i],st.get(arr[i],arr[i]+1)+1);
	}
	cout << ans << "\n";
	
	return 0;
}

