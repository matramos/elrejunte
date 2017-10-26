vector<int> G[MAXN];
bool taken[MAXN];//poner todos en FALSE al principio!!
int padre[MAXN];//padre de cada nodo en el centroid tree

int szt[MAXN];
void calcsz(int v, int p) {
	szt[v] = 1;
	forall(it,G[v]) if (*it!=p && !taken[*it])
		calcsz(*it,v), szt[v]+=szt[*it];
}
void centroid(int v=0, int f=-1, int lvl=0, int tam=-1) {//O(nlogn)
	if(tam==-1)	calcsz(v, -1), tam=szt[v];
	forall(it, G[v]) if(!taken[*it] && szt[*it]>=tam/2)
		{szt[v]=0; centroid(*it, f, lvl, tam); return;}
	taken[v]=true;
	padre[v]=f;
	forall(it, G[v]) if(!taken[*it])
		centroid(*it, v, lvl+1, -1);
}
