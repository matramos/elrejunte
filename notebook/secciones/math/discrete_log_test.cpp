// https://codeforces.com/gym/101853/problem/G
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

ll expMod(ll b,ll e,ll m) //O(log e)
{
	if(!e) return 1;
	ll q=expMod(b,e/2,m);
	q=q*q%m; // or q=mulMod(q,q,m); if needed
	return e%2? b*q%m : q; // or e%2? mulMod(b,q,m) : q;
}

// O(sqrt(m)*log(m))
//returns x such that a^x = b (mod m) or -1 if inexistent
ll discrete_log(ll a,ll b,ll m) {
    a%=m, b%=m;
    if(b == 1) return 0;
    int cnt=0;
    ll tmp=1;
    for(ll g=__gcd(a,m);g!=1;g=__gcd(a,m)) {
        if(b%g) return -1;
        m/=g, b/=g;
        tmp = tmp*a/g%m;
        ++cnt;
        if(b == tmp) return cnt;
    }
    map<ll,int> w;
    int s = (int)ceil(sqrt(m));
    ll base = b;
    forn(i,s) {
        w[base] = i;
        base=base*a%m;
    }
    base=expMod(a,s,m);
    ll key=tmp;
    forr(i,1,s+2) {
        key=base*key%m;
        if(w.count(key)) return i*s-w[key]+cnt;
    }
    return -1;
}

int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	forn(T,t)
	{
		int a,b,m;
		cin >> a >> b >> m;
		cout << discrete_log(a,b,m) << '\n';
	}
	return 0;
}
