//Problema: https://codeforces.com/gym/102001/problem/C
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it, v) for(auto it =v.begin(); it!=v.end(); it++)
#define sz(c) ((int) c.size())
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
	deque<char> x;
	Hash(vector<char>& s) {
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



#define INF 1000100


int main(){
	#ifdef ANARAP
	freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);
	
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m,k;
	set<char> s;
	cin >> n >> m >> k;
	forn(i,m)
	{
		char c;
		cin >> c;
		s.insert(c);
	}
	map<ll, int> posOfHval;
	vector<char> ans;
	int from = 0;
	Hash h(ans);
	forn(i,n) ans.pb(*s.begin()), h.push_back(*s.begin());
	posOfHval[h.getHashVal()] = 0;
	//forn(i,sz(h.x)) cout << h.x[i]; cout << ": " << h.getHashVal() << '\n';
	while(sz(ans) - from < n+k-1)
	{
		int pos = INF;
		bool good = false;
		char c = '$';
		ll hval, poshval;
		h.pop_front();
		h.push_back('$');
		forall(it, s)
		{
			h.change(n-1, *it);
			hval = h.getHashVal();
			//forn(i,sz(h.x)) cout << h.x[i]; cout << ": " << hval << '\n';
			map<ll, int>::iterator ite = posOfHval.find(hval);
			if(ite == posOfHval.end())
			{
				c = *it;
				good = true;
				//cout << "good " << c << '\n';
				break;
			}
			if(ite->snd < pos)
			{
				c = *it;
				pos = ite->snd;
				poshval = hval;
			}
		}
		assert(c != '$');
		ans.pb(c);
		if(!good)
		{
			assert(pos == from);
			from++;
			hval = poshval;
			h.change(n-1, c);
		}
		posOfHval[hval] = sz(ans)-n;
	}
	forr(i,from,sz(ans)) cout << ans[i];
	cout << '\n';
	return 0;
}
