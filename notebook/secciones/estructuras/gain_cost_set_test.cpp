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
#define MAXN 100010
#define INF 1.5e9

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

// stores pairs (benefit,cost) (erases non-optimal pairs)
// Note that these pairs will be increasing by g and increasing by c
// If we insert a pair that is included in other, the big one will be deleted
// For lis 2d, create a GCS por each posible length, use as (-g, c) and
// binary search looking for the longest length where (-g, c) could be added
struct GCS {
	set<ii> s;
	void add(int g, int c){
		ii x={g,c};
		auto p=s.lower_bound(x);
		if(p!=s.end()&&p->snd<=x.snd)return;
		if(p!=s.begin()) {//erase pairs with less or equal benefit and more cost
			--p;
			while(p->snd>=x.snd){
				if(p==s.begin()){s.erase(p);break;}
				s.erase(p--);
			}
		}
		s.insert(x);
	}
	int get(int gain){ // min cost for the benefit greater or equal to gain
		auto p=s.lower_bound((ii){gain,-INF});
		int r=p==s.end()?INF:p->snd;
		return r;
	}
};

int main()
{
	#ifdef REJUNTE
	freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	GCS outerCandidatesOfLength[MAXN];
	int n, ans = 1;
	cin >> n;
	forn(i,n)
	{
		int a,b,L,R,M;
		cin >> a >> b;
		outerCandidatesOfLength[1].add(-a,b);
		L = 0; R = ans;
		while(L<R)
		{
			M = (L+R+1)/2;
			if(outerCandidatesOfLength[M].get(-a+1) < b) L = M;
			else R = M-1;
		}
		outerCandidatesOfLength[L+1].add(-a,b);
		ans = max(ans, L+1);
	}
	cout << ans << '\n';
	return 0;
}