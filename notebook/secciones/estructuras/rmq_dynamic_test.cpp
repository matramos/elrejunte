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

//Dado un arreglo y una operacion asociativa con neutro, get(i, j) opera sobre el rango [i, j).
#define MAXN 100010
#define operacion(x, y) ((x)+(y))
typedef ll tipo;
const tipo neutro=0;
struct RMQ {
	int sz;
	tipo t[4*MAXN];
	tipo &operator[](int p) {return t[sz+p];}
	void init(int n) {//O(nlgn)
		sz = 1 << (32 - __builtin_clz(n));
		forn(i, 2*sz) t[i] = neutro;
	}
	void updall() {dforn(i, sz) t[i]=operacion(t[2*i], t[2*i+1]);} //O(n)
	tipo get(int i, int j) {return get(i,j,1,0,sz);}
	tipo get(int i, int j, int n, int a, int b) {//O(lgn), n = node of range [a,b)
		if(j<=a || i>=b) return neutro;
		if(i<=a && b<=j) return t[n];
		int c = (a+b)/2;
		return operacion(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	void set(int p, tipo val) {//O(lgn)
		p+=sz;
		while(p>0 && t[p]!=val) {
			t[p]=val;
			p/=2;
			val=operacion(t[p*2], t[p*2+1]);
		}
	}
}; //Use: definir operacion tipo neutro y MAXN,
//cin >> n; rmq.init(n); forn(i, n) cin >> rmq[i]; rmq.updall();

int main()
{
	#ifdef REJUNTE
	freopen("input.in","r",stdin);
	freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,k;
	RMQ rmq;
	while(cin >> n >> k)
	{
		rmq.init(n);
		forn(i,n)
		{
			int x;
			cin >> x;
			if(x == 0) rmq[i] = -1e9;
			else if(x < 0) rmq[i] = 1;
			else rmq[i] = 0;
		}
		rmq.updall();
		forn(i,k)
		{
			char t;
			int a,b;
			cin >> t >> a >> b;
			a--;
			if(t == 'C')
			{
				if(b == 0) rmq.set(a, -1e9);
				else if(b < 0) rmq.set(a, 1);
				else rmq.set(a, 0);
			}
			else
			{
				ll aux = rmq.get(a, b);
				if(aux < 0) cout << '0';
				else if(aux%2 == 0) cout << '+';
				else cout << '-';
			}
		}
		cout << '\n';
	}
	return 0;
}