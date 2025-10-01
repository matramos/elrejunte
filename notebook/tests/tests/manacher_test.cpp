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

int d1[MAXN];//d1[i] = max odd palindrome centered on i
int d2[MAXN];//d2[i] = max even palindrome centered on i
//s  aabbaacaabbaa
//d1 1111117111111
//d2 0103010010301
void manacher(string &s) { // O(|S|) - find longest palindromic substring
	int l=0, r=-1, n=s.size();
	forn(i, n) { // build d1
		int k = i>r? 1 : min(d1[l+r-i], r-i);
		while(i+k<n && i-k>=0 && s[i+k]==s[i-k]) k++;
		d1[i] = k--;
		if(i+k > r) l=i-k, r=i+k;
	}
	l=0, r=-1;
	forn(i, n) { // build d2
		int k = (i>r? 0 : min(d2[l+r-i+1], r-i+1))+1;
		while(i+k<=n && i-k>=0 && s[i+k-1]==s[i-k]) k++;
		d2[i] = --k;
		if(i+k-1 > r) l=i-k, r=i+k-1;
	}
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
	int k,ans=0;
	string s;
	cin >> k >> s;
	manacher(s);
	forn(i,s.size())
	{
		if(k%2 == 1 && k <= 2*d1[i]-1) ans++;
		if(k%2 == 0 && k <= 2*d2[i]) ans++;
	}
	cout << ans << '\n';
	return 0;
}