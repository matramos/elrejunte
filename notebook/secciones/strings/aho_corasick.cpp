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
