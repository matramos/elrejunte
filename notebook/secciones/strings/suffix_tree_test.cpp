//Problem: https://codeforces.com/gym/102428/problem/G
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
#define MAXN 200010
#define INF 1000100

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

//The SuffixTree of S is the compressed trie that would result
//after inserting every suffix of S.
//As it is a COMPRESSED trie, some edges may correspond to strings, instead
//of chars, and the compression is done in a way that every vertex that
//doesn't correspond to a suffix and has only one descendent, is omitted.
struct SuffixTree {
	char s[MAXN];
	map<int,int> to[2*MAXN];//key is fst char of substring on edge to value
	//s[fpos[i], fpos[i]+len[i]) is the substring on the edge between
	//i's father and i.
	//link[i] goes to the node that corresponds to the substring that result
	//after "removing" the first character of the substring that i represents
	//note that link is only defined for every internal (non-leaf) node.
	int len[2*MAXN] = {INF}, fpos[2*MAXN], link[2*MAXN];
	int node = 0, pos = 0, sz = 1, n = 0;
	int make_node(int p, int l) {
		fpos[sz] = p; len[sz] = l; return sz++;}
	void go_edge() {
		while(pos > len[to[node][s[n-pos]]]) {
			node = to[node][s[n-pos]];
			pos -= len[node];
		}
	}
	void add(char c) {
		s[n++] = c; pos++;
		int last = 0;
		while(pos > 0) {
			go_edge();
			int edge = s[n-pos];
			int& v = to[node][edge];
			int t = s[fpos[v]+pos-1];
			if(v == 0) {
				v = make_node(n-pos, INF);
				link[last] = node; last = 0;
			}
			else if(t == c) {link[last] = node; return;}
			else {
				int u = make_node(fpos[v], pos-1);
				to[u][c] = make_node(n-1, INF);
				to[u][t] = v;
				fpos[v] += pos-1; len[v] -= pos-1;
				v = u; link[last] = u; last = u;
			}
			if(node == 0) pos--;
			else node = link[node];
		}
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
	SuffixTree st;
	string s;
	int q;
	cin >> s >> q;
	s.push_back('$');
	forn(i,s.size()) st.add(s[i]);
	/*forn(i,st.sz)
	{
		cout << i << ' ' << st.fpos[i];
		cout << ' ' << st.len[i];
		cout << ' ' << st.link[i];
		cout << ": ";
		forall(it,st.to[i]) cout << (char)it->fst << ' ' << it->snd << ", ";
		cout << '\n';
	}
	return 0;*/
	forn(Q,q)
	{
		string x;
		cin >> x;
		int pos = 0, ans = 0;
		while(pos < x.size())
		{
			if(st.to[0].count(x[pos]) == 0)
			{
				ans = -1;
				break;
			}
			ans++;
			int node = 0;
			bool ok = true;
			while(ok && pos < x.size() && st.to[node].count(x[pos]))
			{
				int nextNode = st.to[node][x[pos]];
				forn(i,st.len[nextNode])
				{
					if(pos < x.size() && x[pos] == s[st.fpos[nextNode]+i]) pos++;
					else
					{
						ok = false;
						break;
					}
					if(pos == x.size()) break;
				}
				node = nextNode;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}