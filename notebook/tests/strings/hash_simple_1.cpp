//Problem: https://codeforces.com/contest/1418/problem/G
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
#else
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

// P should be a prime number, could be randomly generated,
// sometimes is good to make it close to alphabet size
// MOD[i] must be a prime of this order, could be randomly generated
const int P=1777771, MOD[2] = {999727999, 1070777777};
const int PI[2] = {325255434, 10018302}; // PI[i] = P^-1 % MOD[i]
struct Hash {
	ll h[2];
	vector<ll> vp[2];
	deque<int> x;
	Hash(vector<int>& s) {
		forn(i,sz(s)) x.pb(s[i]);
		forn(k, 2)
			vp[k].rsz(s.size()+1);
		forn(k, 2) {
			h[k] = 0; vp[k][0] = 1;
			ll p=1;
			forr(i, 1, sz(s)+1) {
				h[k] = (h[k] + p*s[i-1]) % MOD[k];
				vp[k][i] = p = (p*P) % MOD[k];
			}
		}
	}
	//Put the value val in position pos and update the hash value
	void change(int pos, int val) {
		forn(i,2)
			h[i] = (h[i] + vp[i][pos] * (val - x[pos] + MOD[i])) % MOD[i];
		x[pos] = val;
	}
	//Add val to the end of the current string
	void push_back(int val) {
		int pos = sz(x);
		x.pb(val);
		forn(k, 2)
		{
			assert(pos <= sz(vp[k]));
			if(pos == sz(vp[k])) vp[k].pb(vp[k].back()*P%MOD[k]);
			ll p = vp[k][pos];
			h[k] = (h[k] + p*val) % MOD[k];
		}
	}
	//Delete the first element of the current string
	void pop_front() {
		assert(sz(x) > 0);
		forn(k,2)
		{
			h[k] = (h[k] - x[0] + MOD[k]) % MOD[k];
			h[k] = h[k] * PI[k] % MOD[k];
		}
		x.pop_front();
	}
	ll getHashVal() {return (h[0]<<32)|h[1];}
};




int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	vector<int> v(n), cant(n, 0);
	forn(i,n)
	{
		cin >> v[i];
		v[i]--;
	}
	vector<vector<int>> posOfVal(n);
	vector<ll> curpos(n, 0), hvalOfPos(n);
	forn(i,n) posOfVal[v[i]].pb(i);
	Hash h(cant);
	unordered_map<ll, int> m;
	assert(h.getHashVal() == 0);
	m[h.getHashVal()]++;
	ll ans = 0;
	int pos = 0;
	bool fst = true;
	forn(i,n)
	{
		if(curpos[v[i]] >= 3)
		{
			if(fst) m[0]--;
			fst = false;
			int posto = posOfVal[v[i]][curpos[v[i]]-3];
			while(pos < posto) m[hvalOfPos[pos++]]--;
		}
		cant[v[i]]++;
		cant[v[i]]%=3;
		h.change(v[i], cant[v[i]]);
		ll hval = h.getHashVal();
		ans += m[hval]++;
		hvalOfPos[i] = hval;
		curpos[v[i]]++;
	}
	cout << ans << '\n';
	return 0;
}
