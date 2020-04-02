#define operacion(x, y) max(x, y)
int n, m;
int a[MAXN][MAXN], st[2*MAXN][2*MAXN];
void build() { //O(n*m)
	forn(i, n) forn(j, m) st[i+n][j+m] = a[i][j];
	forn(i, n) dforn(j, m) //build st of row i+n (each row independently)
		st[i+n][j] = operacion(st[i+n][j<<1], st[i+n][j<<1|1]);
	dforn(i, n) forn(j, 2*m) //build st of ranges of rows
		st[i][j] = operacion(st[i<<1][j], st[i<<1|1][j]);
}
void upd(int x, int y, int v) { //O(logn * logm)
	st[x+n][y+m] = v;
	for(int j=y+m; j>1; j>>=1)//update the ranges that contains y+m in row x+n
		st[x+n][j>>1] = operacion(st[x+n][j], st[x+n][j^1]);
	for(int i=x+n; i>1; i>>=1)//in each range that contains row x+n
		for(int j=y+m; j; j>>=1) //update the ranges that contains y+m
			st[i>>1][j] = operacion(st[i][j], st[i^1][j]);
}
int query(int x0, int x1, int y0, int y1) { //O(logn * logm)
	int r = NEUT;
	//start at the bottom and move up each time
	for(int i0=x0+n, i1=x1+n; i0<i1; i0>>=1, i1>>=1) {
		int t[4], q=0;
		//if the whole segment of row node i0 is included, then move right
		if(i0&1) t[q++] = i0++; 
		//if the whole segment of row node i1-1 is included, then move left
		if(i1&1) t[q++] = --i1; 
		forn(k, q) for(int j0=y0+m, j1=y1+m; j0<j1; j0>>=1, j1>>=1) {
			if(j0&1) r = operacion(r, st[t[k]][j0++]);
			if(j1&1) r = operacion(r, st[t[k]][--j1]);
		}
	}
	return r;
}