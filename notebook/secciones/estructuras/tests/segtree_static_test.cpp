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
typedef int tipo;

struct RMQ{
	#define LVL 18 // LVL such that 2^LVL>n
	tipo vec[LVL][1<<(LVL+1)]; 
	tipo &operator[](int p) {return vec[0][p];}
	tipo get(int i, int j) {//intervalo [i,j)
		int p = 31 - __builtin_clz(j-i);
		return min(vec[p][i], vec[p][j-(1<<p)]);
	}
	void build(int n) {//O(nlogn)
		int mp = 31 - __builtin_clz(n);
		forn(p, mp) forn(x, n-(1<<p))
			vec[p+1][x] = min(vec[p][x], vec[p][x+(1<<p)]);
	}
}; //Use: define LVL y tipo; insert data with []; call build; answer queries


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
	RMQ rmq;
	cin >> n;
	forn(i,n) cin >> rmq[i];
	rmq.build(n);
	cin >> q;
	forn(i,q)
	{
		int a,b;
		cin >> a >> b;
		cout << rmq.get(a,b+1) << '\n';
	}
	return 0;
}