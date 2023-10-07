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

// b[i] = longest border of t[0,i) = length of the longest prefix of 
// the substring P[0..i-1) that is also suffix of the substring P[0..i)
// For "AABAACAABAA", b[i] = {-1, 0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5}
vector<int> kmppre(string& P) { // 
	vector<int> b(sz(P)+1); b[0] = -1;
	int j = -1;
	forn(i, sz(P)) {
		while(j >= 0 && P[i] != P[j]) j = b[j];
		b[i+1] = ++j;
	}
	return b;
}
void kmp(string& T, string& P) { //Text, Pattern -- O(|T|+|P|)
	int j = 0;
	vector<int> b = kmppre(P);
	forn(i, sz(T)) {
		while(j >= 0 && T[i] != P[j]) j = b[j];
		if(++j == sz(P)) {
			//Match at i-j+1, do something
			cout << i-j+1 << '\n';
			j = b[j];
		}
	}
}

int main()
{
	#ifdef ANARAP
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
		kmp(t,p);		
	}
	return 0;
}
