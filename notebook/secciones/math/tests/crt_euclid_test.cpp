// https://codeforces.com/contest/724/problem/C
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef ANARAP
//local
#else
//judge
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

// ecuacion diofantica lineal
// sea d = gcd(a,b); la ecuacion a * x + b * y = c tiene soluciones enteras si
// d|c. La siguiente funcion nos sirve para esto. De forma general sera:
// x = x0 + (b/d)n			x0 = x*c/d
// y = y0 - (a/d)n			y0 = y*c/d
// la funcion devuelve d

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

// Chinese remainder theorem (special case): find z such that
// z % m = a, z % n = b.  Here, z is unique modulo M = lcm(m, n)
// Returns -1 when there is no solution 
// CRT is associative

ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y);
  if ((a - b) % g != 0) return -1; // uncomment to get RTE when there is no solution
  assert((a - b) % g == 0);
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}
 
int main() {
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out","w", stdout);
	#endif
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	const ll inf = 1e18;
	
	ll n,m,k;
	cin>>n>>m>>k;
	
	while(k--){
		ll x,y;
		cin>>x>>y;
		vector<pair<ll,ll>> vaux = {{x,y}, {2*n - x , y}, {2 * n - x , 2 * m - y}, {x, 2 * m - y}};
		ll ret = inf;
		for(auto [a,b]: vaux){
			auto d = crt(a,2*n,b,2*m);
			if(d == -1) continue;
			ret = min(ret,d);
		}
		cout<<(ret == inf ? -1 : ret)<<'\n';
	}
	
	return 0;
}
