//Problem H from: https://codeforces.com/group/YjFmW2O15Q/contest/102363/attachments
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

// P should be a prime number, could be randomly generated,
// sometimes is good to make it close to alphabet size
// MOD[i] must be a prime of this order, could be randomly generated
const int P=1777771, MOD[2] = {999727999, 1070777777};
const int PI[2] = {325255434, 10018302}; // PI[i] = P^-1 % MOD[i]
struct Hash {
	vector<int> h[2], pi[2];
	vector<ll> vp[2]; //Only used if getChanged is used (delete it if not)
	Hash(string& s) {
		forn(k, 2)
			h[k].rsz(s.size()+1), pi[k].rsz(s.size()+1), vp[k].rsz(s.size()+1);
		forn(k, 2) {
			h[k][0] = 0; vp[k][0] = pi[k][0] = 1;
			ll p=1;
			forr(i, 1, sz(s)+1) {
				h[k][i] = (h[k][i-1] + p*s[i-1]) % MOD[k];
				pi[k][i] = (1LL * pi[k][i-1] * PI[k]) % MOD[k];
				vp[k][i] = p = (p*P) % MOD[k];
			}
		}
	}
	ll get(int s, int e) { // get hash value of the substring [s, e)
		ll H[2];
		forn(i, 2) {
			H[i] = (h[i][e] - h[i][s] + MOD[i]) % MOD[i];
			H[i] = (1LL * H[i] * pi[i][s]) % MOD[i];
		}
		return (H[0]<<32)|H[1];
	}
	//get hash value of [s, e) if origVal in pos is changed to val
	//Assumes s <= pos < e. If multiple changes are needed, 
    //do what is done in the for loop for every change
    ll getChanged(int s, int e, int pos, int val, int origVal) {
        ll hv = get(s,e), hh[2];
        hh[1] = hv & ((1LL<<32)-1);
        hh[0] = hv >> 32;
        forn(i, 2)
        	hh[i] = (hh[i] + vp[i][pos] * (val - origVal + MOD[i])) % MOD[i];
        return (hh[0]<<32)|hh[1];
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
    map<ll,ll> hashReps;
    ll ans=0;
    int n,m,r;
    string s,x;
    char aux[3]={'.',',','_'};
    cin >> n >> s >> r >> m;
    Hash textHash(s);
    forn(R,r)
    {
        cin >> x;
        Hash wordHash(x);
        hashReps[wordHash.get(0,m)]++;
        forn(i,m)
        {
            forn(j,26)
            {
                if(x[i]==j+'a') continue;
                hashReps[wordHash.getChanged(0, m,i,j+'a',x[i])]++;
            }
            forn(j,3)
            {
                if(x[i]==aux[j]) continue;
                hashReps[wordHash.getChanged(0, m,i,aux[j],x[i])]++;
            }
        }
    }
    forn(i,n-m+1) ans+=hashReps[textHash.get(i,i+m)];
    cout << ans << '\n';
    return 0;
}
