typedef int tipo;
const tipo neutro = 0;
tipo oper(const tipo& a, const tipo& b) { return a+b; }
struct ST {
	int n;
	vector<tipo> st;
	vector<int> L, R;
	ST(int nn): n(nn), st(1,neutro), L(1,0), R(1,0) {}
	int new_node(tipo v, int l = 0, int r = 0) {
		int id = sz(st);
		st.pb(v); L.pb(l); R.pb(r);
		return id;
	}
	int init(vector<tipo>& v, int l, int r) {
		if(l+1 == r) return new_node(v[l]);
		int m = (l+r)/2, a = init(v, l, m), b = init(v, m ,r);
		return new_node(oper(st[a], st[b]), a, b);
	}
	int update(int cur, int pos, int val, int l, int r) {
		int id = new_node(st[cur], L[cur], R[cur]);
		if(l+1 == r) { st[id] = val; return id; }
		int m = (l+r)/2, ASD; // MUST USE THE ASD!!!
		if(pos < m) ASD = update(L[id], pos, val, l, m), L[id] = ASD;
		else ASD = update(R[id], pos, val, m, r), R[id] = ASD;
		st[id] = oper(st[L[id]], st[R[id]]);
		return id;
	}
	tipo get(int cur, int from, int to, int l, int r) {
		if(to <= l || r <= from) return neutro;
		if(from <= l && r <= to) return st[cur];
		int m = (l+r)/2;
		return oper(get(L[cur], from, to, l, m), get(R[cur], from, to, m, r));
	}
	int init(vector<tipo>& v) { return init(v, 0, n); }
	int update(int root, int pos, int val) {
		return update(root, pos, val, 0, n);
	}
	tipo get(int root, int from, int to) {
		return get(root, from, to, 0, n);
	}
}; // usage: ST st(n); root = st.init(v) (or root = 0);
// new_root = st.update(root,i,x); st.get(root,l,r);
