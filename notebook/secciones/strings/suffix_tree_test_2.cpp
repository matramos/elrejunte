// Problem: https://open.kattis.com/problems/cram
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
//local
#else
//judge
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

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
    vector<int> vleaf, vdepth, vsubtree;
    vector<vector<int>> vp;
    int dfs(int cur, int p, int curlen) {
		if(cur > 0) curlen += len[cur];
		vdepth[cur] = curlen;
		vp[cur][0] = p;
		if(to[cur].empty()) {
			assert(0 < curlen && curlen <= n);
			assert(vleaf[n-curlen] == -1);
			vleaf[n-curlen] = cur;
			// here maybe compute some extra info
			vsubtree[cur] = n-curlen;
		}
		else forall(it,to[cur]) {
			int aux = dfs(it->snd, cur, curlen);
			// maybe change return type and here compute extra info
			vsubtree[cur] = min(vsubtree[cur], aux);
		}
		// maybe return something here related to extra info
		return vsubtree[cur];
	}
    void buildLeaf() {
		vsubtree.rsz(sz(to), n); // tree size
		vdepth.rsz(sz(to), 0); // tree size
		vleaf.rsz(n, -1); // string size
		vp.rsz(sz(to), vector<int>(MAXLOG)); // tree size * log
		dfs(0,0,0);
		forr(k,1,MAXLOG) forn(i,sz(to)) vp[i][k] = vp[vp[i][k-1]][k-1];
		forn(i,n) assert(vleaf[i] != -1);
	}
};


string s;

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
    string x;
    while(cin >> x)
    {
        if(!s.empty()) s.pb(' ');
        s += x;
    }
    s.pb('$');
    SuffixTree st(sz(s));
    forall(it,s) st.add(*it);
    st.finishedAdding();
    st.buildLeaf();
    vector<int> dp(sz(s),0);
    dforn(i,sz(s)-1)
    {
        dp[i] = 1+dp[i+1];
        int L = 1, R = sz(s)-i;
        while(L < R)
        {
			int M = (L+R)/2;
			int aux = M;
			int node = st.vleaf[i];
			dforn(j,MAXLOG) if((1<<j) <= aux)
			{
				node = st.vp[node][j];
				aux -= 1<<j;
			}
			assert(aux == 0);
			if(st.vsubtree[node] < i) R = M;
			else L = M+1;
		}
		int node = st.vleaf[i];
		dforn(j,MAXLOG) if((1<<j) <= L)
		{
			node = st.vp[node][j];
			L -= 1<<j;
		}
		int len = max(1,st.vdepth[node]);
        dp[i] = min(dp[i], dp[i+len] + min(len, 3));
    }
    cout << dp[0] << '\n';
    return 0;
}
//ababbbbbbbbbbbbbbbbababababababababab
