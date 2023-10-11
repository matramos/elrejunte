//Problem: https://codeforces.com/contest/1400/problem/F
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

struct Node {
	map<char,int> next, go;
	int p, link, leafLink;
	char pch;
	vector<int> leaf;
	Node(int pp, char c): p(pp), link(-1), leafLink(-1), pch(c) {}
};
struct AhoCorasick {
	vector<Node> t = { Node(-1,-1) };
	void add_string(string s, int id) {
		int v = 0;
		for(char c : s) {
			if(!t[v].next.count(c)) {
				t[v].next[c] = sz(t);
				t.pb(Node(v,c));
			}
			v = t[v].next[c];
		}
		t[v].leaf.pb(id);
	}
	int go(int v, char c) {
		if(!t[v].go.count(c)) {
			if(t[v].next.count(c)) t[v].go[c] = t[v].next[c];
			else t[v].go[c] = v==0 ? 0 : go(get_link(v), c);
		}
		return t[v].go[c];
	}
	int get_link(int v) { // suffix link
		if(t[v].link < 0) {
			if(!v || !t[v].p) t[v].link = 0;
			else t[v].link = go(get_link(t[v].p), t[v].pch);
		}
		return t[v].link;
	}
	// like suffix link, but only going to the root or to a node with
	// a non-emtpy "leaf" list. Copy only if needed
	int get_leaf_link(int v) {
		if(t[v].leafLink < 0) {
			if(!v || !t[v].p) t[v].leafLink = 0;
			else if(!t[get_link(v)].leaf.empty()) t[v].leafLink = t[v].link;
			else t[v].leafLink = get_leaf_link(t[v].link);
		}
		return t[v].leafLink;
	}
};

AhoCorasick aho;

int x;

void buildBadStrings(string &str, int sum)
{
	if(sum > x) return;
	if(sum == x)
	{
		bool bad = true;
		int n = sz(str);
		forn(i,n)
		{
			int acum = 0;
			forr(j,i,n)
			{
				acum += str[j]-'0';
				if(acum < x && x%acum == 0)
				{
					bad = false;
					break;
				}
			}
			if(!bad) break;
		}
		if(bad) aho.add_string(str, 0);
		return;
	}
	forr(i,1,10)
	{
		str.pb('0'+i);
		buildBadStrings(str, sum+i);
		str.pop_back();
	}
}

int dp[1000][5000];
string s;

int solve(int pos, int node)
{
	if(sz(aho.t[node].leaf)) return 1e5;
	if(pos == sz(s)) return 0;
	if(dp[pos][node] != -1) return dp[pos][node];
	int ret = solve(pos+1, node) + 1;
	ret = min(ret, solve(pos+1, aho.go(node, s[pos])));
	return dp[pos][node] = ret;
}

int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> s >> x;
	string aux = "";
	buildBadStrings(aux, 0);
	memset(dp, -1, sizeof(dp));
	cout << solve(0, 0) << '\n';
	return 0;
}
