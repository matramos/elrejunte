//Problem: https://www.spoj.com/problems/ADAINDEX/
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
#define PI 3.1415926535897932384626

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct trie{
	map<char, trie> m;
	int cant = 0;
	void add(const string &s, int p=0)
	{
		if(s[p]) m[s[p]].add(s, p+1);
		cant++;
	}
	int count(string &s, int p=0)
	{
		if(p == s.size()) return cant;
		if(m.count(s[p])) return m[s[p]].count(s,p+1);
		return 0;
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
	int n,q;
	cin >> n >> q;
	trie t;
	forn(i,n)
	{
		string s;
		cin >> s;
		t.add(s);
	}
	forn(i,q)
	{
		string s;
		cin >> s;
		cout << t.count(s) << '\n';
	}
	return 0;
}