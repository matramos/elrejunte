//Problem: https://codeforces.com/contest/1423/problem/B
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
//prueba
#else
//real
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
deque<pair<int,ii>> agregar;



#define MAXN 10003

vector<int> g[MAXN]; // [0,n)->[0,m)
int n,m;
int mt[MAXN],mt2[MAXN],ds[MAXN];
bool bfs(){
	queue<int> q;
	memset(ds,-1,sizeof(ds));
	forn(i,n)if(mt2[i]<0)ds[i]=0,q.push(i);
	bool r=false;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int y:g[x]){
			if(mt[y]>=0&&ds[mt[y]]<0)ds[mt[y]]=ds[x]+1,q.push(mt[y]);
			else if(mt[y]<0)r=true;
		}
	}
	return r;
}
bool dfs(int x){
	for(int y:g[x])if(mt[y]<0||ds[mt[y]]==ds[x]+1&&dfs(mt[y])){
		mt[y]=x;mt2[x]=y;
		return true;
	}
	ds[x]=1<<30;
	return false;
}
int mm(){
	int r=0;
	memset(mt,-1,sizeof(mt));memset(mt2,-1,sizeof(mt2));
	while(bfs()){
		forn(i,n)if(mt2[i]<0)r+=dfs(i);
	}
	return r;
}



int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
		unsigned t0, t1; t0=clock();
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n;	m=n;
	int a;	cin >> a;
	forn(i,a){
		int u,v, d; cin >> u >> v >> d;
		u--; v--;
		agregar.pb(mp(d, mp(u, v)));
	}
	sort(agregar.begin(), agregar.end());
	
	auto last = agregar.end();	last--;
	int L = 0, R = last->fst+2;
		
	while(L<R){
		
		int M = (L+R)/2;
		forn(i,n) g[i].clear();
		forall(it, agregar){
			if(it->fst <= M) g[it->snd.fst].pb(it->snd.snd);
			else break;
		}
		
		if(mm()==n) R = M;
		else L = M+1;
	}
	if(L == last->fst+2) cout << "-1\n";
	else cout << L << "\n";
	
	#ifdef ANARAP
	t1 = clock();double time = (double(t1-t0)/CLOCKS_PER_SEC); cout << "Execution Time: " << time << endl;
	#endif
	return 0;
}
 


