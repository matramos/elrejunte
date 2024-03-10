typedef long double td; typedef vector<int> vi; typedef vector<td> vd;
const td INF = 1e100; //for maximum set INF to 0, and negate costs
bool zz(td x) { return abs(x) < 1e-9; } //change to x==0, for ints/ll
struct Hungarian{
    int n; vector<vd> cs; vi L, R;
    Hungarian(int N, int M) : n(max(N, M)), cs(n, vd(n)), L(n), R(n) {
        forn(x, N) forn(y, M) cs[x][y] = INF;
    }
    void set(int x, int y, td c) { cs[x][y] = c; }
	td assign() { // O(n^3)
		int mat = 0; vd ds(n), u(n), v(n); vi dad(n), sn(n);
		forn(i,n) u[i] = *min_element(cs[i].begin(), cs[i].end());
		forn(j,n) {
			v[j] = cs[0][j] - u[0];
			forr(i, 1, n) v[j] = min(v[j], cs[i][j] - u[i]);
		}
		L = R = vi(n, -1);
		forn(i,n)forn(j,n)if(R[j] == -1 && zz(cs[i][j] - u[i] - v[j])) {
			L[i] = j, R[j] = i, mat++;
			break;
		}
		for(; mat<n; mat++) {
		    int s = 0, j = 0, i;
		    while(L[s] != -1) s++;
		    fill(dad.begin(), dad.end(), -1);
		    fill(sn.begin(), sn.end() ,0);
		    forn(k, n) ds[k] = cs[s][k] - u[s] - v[k];
		    while(1) {
		        j = -1;
		        forn(k,n)if(!sn[k] && (j == -1 || ds[k] < ds[j])) j = k;
		        sn[j] = 1; i = R[j];
		        if(i == -1) break;
		        forn(k, n) if(!sn[k]) {
		            td new_ds = ds[j] + cs[i][k] - u[i] - v[k];
		            if(ds[k] > new_ds) ds[k] = new_ds, dad[k] = j;
		        }
		    }
		    forn(k, n) if(k != j && sn[k]) {
				td w = ds[k] - ds[j];
				v[k] += w, u[R[k]] -= w;
			}
		    u[s] += ds[j];
		    while(dad[j] >= 0) {
				int d = dad[j];
				R[j] = R[d], L[R[j]] = j, j = d;
			}
		    R[j] = s, L[s]=j;
		}
		td ret = 0;
		forn(i, n) ret += cs[i][L[i]];
		return ret;
	}
};
