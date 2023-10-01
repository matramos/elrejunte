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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 1e6+10; // INF > n
const int MAXLOG = 20; // 2^MAXLOG > 2*n
//The SuffixTree of S is the compressed trie that would result after
//inserting every suffix of S.
//As it is a COMPRESSED trie, some edges may correspond to strings,
//instead of chars, and the compression is done in a way that every
//vertex that doesn't correspond to a suffix and has only one
//descendent, is omitted.
struct SuffixTree {
    vector<char> s;
    vector<map<int,int>> to;//fst char of substring on edge -> node
    //s[fpos[i], fpos[i]+len[i]) is the substring on the edge between
    //i's father and i.
    //link[i] goes to the node that corresponds to the substring that
    //result after "removing" the first character of the substring that
    //i represents. Only defined for internal (non-leaf) nodes.
    vector<int> len, fpos, link;
    SuffixTree(int nn = 0) { // O(nn). nn should be the expected size
        s.reserve(nn); to.reserve(2*nn); len.reserve(2*nn);
        fpos.reserve(2*nn); link.reserve(2*nn);
        make_node(0, INF);
    }
    int node = 0, pos = 0, n = 0;
    int make_node(int p, int l) {
        fpos.pb(p); len.pb(l); to.pb({}); link.pb(0);
        return sz(to)-1;
    }
    void go_edge() {
        while(pos > len[to[node][s[n-pos]]]) {
            node = to[node][s[n-pos]];
            pos -= len[node];
        }
    }
    void add(char c) {
        s.pb(c); n++; pos++;
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
    // Call this after you finished building the SuffixTree to correctly
    // set some values of the vector 'len' that currently have a big
    // value (because of INF usage). Note that you shouldn't call 'add'
    // anymore after calling this method.
    void finishedAdding() {
        forn(i, sz(len)) if(len[i] + fpos[i] > n) len[i] = n - fpos[i];
    }
    // From here, copy only if needed!!
    // Map each suffix with it corresponding leaf node
    // vleaf[i] = node id of leaf of suffix s[i..n)
    // Note that the last character of the string must be unique
    // Use 'buildLeaf' not 'dfs' directly. Also 'finishedAdding' must
    // be called before calling 'buildLeaf'.
    // When this is needed, usually binary lifting (vp) and depths are
    // also needed.
    // Usually you also need to compute extra information in the dfs.
    vector<int> vleaf, vdepth;
    vector<vector<int>> vp;
    void dfs(int cur, int p, int curlen) {
		if(cur > 0) curlen += len[cur];
		vdepth[cur] = curlen;
		vp[cur][0] = p;
		if(to[cur].empty()) {
			assert(0 < curlen && curlen <= n);
			assert(vleaf[n-curlen] == -1);
			vleaf[n-curlen] = cur;
			// here maybe compute some extra info
		}
		else forall(it,to[cur]) {
			dfs(it->snd, cur, curlen);
			// maybe change return type and here compute extra info
		}
		// maybe return something here related to extra info
	}
    void buildLeaf() {
		vdepth.rsz(sz(to), 0); // tree size
		vleaf.rsz(n, -1); // string size
		vp.rsz(sz(to), vector<int>(MAXLOG)); // tree size * log
		dfs(0,0,0);
		forr(k,1,MAXLOG) forn(i,sz(to)) vp[i][k] = vp[vp[i][k-1]][k-1];
		forn(i,n) assert(vleaf[i] != -1);
	}
};

int main()
{
	#ifdef ANARAP
	freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	string s;
	int q;
	cin >> s >> q;
	s.push_back('$');
	SuffixTree st(sz(s));
	forn(i,sz(s)) st.add(s[i]);
	st.finishedAdding();
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
		while(pos < sz(x))
		{
			if(st.to[0].count(x[pos]) == 0)
			{
				ans = -1;
				break;
			}
			ans++;
			int node = 0;
			bool ok = true;
			while(ok && pos < sz(x) && st.to[node].count(x[pos]))
			{
				int nextNode = st.to[node][x[pos]];
				forn(i,st.len[nextNode])
				{
					if(pos < sz(x) && x[pos] == s[st.fpos[nextNode]+i]) pos++;
					else
					{
						ok = false;
						break;
					}
					if(pos == sz(x)) break;
				}
				node = nextNode;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
