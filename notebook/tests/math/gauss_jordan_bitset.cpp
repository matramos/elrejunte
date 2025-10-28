// https://codeforces.com/gym/101908/problem/M
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
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

#ifdef ANARAP
//local
#else
//judge
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

const int N = 4096;
const int INF = 2;

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

int toInt(string& s)
{
	int ret = 0;
	forn(i,sz(s)) ret = ret*10+s[i]-'0';
	return ret;
}

int main()
{
	// agregar g++ -DANARAP en compilacion
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,nv;
	cin >> n >> nv;
	vector<bitset<N>> v(n+nv);
	forn(i,n)
	{
		string s;
		bool pos = true;
		while(cin >> s)
		{
			if(s == "and") break;
			if(s == "not" || s == "(not") pos = false;
			else if(s == "or") pos = true;
			else
			{
				if(s.back() == ')') s.pop_back();
				reverse(s.begin(), s.end());
				if(s.back() == '(') s.pop_back();
				assert(s.back() == 'x');
				s.pop_back();
				reverse(s.begin(), s.end());
				int id = toInt(s)-1;
				v[i].flip(id + nv*pos);
			}
		}
	}
	forn(i,nv)
	{
		v[n+i].set(i);
		v[n+i].set(i+nv);
	}
	forn(i,n+nv) v[i].set(2*nv);
	bitset<N> ans;
	if(gauss(v, n+nv, 2*nv, ans) == 0) cout << "impossible\n";
	else
	{
		forn(i,nv) if(ans[i]) cout << "F"; else cout << "T";
		cout << '\n';
	}
	return 0;
}
