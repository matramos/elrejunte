// https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
// special case of gauss_jordan_mod with mod=2, bitset for efficiency
// finds lexicograhically minimal solution (0 < 1, False < True)
// for lexicographically maximal change your solution model accordingly
int gauss (vector < bitset<N> > a, int n, int m, bitset<N> & ans) {
    vector<int> where (m, -1);
    for (int col=m-1, row=0; col>=0 && row<n; --col) {
        for (int i=row; i<n; ++i)
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        if (! a[row][col])
            continue;
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }
    ans.reset();
    forn(i,m) if(where[i] != -1) {
		ans[i] = a[where[i]][m] & a[where[i]][i];
	}
    forn(i,n) if((ans & a[i]).count()%2 != a[i][m]) return 0;
    forn(i,m) if(where[i] == -1) return INF;
    return 1;
}
