#define MAXN 1000000
vector<int> G[MAXN],gt[MAXN]; //Limpiar si se corre mas de una vez
//nodos 0...N-1 ; componentes 0...cantcomp-1
int comp[MAXN],N,cantcomp,used[MAXN];
stack<int> pila;
void add(int a, int b){ G[a].pb(b);gt[b].pb(a);}
void dfs1(int nodo)
{
	used[nodo]=1;
	forall(it,G[nodo]) if(!used[*it]) dfs1(*it);
	pila.push(nodo);
}
void dfs2(int nodo)
{
	used[nodo]=2;
	comp[nodo]=cantcomp-1;
	forall(it,gt[nodo]) if(used[*it]!=2) dfs2(*it);
}
void kosaraju()
{
	cantcomp=0;
	memset(used,0,sizeof(used));
	forn(i,N) if(!used[i]) dfs1(i);
	while(!pila.empty())
	{
		if(used[pila.top()]!=2)
		{
			cantcomp++;
			dfs2(pila.top());
		}
		pila.pop();
	}
}