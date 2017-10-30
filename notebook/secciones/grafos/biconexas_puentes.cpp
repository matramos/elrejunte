vector<int> G[MAXN];

struct edge{
	int u,v, comp;
	bool bridge;
};
vector<edge> e;
void addEdge(int u, int v)
{
	G[u].pb(sz(e)), G[v].pb(sz(e));
	e.pb((edge){u,v,-1,false});
}
//d[i]=id de la dfs
//b[i]=lowest id reachable from i
int d[MAXN], b[MAXN], t;
int nbc;//cant componentes
int comp[MAXN];//comp[i]=cant comp biconexas a la cual pertenece i
void initDfs(int n)
{
	zero(G), zero(comp);
	e.clear();
	forn(i,n) d[i]=-1;
	nbc = t = 0;
}
stack<int> st;
void dfs(int u,int pe) //O(n + m)
{
	b[u]=d[u]=t++;
	comp[u]=(pe!=-1);
	forall(ne,G[u]) if(*ne!=pe)
	{
		int v=e[*ne].u ^ e[*ne].v ^ u;
		if(d[v]==-1)
		{
			st.push(*ne);
			dfs(v,*ne);
			if(b[v]>d[u]) e[*ne].bridge=true; // bridge
			if(b[v]>=d[u])  // art
			{
				int last;
				do 
				{
					las=st.top(); st.pop();
					e[last].comp=nbc;
				}while(last!=*ne);
				nbc++;
				comp[u]++;
			}
			b[u]=min(b[u],b[v]);
		}
		else if(d[v]<d[u])  // back edge
		{
			st.push(*ne);
			b[u]=min(b[u], d[v]);
		}
	}
}
