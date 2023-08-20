typedef int tipo;
const tipo neutro = 0;
tipo oper(const tipo& a, const tipo& b) { return a+b; }
// Compressed segtree, it works for any range (even negative indexes)
struct ST {
	ST *lc, *rc;
	tipo ret;
	int L, R;
	ST(int l, int r, tipo x = neutro) {
		lc = rc = nullptr;
		L = l; R = r; ret = x;
	}
	ST(int l, int r, ST* lp, ST* rp) {
		if(lp->L > rp->L) swap(lp, rp);
		lc = lp; rc = rp;
		L = l; R = r;
		ret = oper(lp->ret, rp->ret);
	}
	// O(log(R-L))
	// This operation inserts at most 2 nodes to the tree, i.e. the
	// total memory used by the tree is O(N), where N is the number
	// of times this 'set' function is called.
	void set(int p, tipo x) {
		// might need to CHANGE ret = x with something else
		if(L + 1 == R) { ret = x; return; }
		int m = (L+R) / 2;
		ST** c = p < m ? &lc : &rc;
		if(!*c) *c = new ST(p, p+1, x);
		else if((*c)->L <= p && p < (*c)->R) (*c)->set(p,x);
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
		ret = oper(lc ? lc->ret : neutro, rc ? rc->ret : neutro);
	}
	// O(log(R-L))
	tipo get(int ql, int qr) {
		if(L >= qr || R <= ql) return neutro;
		if(ql <= L && R <= qr) return ret;
		return oper(lc ? lc->get(ql,qr) : neutro, rc ? rc->get(ql,qr) : neutro);
	}
};
// Usage: 1- RMQ st(MIN_INDEX, MAX_INDEX) 2- normally use set/get
