// problem: https://codeforces.com/gym/104065/problem/L
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforN(i,n) for(int i=n-1;i>=0;i--)
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
typedef pair<int,int> ii;

const int MAX_COST = 1<<30;

struct Node {
	int cnt;
	ll sum;
};
typedef Node tipo;
const tipo neutro = {0,0};
tipo oper(const tipo& a, const tipo& b) {
	return {a.cnt+b.cnt, a.sum+b.sum};
}
// Compressed segtree, it works for any range (even negative indexes)
struct ST {
	ST *lc, *rc;
	tipo ret;
	int L, R;
	ST(int l, int r, tipo x = neutro) {
		lc = rc = nullptr;
		L = l; R = r; ret = x;
	}
	ST(int l, int r, ST* lp, ST* rp) {
		if(lp->L > rp->L) swap(lp, rp);
		lc = lp; rc = rp;
		L = l; R = r;
		ret = oper(lp->ret, rp->ret);
	}
	// O(log(R-L))
	// This operation inserts at most 2 nodes to the tree, i.e. the
	// total memory used by the tree is O(N), where N is the number
	// of times this 'set' function is called.
	void set(int p, tipo x) {
		// might need to CHANGE ret = x with something else
		if(L + 1 == R) { ret = x; return; }
		int m = (L+R) / 2;
		ST** c = p < m ? &lc : &rc;
		if(!*c) *c = new ST(p, p+1, x);
		else if((*c)->L <= p && p < (*c)->R) (*c)->set(p,x);
		else {
			int l = L, r = R;
			while((p < m) == ((*c)->L < m)) {
				if(p < m) r = m;
				else l = m;
				m = (l+r)/2;
			}
			*c = new ST(l, r, *c, new ST(p, p+1, x));
			// The code above, inside this else block, could be
			// replaced by the following 2 lines when the complete
			// range has the form [0, 2^k)
			//int rm = (1<<(32-__builtin_clz(p^(*c)->L)))-1;
			//*c = new ST(p & ~rm, (p | rm)+1, *c, new ST(p, p+1, x));
		}
		ret = oper(lc ? lc->ret : neutro, rc ? rc->ret : neutro);
	}
	// O(log(R-L))
	tipo get(int ql, int qr) {
		if(qr <= L || R <= ql) return neutro;
		if(ql <= L && R <= qr) return ret;
		return oper(lc ? lc->get(ql,qr) : neutro, rc ? rc->get(ql,qr) : neutro);
	}
	tipo find(int k)
	{
		assert(ret.cnt >= k);
		if(ret.cnt == k) return ret;
		if(L+1 == R) return {0, L*(ll)k};
		ll extra = 0;
		if(lc)
		{
			if(lc->ret.cnt >= k) return lc->find(k);
			extra += lc->ret.sum;
			k -= lc->ret.cnt;
		}
		assert(rc);
		tipo asd = rc->find(k);
		asd.sum += extra;
		return asd;
	}
};
// Usage: 1- RMQ st(MIN_INDEX, MAX_INDEX) 2- normally use set/get

vector<vector<int>> g;
vector<int> decider;
vector<vector<int>> vv;
vector<int> vvposOfPerson;

bool cmp(int a, int b)
{
	return decider[a] < decider[b];
}

void dfs(int node)
{
	if(g[node].empty())
	{
		decider[node] = node;
		return;
	}
	forall(it,g[node]) dfs(*it);
	sort(g[node].begin(), g[node].end(), cmp);
	decider[node] = decider[g[node].back()];
	//cout << "dfs " << node << ' ' << sz(g[node]) << endl;
	forall(it,g[node]) if(next(it) != g[node].end())
	{
		int id = decider[*it];
		//cout << "\tid " << id << endl;
		assert(vvposOfPerson[id] == -1);
		vvposOfPerson[id] = node;
		vv[node].pb(id);
	}
}

struct Person {
	int vote, cost;
};

ll getCost(vector<int> vcnt[2], vector<ST> vflip[2], int id)
{
	assert(abs(vcnt[0][id]-vcnt[1][id])%2 == 0);
	int aux = abs(vcnt[0][id]-vcnt[1][id])/2;
	//cout << "when getCost aux=" << aux << ' ' << vcnt[0][id] << ' ' << vcnt[1][id] << endl;
	if(aux == 0) return 0;
	if(vcnt[0][id] > vcnt[1][id]) return vflip[0][id].find(aux).sum;
	return vflip[1][id].find(aux).sum;
}

int main(){
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,m,q;
	cin >> n >> m >> q;
	g.rsz(n+m);
	vector<Person> v(n);
	forn(i,n)
	{
		int vote, cost;
		cin >> vote >> cost;
		v[i] = {vote, cost};
	}
	forn(i,m)
	{
		int k;
		cin >> k;
		forn(_,k)
		{
			int x;
			cin >> x;
			if(x < 0) x = -x + n;
			x--;
			//cout << "add " << i+n << ' ' << x << endl;
			g[i+n].pb(x);
		}
	}
	decider.rsz(n+m);
	vv.rsz(n+m);
	vvposOfPerson.rsz(n,-1);
	dfs(n+m-1);
	forn(i,n-1) assert(vvposOfPerson[i] != -1);
	assert(vvposOfPerson[n-1] == -1);
	vector<int> vcnt[2];
	forn(i,2) vcnt[i] = vector<int>(n+m, 0);
	vector<ST> vflip[2];
	forn(i,2) vflip[i] = vector<ST>(n+m, ST(1, MAX_COST));
	ll ans = 0;
	forn(i,n+m)
	{
		assert(sz(vv[i])%2 == 0);
		forall(it,vv[i]) vcnt[v[*it].vote][i]++, vflip[v[*it].vote][i].set(v[*it].cost, oper(vflip[v[*it].vote][i].get(v[*it].cost, v[*it].cost+1), {1, v[*it].cost}));
		ans += getCost(vcnt, vflip, i);
	}
	forn(_,q)
	{
		int id, vote, cost;
		cin >> id >> vote >> cost;
		id--;
		int vvpos = vvposOfPerson[id];
		if(vvpos == -1)
		{
			//cout << "xd ";
			cout << ans << '\n';
			continue;
		}
		//cout << "changing " << id << ' ' << vvpos << ' ' << v[id].vote << ' ' << v[id].cost << '\n';
		ans -= getCost(vcnt, vflip, vvpos);
		
		vcnt[v[id].vote][vvpos]--;
		vflip[v[id].vote][vvpos].set(v[id].cost, oper(vflip[v[id].vote][vvpos].get(v[id].cost, v[id].cost+1), {-1, -v[id].cost}));
		
		v[id] = {vote, cost};
		
		vcnt[v[id].vote][vvpos]++;
		vflip[v[id].vote][vvpos].set(v[id].cost, oper(vflip[v[id].vote][vvpos].get(v[id].cost, v[id].cost+1), {1, v[id].cost}));
		
		ans += getCost(vcnt, vflip, vvpos);
		cout << ans << endl;
	}
	return 0;
}
