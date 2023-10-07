struct UnionFind {
	int nsets;
	vector<int> f, setsz; // f[i] = parent of node i
	UnionFind(int n) : nsets(n), f(n, -1), setsz(n, 1) {}
	int comp(int x) { return (f[x] == -1 ? x : f[x]=comp(f[x])); } //O(1)
	bool join(int i,int j) { // returns true if already in the same set
		int a = comp(i), b = comp(j);
		if(a != b) {
			if(setsz[a] > setsz[b]) swap(a,b);
			setsz[b] += setsz[a];
			f[a] = b; // the bigger group (b) now represents the smaller (a)
			nsets--;
		}
		return a == b;
	}
};
