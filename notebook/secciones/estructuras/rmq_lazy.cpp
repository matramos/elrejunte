typedef ll Elem;
typedef ll Alt;
const Elem neutro = 0;
const Alt neutro2 = 0;
Elem oper(const Elem& a, const Elem& b) { return a+b; }
struct ST{
	int sz;
	vector<Elem> t;
	vector<Alt> dirty; // Alt and Elem could be different types
	ST(int n) {
		sz = 1 << (32-__builtin_clz(n));
		t = vector<Elem>(2*sz, neutro);
		dirty = vector<Alt>(2*sz, neutro);
	}
	Elem &operator[](int p) { return t[sz+p]; }
	void updall() { dforn(i, sz) t[i] = oper(t[2*i], t[2*i+1]); }
	void push(int n, int a, int b) { // push dirt to n's child nodes
		if(dirty[n] != neutro2) { // n = node of range [a,b)
			t[n] += dirty[n]*(b-a); // CHANGE for your problem
			if(n < sz) {
				dirty[2*n] += dirty[n]; // CHANGE for your problem
				dirty[2*n+1] += dirty[n]; // CHANGE for your problem
			}
			dirty[n] = neutro2;
		}
	}
	Elem get(int i, int j, int n, int a, int b) { //O(lgn)
		if(j <= a || i >= b) return neutro;
		push(n, a, b); // adjust value before using it
		if(i <= a && b <= j) return t[n]; // n = node of range [a,b)
		int c = (a+b)/2;
		return oper(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	Elem get(int i, int j) { return get(i, j, 1, 0, sz); }
	//altera los valores en [i, j) con una alteracion de val
	void update(Alt val, int i, int j, int n, int a, int b) {//O(lgn)
		push(n, a, b);
		if(j <= a || i >= b) return;
		if(i <= a && b <= j) {
			dirty[n] += val; // CHANGE for your problem
			push(n, a, b);
			return;
		}
		int c = (a+b)/2;
		update(val, i, j, 2*n, a, c), update(val, i, j, 2*n+1, c, b);
		t[n] = oper(t[2*n], t[2*n+1]);
	}
	void update(Alt val, int i, int j){update(val,i,j,1,0,sz);}
};//Use: definir operacion, neutros, Alt, Elem, uso de dirty
//cin >> n; ST st(n); forn(i,n) cin >> st[i]; st.updall()
