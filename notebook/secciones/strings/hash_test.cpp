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

struct Hash {
	int P=1777771, MOD[2], PI[2];
	vector<int> h[2], pi[2];
	Hash(string& s) {
		MOD[0]=999727999; MOD[1]=1070777777;
		PI[0]=325255434; PI[1]=10018302;
		forn(k,2) h[k].resize(s.size()+1), pi[k].resize(s.size()+1);
		forn(k,2) {
			h[k][0]=0;pi[k][0]=1;
			ll p=1;
			forr(i, 1, s.size()+1) {
				h[k][i] = (h[k][i-1] + p*s[i-1]) % MOD[k];
				pi[k][i] = (1LL * pi[k][i-1] * PI[k]) % MOD[k];
				p = (p*P) % MOD[k];
			}
		}
	}
	ll get(int s, int e) { // get hash value of the substring [s, e)
		ll h0 = (h[0][e] - h[0][s] + MOD[0]) % MOD[0];
		h0 = (1LL * h0 * pi[0][s]) % MOD[0];
		ll h1 = (h[1][e] - h[1][s] + MOD[1]) % MOD[1];
		h1 = (1LL * h1 * pi[1][s]) % MOD[1];
		return (h0<<32)|h1;
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
	forn(i,s.size()-k+1) if(h.get(i, i+k) == rh.get(s.size()-i-k,s.size()-i)) ans++;
	cout << ans << '\n';
	return 0;
}