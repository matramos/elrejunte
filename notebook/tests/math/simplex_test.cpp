// https://codeforces.com/gym/104207/problem/F
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a); i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0; i--)
#define forall(it,v) for(auto it=v.begin(); it!=v.end(); it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef ANARAP

#else 

#endif 

using namespace std;
typedef long long ll;
typedef pair<int, int> ii ;

typedef double tipo;
typedef vector<tipo> vt;
const tipo EPS = 1e-9;
// maximize c^T x s.t. Ax<=b, x>=0
// returns pair (maximum value, solution vector)
pair<tipo, vt> simplex(vector<vt> A, vt b, vt c) {
  int n = sz(b), m = sz(c);
  tipo z = 0.;
  vector<int> X(m), Y(n);
  forn(i, m) X[i] = i;
  forn(i, n) Y[i] = i + m;
  auto pivot = [&](int x, int y) {
    swap(X[y], Y[x]);
    b[x] /= A[x][y];
    forn(i, m) if (i != y) A[x][i] /= A[x][y];
    A[x][y] = 1 / A[x][y];
    forn(i, n) if (i != x && abs(A[i][y]) > EPS) {
      b[i] -= A[i][y] * b[x];
      forn(j, m) if (j != y) A[i][j] -= A[i][y] * A[x][j];
      A[i][y] *= -A[x][y];
    }
    z += c[y] * b[x];
    forn(i, m) if (i != y) c[i] -= c[y] * A[x][i];
    c[y] *= -A[x][y];
  };
  while (1) {
    int x = -1, y = -1;
    tipo mn = -EPS;
    forn(i, n) if (b[i] < mn) mn = b[i], x = i;
    if (x < 0) break;
    forn(i, m) if (A[x][i] < -EPS) {
      y = i;
      break;
    }
    assert(y >= 0);  // no solution to Ax<=b
    pivot(x, y);
  }
  while (1) {
    tipo mx = EPS;
    int x = -1, y = -1;
    forn(i, m) if (c[i] > mx) mx = c[i], y = i;
    if (y < 0) break;
    tipo mn = 1e200;
    forn(i, n) if (A[i][y] > EPS && b[i] / A[i][y] < mn) {
      mn = b[i] / A[i][y], x = i;
    }
    assert(x >= 0);  // c^T x is unbounded
    pivot(x, y);
  }
  vt r(m);
  forn(i, n) if (Y[i] < m) r[Y[i]] = b[i];
  return {z, r};
}


int main(){
	
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
	#endif 
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	forn(T,t)
	{
		int n,m;
		cin >> n >> m;
		vector<int> v(n);
		forn(i,n) cin >> v[i];
		int nvars = 1+(1<<n);
		vector<double> all0(nvars, 0.);
		vector<bool> isvalid(1<<n);
		forn(bm, (1<<n))
		{
			int sum = 0;
			forn(i,n) if(bm & (1<<i)) sum += v[i];
			isvalid[bm] = sum <= m;
		}
		vector<vector<double>> rows;
		vector<double> b;
		// each valid p_i <= 1
		// each invalid p_i == 0
		forn(i,(1<<n))
		{
			rows.pb(all0);
			rows.back()[i] = 1.; // p_i <= 0
			if(isvalid[i]) b.pb(1.);
			else b.pb(0.);
		}
		// each group == G
		forn(i,n)
		{
			rows.pb(all0);
			//cout << "for i " << i << ": ";
			forn(bm,(1<<n)) if(isvalid[bm] && ((1<<i) & bm))
			{
				//cout << bm << ' ';
				rows.back()[bm] = 1.;
			}
			//cout << '\n';
			rows.back().back() = -1.;
			b.pb(0.);
			
			rows.pb(all0);
			//cout << "for i " << i << ": ";
			forn(bm,(1<<n)) if(isvalid[bm] && ((1<<i) & bm))
			{
				//cout << bm << ' ';
				rows.back()[bm] = -1.;
			}
			//cout << '\n';
			rows.back().back() = 1.;
			b.pb(0.);
		}
		// 0 <= g <= 1
		rows.pb(all0);
		rows.back().back() = 1;
		b.pb(1);
		rows.pb(all0);
		rows.back().back() = -1;
		b.pb(0);
		// sum of p_i == 1
		rows.pb(all0);
		forn(i,sz(rows.back())-1) rows.back()[i] = 1.;
		b.pb(1.);
		rows.pb(all0);
		forn(i,sz(rows.back())-1) rows.back()[i] = -1.;
		b.pb(-1.);
		vector<double> c = all0;
		c.back() = 1.;
		/*cout << "c: "; forn(i,sz(c)) cout << fixed << setprecision(2) << c[i] << ' '; cout << '\n';
		cout << "restr:\n";
		forn(i,sz(b))
		{
			cout << '\t';
			forall(it,rows[i]) cout << *it << ' ';
			cout << "<= ";
			cout << b[i] << '\n';
		}*/
		pair<double, vector<double>> res = simplex(rows, b, c);
		//forall(it,res.snd) cout << fixed << setprecision(2) << *it << ' '; cout << '\n';
		cout << fixed << setprecision(8) << "Case #" << T+1 << ": " << res.fst << '\n';
	}
	return 0;
} 
