struct UnionFind{
	vector<int> f,setSize; //the array f contains the parent of each node
	int cantSets;
	void init(int n)
	{
		f.clear(); setSize.clear();
		cantSets=n;
		f.rsz(n,-1);
		setSize.rsz(n,1);
	}
	int comp(int x){return (f[x]==-1?x:f[x]=comp(f[x]));}//O(1)
	bool join(int i,int j) //devuelve true si ya estaban juntos
	{
		bool con=comp(i)==comp(j);
		if(!con)
		{
			cantSets--;
			setSize[comp(j)]+=setSize[comp(i)];
			setSize[comp(i)]=setSize[comp(j)]; //no suma, solo asigna
			f[comp(i)]=comp(j);
		}
		return con;
	}
};
