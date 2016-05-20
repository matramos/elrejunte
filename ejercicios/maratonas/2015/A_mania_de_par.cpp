#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 1000000000

typedef long long ll;

struct edge
{
  int v; ll w;
  edge(int _v,ll _w):v(_v),w(_w){};
  bool operator<(const edge& o) const {return w > o.w;}
};


typedef vector<edge> ve;
typedef vector<ve> vie;


int main() {
    int c,v,a,b,i,j; ll w;

    while(scanf("%d %d",&c,&v)!=EOF)
    {
        vie adj(c+1, ve());
        priority_queue< edge, ve> pq;

        for(int i=0;i<v;++i)
        {
            scanf("%d %d %lld",&a,&b,&w);
            adj[a].push_back(edge(b,w));
            adj[b].push_back(edge(a,w));
        }

        vector<ll> dist(c+1,INF); dist[c]=0LL;
        pq.push(edge(c,0LL));

        while(!pq.empty())
        {
            edge e = pq.top(); pq.pop();
            
            if(e.w > dist[e.v]) continue;

            for(i=0;i<adj[e.v].size();++i)
            {
		//estos son los "arcos" que se toman en un dijkstra común
		// o lo que es lo mismo, los "arcos" de distancia impar
                edge n_i = adj[e.v][i];

		//en cambio nos fijamos en los "arcos" de los vecinos
		// o lo que es lo mismo, los "arcos" de distancia par.
                for (j=0; j < adj[n_i.v].size(); ++j)
                {
                    edge n_p = adj[n_i.v][j];
		    // hay que tener en cuenta los pesos de nuestro padre (n_i)
                    if(dist[e.v] + n_p.w + n_i.w < dist[n_p.v])
                    {
                        dist[n_p.v] = dist[e.v] + n_p.w + n_i.w;
                        n_p.w=dist[n_p.v];
                        pq.push(n_p);
                    }
                }
            }
        }


        printf("%lld\n", dist[1]==INF?-1:dist[1]);
    }

  
    return 0;
}
