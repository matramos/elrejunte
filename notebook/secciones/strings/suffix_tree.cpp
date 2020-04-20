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