// https://cses.fi/problemset/task/1651
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

int main()
{
	#ifdef ANARAP
		freopen("input.in","r",stdin);
		//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,q;
	cin >> n >> q;
	ST st(n);
	forn(i,n) cin >> st[i];
	st.updall();
	forn(_,q)
	{
		int t,a;
		cin >> t >> a;
		a--;
		if(t == 1)
		{
			int b,x;
			cin >> b >> x;
			st.update(x,a,b);
		}
		else cout << st.get(a,a+1) << '\n';
	}
	return 0;
}
