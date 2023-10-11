// Problem: https://codeforces.com/gym/104666/problem/H
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

const ll MOD = 1000000007;

typedef ll tipo; // maybe use double or other depending on the problem
struct Mat {
	int N; // square matrix
	vector<vector<tipo>> m;
	Mat(int n): N(n), m(n, vector<tipo>(n, 0)) {}
	vector<tipo> &operator[](int p) { return m[p]; }
	Mat operator *(Mat& b) { // O(N^3), multiplication
		assert(N == b.N);
		Mat res(N);
		forn(i, N) forn(j, N) forn(k, N) // remove MOD if not needed
			res[i][j] = (res[i][j] + m[i][k] * b[k][j])%MOD;
		return res;
	}
	Mat operator ^(int k) { // O(N^3 * logk), exponentiation
		Mat res(N);
		Mat aux = *this;
		forn(i, N) res[i][i] = 1;
		while(k) if(k&1) res = res*aux, k--; else aux = aux*aux, k/=2;
		return res;
	}
};

vector<bool> bad;
AhoCorasick aho;

void dfs(int node, bool isbad)
{
	if(!aho.t[node].leaf.empty()) isbad = true;
	bad[node] = isbad;
	forall(it, aho.t[node].next) dfs(it->snd, isbad);
}

int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int k,n;
	cin >> k >> n;
	forn(i,n)
	{
		int asd;
		string s;
		cin >> asd >> s;
		aho.add_string(s, i);
	}
	bad.rsz(sz(aho.t));
	dfs(0, false);
	forn(i,sz(aho.t))
	{
		int node = i;
		bool isbad = false;
		while(node != 0)
		{
			isbad |= bad[node];
			node = aho.get_link(node);
		}
		bad[i] = isbad;
	}
	Mat mat(sz(aho.t));
	forn(i,sz(aho.t)) if(!bad[i]) forr(c,'a','z'+1) if(!bad[aho.go(i, char(c))]) mat[i][aho.go(i, char(c))]++;
	Mat res = mat^k;
	ll ans = 0;
	forn(i,sz(aho.t)) ans += res[0][i];
	ans %= MOD;
	cout << ans << '\n';
	return 0;
}
