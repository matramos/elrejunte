// Problem: https://codeforces.com/problemset/problem/126/B
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

//z[i] = length of longest substring starting from s[i] that is prefix of s
//z[i] = max k: s[0,k) == s[i,i+k)
vector<int> zFunction(string &s) {
	int l=0, r=0, n=s.size();
	vector<int> z(n,0);
	forr(i, 1, n) {
		if(i<=r) z[i] = min(r-i+1, z[i-l]);
		while(i+z[i]<n && s[z[i]]==s[i+z[i]]) z[i]++;
		if(i+z[i]-1>r) l=i, r=i+z[i]-1;
	}
	return z;
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
	string s;
	cin >> s;
	vector<int> z = zFunction(s);
	int longestObelix = 0, ans = 0;
	forr(i,1,z.size())
	{
		int aux = z[i];
		if(aux + i == s.size()) aux--;
		longestObelix = max(longestObelix, aux);
	}
	dforn(i,s.size()) if(i>0)
	{
		if(z[i] == s.size()-i && longestObelix >= z[i]) ans = z[i];
	}
	if(ans == 0) cout << "Just a legend\n";
	else cout << s.substr(0,ans) << '\n';
	return 0;
}