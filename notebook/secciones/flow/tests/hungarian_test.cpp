//Problem: https://codeforces.com/gym/101635/problem/G
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define fore(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second
#define ALL(x) x.begin(), x.end()

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

typedef int td; typedef vector<int> vi; typedef vector<td> vd;
const td INF = 1e9; //for maximum set INF to 0, and negate costs
bool zz(td x) { return x == 0; } //change to x==0, for ints/ll
struct Hungarian{
    int n; vector<vd> cs; vi L, R;
    Hungarian(int N, int M) : n(max(N, M)), cs(n, vd(n)), L(n), R(n) {
        forn(x, N) forn(y, M) cs[x][y] = INF;
    }
    void set(int x, int y, td c) { cs[x][y] = c; }
	td assign() {
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

int main(){
	#ifdef ANARAP
		freopen("input.in", "r",stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int nn,mm;
	cin >> nn >> mm;
	vector<ii> bots(nn), devs(mm);
	forn(i,nn) cin >> bots[i].fst >> bots[i].snd;
	forn(i,mm) cin >> devs[i].fst >> devs[i].snd;
	int x,y;
	cin >> x >> y;
	int left = mm+nn-1, right = nn;
	Hungarian h(left, right);
	forn(i,mm)
	{
		forn(j,nn)
		{
			int d = abs(devs[i].fst - bots[j].fst) + abs(devs[i].snd - bots[j].snd);
			d += abs(x - bots[j].fst) + abs(y - bots[j].snd);
			//cost[i][mm+j] = d;
			h.set(i,j,d);
		}
	}
	forn(i,nn-1)
	{
		forn(j,nn)
		{
			int d = 2*(abs(x - bots[j].fst) + abs(y - bots[j].snd));
			//cost[mm+nn+i][mm+j] = d;
			h.set(mm+i,j,d);
		}
	}
	assert(left >= right);
	cout << h.assign() << '\n';
	return 0;
	
}

