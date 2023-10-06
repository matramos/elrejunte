//Problem: https://www.spoj.com/problems/QTREE/
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
#else
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

#define MAXN 10001

//Dado un arreglo y una operacion asociativa con neutro
#define operacion(x, y) max(x, y)
typedef int tipo;
const tipo neutro=0;
struct RMQ {
	int sz;
	tipo t[4*MAXN];
	tipo &operator[](int p) {return t[sz+p];}
	void init(int n) {//O(nlgn)
		sz = 1 << (32 - __builtin_clz(n));
		forn(i, 2*sz) t[i] = neutro;
	}
	void updall() {dforn(i, sz) t[i]=operacion(t[2*i], t[2*i+1]);} //O(n)
	tipo get(int i, int j) {return get(i,j,1,0,sz);}
	tipo get(int i, int j, int n, int a, int b) {//O(lgn), [i, j)
		if(j<=a || i>=b) return neutro;
		if(i<=a && b<=j) return t[n];//n = node of range [a,b)
		int c = (a+b)/2;
		return operacion(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	void set(int p, tipo val) {//O(lgn)
		p += sz;
		while(p>0 && t[p]!=val) {
			t[p] = val;
			p /= 2;
			val = operacion(t[p*2], t[p*2+1]);
		}
	}
}; //Use: definir operacion tipo neutro y MAXN,
//cin >> n; rmq.init(n); forn(i, n) cin >> rmq[i]; rmq.updall();

vector<ii> g[MAXN];
int wg[MAXN],dad[MAXN],dep[MAXN]; // weight,father,depth
void dfs1(int x){
	wg[x]=1;
	for(ii y:g[x])if(y.fst!=dad[x]){
		dad[y.fst]=x;dep[y.fst]=dep[x]+1;dfs1(y.fst);
		wg[x]+=wg[y.fst];
	}
}
int curpos,pos[MAXN],head[MAXN];
void hld(int x, int c){
	if(c<0)c=x;
	pos[x]=curpos++;head[x]=c;
	int mx=-1;
	for(ii y:g[x])if(y.fst!=dad[x]&&(mx<0||wg[mx]<wg[y.fst]))mx=y.fst;
	if(mx>=0)hld(mx,c);
	for(ii y:g[x])if(y.fst!=mx&&y.fst!=dad[x])hld(y.fst,-1);
}
void hld_init(){dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);}
int query(int x, int y, RMQ &st){
	int r=neutro;
	while(head[x]!=head[y]){
		if(dep[head[x]]>dep[head[y]])swap(x,y);
		r=operacion(r,st.get(pos[head[y]],pos[y]+1));
		y=dad[head[y]];
	}
	if(dep[x]>dep[y])swap(x,y); // now x is lca
	r=operacion(r,st.get(pos[x]+1,pos[y]+1));
	return r;
}
// for updating: rmq.upd(pos[x],v);
// queries on edges: - assign values of edges to "child" node
//                   - change pos[x] to pos[x]+1 in query (line 28)

RMQ st;
vector<int> edgeIdToNode;
map<ii,int> edgeId;

void buildSt(int node, int prev)
{
	forall(it,g[node]) if(it->fst != prev)
	{
		edgeIdToNode[edgeId[mp(node, it->fst)]] = it->fst;
		st[pos[it->fst]] = it->snd;
		buildSt(it->fst, node);
	}
}

int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >> t;
	forn(T,t)
	{
		int n;
		cin >> n;
		forn(i,n-1)
		{
			int a,b,c;
			cin >> a >> b >> c;
			a--;b--;
			edgeId[mp(a,b)] = i;
			edgeId[mp(b,a)] = i;
			g[a].pb(mp(b,c));
			g[b].pb(mp(a,c));
		}
		hld_init();
		st.init(n);
		edgeIdToNode = vector<int>(n-1);
		buildSt(0,0);
		st.updall();
		string s;
		while(cin >> s)
		{
			if(s == "DONE") break;
			if(s == "CHANGE")
			{
				int id,x;
				cin >> id >> x;
				id--;
				st.set(pos[edgeIdToNode[id]], x);
			}
			else
			{
				int a,b;
				cin >> a >> b;
				a--;b--;
				cout << query(a,b,st) << '\n';
			}
		}
		edgeId.clear();
		edgeIdToNode.clear();
		forn(i,n) g[i].clear();
	}
	return 0;
}
