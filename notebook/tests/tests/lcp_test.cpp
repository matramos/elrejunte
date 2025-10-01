//Problem: https://www.spoj.com/problems/ADACLEAN/
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
#define MAXN 300010

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

//LCP(sa[i], sa[j]) = min(lcp[i+1], lcp[i+2], ..., lcp[j])
//example: "banana", sa = {5,3,1,0,4,2}, lcp = {0,1,3,0,0,2}
//Num of dif substrings: (n*n+n)/2 - (sum over lcp array)
vector<int> computeLCP(string& s, vector<int>& sa) {
	int n = s.size(), L = 0;
	vector<int> lcp(n), plcp(n), phi(n);
	phi[sa[0]] = -1;
	forr(i, 1, n) phi[sa[i]] = sa[i-1];
	forn(i, n) {
		if(phi[i]<0) {plcp[i] = 0; continue;}
		while(s[i+L] == s[phi[i]+L]) L++;
		plcp[i] = L;
		L = max(L-1, 0);
	}
	forn(i,n) lcp[i] = plcp[sa[i]];
	return lcp; // lcp[i]=LCP(sa[i-1],sa[i])
}

pair<int, int> sf[MAXN];
bool sacomp(int lhs, int rhs) {return sf[lhs] < sf[rhs];}
vector<int> constructSA(string& s) { // O(n log^2(n))
	int n = s.size();                   // (sometimes fast enough)
	vector<int> sa(n), r(n);
	forn(i,n) r[i] = s[i]; //r[i]: equivalence class of s[i..i+m)
	for(int m=1; m<n; m*=2) {
		//sf[i] = {r[i], r[i+m]}, used to sort for next equivalence classes
		forn(i,n) sa[i] = i, sf[i] = {r[i], i+m<n ? r[i+m] : -1};
		stable_sort(sa.begin(), sa.end(), sacomp); //O(n log(n))
		r[sa[0]] = 0;
		//if sf[sa[i]] == sf[sa[i-1]] then same equivalence class
		forr(i,1,n) r[sa[i]] = sf[sa[i]]!=sf[sa[i-1]] ? i : r[sa[i-1]];
	}
	return sa;
}

int main()
{
	#ifdef REJUNTE
	freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	forn(T,t)
	{
		int n,k,ans=0;
		string s;
		cin >> n >> k >> s;
		vector<int> sa = constructSA(s);
		vector<int> lcp = computeLCP(s, sa);
		forn(i,sa.size()) if(sa[i]+k <= s.size() && (i==0 || lcp[i]<k)) ans++;
		cout << ans << '\n';
	}
	return 0;
}