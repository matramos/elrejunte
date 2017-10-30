struct UnionFind {
	int n, comp;
	vector<int> pre,si,c;
	UnionFind(int n=0):n(n), comp(n), pre(n), si(n, 1) {
		forn(i,n) pre[i] = i; }
	int find(int u){return u==pre[u]?u:find(pre[u]);}
	bool merge(int u, int v)
	{
		if((u=find(u))==(v=find(v))) return false;        
		if(si[u]<si[v]) swap(u, v);
		si[u]+=si[v], pre[v]=u, comp--, c.pb(v);
		return true;
	}
	int snap(){return sz(c);}
	void rollback(int snap)
	{
		while(sz(c)>snap)
		{
			int v = c.back(); c.pop_back();
			si[pre[v]] -= si[v], pre[v] = v, comp++;
		}
	}
};
enum {ADD,DEL,QUERY};
struct Query {int type,u,v;};
struct DynCon{
	vector<Query> q;
	UnionFind dsu;
	vector<int> match,res;
	map<ii,int> last;//se puede no usar cuando hay identificador para cada arista (mejora poco)
	DynCon(int n=0):dsu(n){}
	void add(int u, int v)
	{
		if(u>v) swap(u,v);
		q.pb((Query){ADD, u, v}), match.pb(-1);
		last[ii(u,v)] = sz(q)-1;
	}
	void remove(int u, int v)
	{
		if(u>v) swap(u,v);
		q.pb((Query){DEL, u, v});
		int prev = last[ii(u,v)];
		match[prev] = sz(q)-1;
		match.pb(prev);
	}
	void query()
	{
		q.pb((Query){QUERY, -1, -1}), match.pb(-1);
	}
	void process() 
	{
		forn(i,sz(q)) if (q[i].type == ADD && match[i] == -1) match[i] = sz(q);
		go(0,sz(q));
	}
	void go(int l, int r) 
	{
		if(l+1==r)
		{
			if (q[l].type == QUERY)//Aqui responder la query usando el dsu!
				res.pb(dsu.comp);//aqui query=cantidad de componentes conexas
			return;
		}
		int s=dsu.snap(), m = (l+r) / 2;
		forr(i,m,r) if(match[i]!=-1 && match[i]<l) dsu.merge(q[i].u, q[i].v);
		go(l,m);
		dsu.rollback(s);
		s = dsu.snap();
		forr(i,l,m) if(match[i]!=-1 && match[i]>=r) dsu.merge(q[i].u, q[i].v);
		go(m,r);
		dsu.rollback(s);
	}
}dc;
