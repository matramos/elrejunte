//Problem: https://www.spoj.com/problems/NHAY/
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
void match(string &T,string &P) { //Text, Pattern -- O(|T|+|P|)
	string s = P+'$'+T;//'$'' should be a character that is not present in T
	vector<int> z = zFunction(s);
	forr(i, P.size()+1, s.size())
		if(z[i] == P.size())
		{
			cout << i-P.size()-1 << '\n';
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
	int n;
	bool print = false;
	string t,p;
	while(cin >> n >> p >> t)
	{
		if(print) cout << '\n';
		else print = true;
		match(t,p);		
	}
	return 0;
}