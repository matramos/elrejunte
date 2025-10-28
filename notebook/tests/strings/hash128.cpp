//Problem: https://www.spoj.com/problems/PLD/
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
#define MAXN 30010

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

typedef __int128 bint; // needs gcc compiler?
const bint MOD=212345678987654321LL, P=1777771, PI=106955741089659571LL;
struct Hash {
	vector<bint> h, pi;
	Hash(string& s) {
		assert((P*PI)%MOD == 1);
		h.resize(s.size()+1); pi.resize(s.size()+1);
		h[0]=0; pi[0]=1;
		bint p=1;
		forr(i, 1, sz(s)+1) {
			h[i] = (h[i-1] + p*s[i-1]) % MOD;
			pi[i] = (pi[i-1] * PI) % MOD;
			p = (p*P) % MOD;
		}
	}
	ll get(int s, int e){ // get hash value of the substring [s, e)
		return (((h[e]-h[s]+MOD)%MOD)*pi[s])%MOD;
	}
};

int main()
{
	#ifdef REJUNTE
	freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int k,ans=0;
	string s,rs;
	cin >> k >> s;
	rs = s;
	reverse(rs.begin(), rs.end());
	Hash h(s), rh(rs);
	forn(i,sz(s)-k+1) if(h.get(i, i+k) == rh.get(sz(s)-i-k,sz(s)-i)) ans++;
	cout << ans << '\n';
	return 0;
}
