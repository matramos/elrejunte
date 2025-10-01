//Problem: https://www.spoj.com/problems/MATSUM/
#include <bits/stdc++.h>
#define sqr(a) ((a)*(a))
#define rsz resize
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second
#define MAXN 1025

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

#define operacion(x, y) (x + y)
int n, m, NEUT = 0;
int a[MAXN][MAXN], st[2 * MAXN][2 * MAXN];
void build() {  // O(n*m)
  forn(i, n) forn(j, m) st[i + n][j + m] = a[i][j];
  forn(i, n) dforn(j, m)  // build st of row i+n (each row independently)
      st[i + n][j] = operacion(st[i + n][j << 1], st[i + n][j << 1 | 1]);
  dforn(i, n) forn(j, 2 * m)  // build st of ranges of rows
      st[i][j] = operacion(st[i << 1][j], st[i << 1 | 1][j]);
}
void upd(int x, int y, int v) {  // O(logn * logm)
  st[x + n][y + m] = v;
  for (int j = y + m; j > 1; j >>= 1)  // update ranges containing y+m
    st[x + n][j >> 1] = operacion(st[x + n][j], st[x + n][j ^ 1]);
  for (int i = x + n; i > 1; i >>= 1)  // in each range that contains row x+n
    for (int j = y + m; j; j >>= 1)    // update the ranges that contains y+m
      st[i >> 1][j] = operacion(st[i][j], st[i ^ 1][j]);
}
int query(int x0, int x1, int y0, int y1) {  // O(logn * logm)
  int r = NEUT;
  // start at the bottom and move up each time
  for (int i0 = x0 + n, i1 = x1 + n; i0 < i1; i0 >>= 1, i1 >>= 1) {
    int t[4], q = 0;
    // if the whole segment of row node i0 is included, then move right
    if (i0 & 1) t[q++] = i0++;
    // if the whole segment of row node i1-1 is included, then move left
    if (i1 & 1) t[q++] = --i1;
    forn(k, q) for (int j0 = y0 + m, j1 = y1 + m; j0 < j1; j0 >>= 1, j1 >>= 1) {
      if (j0 & 1) r = operacion(r, st[t[k]][j0++]);
      if (j1 & 1) r = operacion(r, st[t[k]][--j1]);
    }
  }
  return r;
}


int main()
{
	#ifdef REJUNTE
	freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	forn(T,t)
	{
		cin >> n;
		m = n;
		forn(i,n)forn(j,n) a[i][j] = 0;
		build();
		string str;
		do
		{
			cin >> str;
			if(str == "SET")
			{
				int x,y,val;
				cin >> x >> y >> val;
				upd(x, y, val);
			}
			else if(str == "SUM")
			{
				int xa,xb,ya,yb;
				cin >> xa >> ya >> xb >> yb;
				cout << query(xa,xb+1,ya,yb+1) << '\n';
			}
		}while(str != "END");
	}
	return 0;
}
