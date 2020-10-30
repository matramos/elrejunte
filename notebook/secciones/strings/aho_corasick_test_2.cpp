//https://codeforces.com/contest/1437/problem/G
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

struct vertex {
	map<char,int> next,go;
	int p,link,leafLink;
	char pch;
	vector<int> leaf;
	multiset<int> vals;
	vertex(int p=-1, char pch=-1):p(p),link(-1),leafLink(-1),pch(pch){}
};
vector<vertex> t;
void aho_init(){ //do not forget!!
	t.clear();t.pb(vertex());
}

vector<int> nodeOfId;

void add_string(string &s, int id){
	int v=0;
	for(char c:s){
		if(!t[v].next.count(c)){
			t[v].next[c]=t.size();
			t.pb(vertex(v,c));
		}
		v=t[v].next[c];
	}
	t[v].leaf.pb(id);
	nodeOfId[id] = v;
	t[v].vals.insert(0);
	//cout << v << '\n';
}
int go(int v, char c);
int get_link(int v){
	if(t[v].link<0)
		if(!v||!t[v].p)t[v].link=0;
		else t[v].link=go(get_link(t[v].p),t[v].pch);
	return t[v].link;
}
int go(int v, char c){
	if(!t[v].go.count(c))
		if(t[v].next.count(c))t[v].go[c]=t[v].next[c];
		else t[v].go[c]=v==0?0:go(get_link(v),c);
	return t[v].go[c];
}
int get_leaf_link(int v){
	if(t[v].leafLink < 0){
		if(!v||!t[v].p) t[v].leafLink = 0;
		else
		{
			if(t[get_link(v)].leaf.empty()) t[v].leafLink = get_leaf_link(t[v].link);
			else t[v].leafLink = t[v].link;
		}
	}
	return t[v].leafLink;
}
int goUp(int v){
	if(v == 0) return -1;
	int ret = -1;
	if(!t[v].vals.empty())
	{
		ret = *t[v].vals.rbegin();
		//cout << "found leaf " << ret << '\n';
	}
	ret = max(ret, goUp(get_leaf_link(v)));
	//cout << v << ' ' << ret << '\n';
	return ret;
}


int findMaxSubstr(string &s)
{
	int ret = -1, node = 0;
	forn(i,sz(s))
	{
		node = go(node, s[i]);
		ret = max(ret, goUp(node));
	}
	return ret;
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
	int n,q;
	cin >> n >> q;
	aho_init();
	vector<string> vs(n);
	vector<int> v(n, 0);
	nodeOfId = vector<int>(n);
	forn(i,n)
	{
		cin >> vs[i];
		add_string(vs[i], i);
	}
	forn(_,q)
	{
		int tq;
		cin >> tq;
		if(tq == 1)
		{
			int id, x;
			cin >> id >> x;
			id--;
			t[nodeOfId[id]].vals.erase(t[nodeOfId[id]].vals.find(v[id]));
			v[id] = x;
			t[nodeOfId[id]].vals.insert(v[id]);
		}
		else
		{
			string x;
			cin >> x;
			cout << findMaxSubstr(x) << '\n';
		}
	}
	return 0;
}
