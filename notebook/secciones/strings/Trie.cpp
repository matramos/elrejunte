struct trie{
	map<char, trie> m;
	// For persistent trie only. Call "clone" probably from
	// "add" and/or other methods, to implement persistence.
	void clone(int pos) {
		Trie* prev = NULL;
		if(m.count(pos)) prev = m[pos];
		m[pos] = new Trie();
		if(prev != NULL)
		{
			m[pos]->m = prev->m;
			// copy other relevant data
		}
	}
	void add(const string &s, int p=0) {
		if(s[p]) m[s[p]].add(s, p+1);
	}
	void dfs() {
		//Do stuff
		forall(it, m)
		it->second.dfs();
	}
};
