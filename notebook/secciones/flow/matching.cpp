vector<int> g[MAXN]; // [0,n)->[0,m)
int n, m;
int mat[MAXM]; bool vis[MAXN];
int match(int x) {
	if(vis[x]) return 0;
	vis[x] = true;
	for(int y:g[x])if(mat[y]<0||match(mat[y])){mat[y]=x;return 1;}
	return 0;
}
vector<pair<int,int> > max_matching() { //O(V^2 * E)
	vector<pair<int,int> > r;
	memset(mat,-1,sizeof(mat));
	forn(i,n) memset(vis,false,sizeof(vis)), match(i);
	forn(i,m) if(mat[i]>=0) r.pb({mat[i],i});
	return r;
}