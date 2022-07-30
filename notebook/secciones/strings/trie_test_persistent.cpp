// Problem: https://codeforces.com/problemset/problem/916/D
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

struct Trie{
	vector<Trie*> m;
	int cnt = 0, x = -1;
	void clone(int pos, int sz)
	{
		if(m.empty()) m.rsz(sz, NULL);
		Trie* prev = NULL;
		prev = m[pos];
		m[pos] = new Trie();
		if(prev != NULL)
		{
			m[pos]->m = prev->m;
			m[pos]->x = prev->x;
			m[pos]->cnt = prev->cnt;
		}
	}
	// update or insert
	void upsert(const string &s, int newx, int p)
	{
		if(p < sz(s))
		{
			clone(s[p]-'a', 26);
			m[s[p]-'a']->upsert(s, newx, p+1);
		}
		else x = newx;
	}
	int getx(string s, int p)
	{
		if(p < sz(s))
		{
			if(m.empty() || m[s[p]-'a'] == NULL) return -1;
			return m[s[p]-'a']->getx(s, p+1);
		}
		return x;
	}
	
	
	void add(int bm, int p)
	{
		if(p >= 0)
		{
			clone((bm&(1<<p)) != 0, 2);
			m[(bm&(1<<p)) != 0]->add(bm, p-1);
		}
		cnt++;
	}
	void remove(int bm, int p)
	{
		if(p >= 0)
		{
			assert(sz(m) == 2 && m[(bm&(1<<p)) != 0] != NULL);
			clone((bm&(1<<p)) != 0, 2);
			m[(bm&(1<<p)) != 0]->remove(bm, p-1);
		}
		assert(--cnt >= 0);
	}
	int count(int bm, int p)
	{
		if(p == -1 || m.empty()) return 0;
		assert(sz(m) == 2);		
		int ret = m[(bm&(1<<p)) != 0]->count(bm, p-1);
		if((bm&(1<<p)) != 0 && m[0] != NULL) ret += m[0]->cnt;
		return ret;
	}
};

int solve(Trie* tn, Trie* tx, string& name)
{
	//cout << "solve " << name << endl;
	int aux = tn->getx(name, 0);
	//cout << "aux " << aux << endl;
	if(aux == -1) return aux;
	return tx->count(aux,29);
}

pair<Trie*, Trie*> update(Trie* tn, Trie* tx, string& name, int x)
{
	assert(tn != NULL);
	assert(tx != NULL);
	Trie* newtn = new Trie();
	newtn->m = tn->m;
	newtn->upsert(name, x, 0);
	Trie* newtx = new Trie();
	newtx->m = tx->m;
	newtx->cnt = tx->cnt;
	int aux = tn->getx(name, 0);
	//cout << name << ' ' << aux << ' ' << newtn->getx(name, 0) << endl;
	if(aux != -1) newtx->remove(aux,29);
	if(x != -1) newtx->add(x,29);
	return mp(newtn, newtx);
}

int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out","w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int q;
	cin >> q;
	vector<Trie*> vn, vx;
	vn.pb(new Trie());
	vx.pb(new Trie());
	forn(_,q)
	{
		string s;
		cin >> s;
		if(s == "undo")
		{
			int a;
			cin >> a;
			vn.pb(vn[max(0,sz(vn)-1-a)]);
			vx.pb(vx[max(0,sz(vx)-1-a)]);
		}
		else if(s == "query")
		{
			string a;
			cin >> a;
			cout << solve(vn.back(), vx.back(), a) << endl;
			vn.pb(vn.back());
			vx.pb(vx.back());
		}
		else
		{
			string a;
			cin >> a;
			int x = -1;
			if(s == "set") cin >> x;
			pair<Trie*, Trie*> aux = update(vn.back(), vx.back(), a, x);
			vn.pb(aux.fst);
			vx.pb(aux.snd);
		}
	}
	return 0;
}

