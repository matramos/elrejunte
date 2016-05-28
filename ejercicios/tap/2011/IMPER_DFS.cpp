#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define INF (1<<31)
#define max(a,b) ((a)>(b)?(a):(b))

int n, max_dist, max_v;
int dist[10001];
int adj[10001][10001];

void bfs(int s){
    for(int i=1;i<=n;++i)dist[i]=INF;
    queue<int> q;
    dist[s] = 0;
    q.push(s);

    while(!q.empty()){
        int u = q.front();q.pop();
        for(int i=1;i<=adj[u][0]; ++i)
        {
            int v = adj[u][i];
            if(dist[v]==INF){
                dist[v] = dist[u]+1;

                if (max_dist <dist[v]){
                    max_dist = dist[v];
                    max_v = v;
                }

                q.push(v);
            }
        }
    }
}



int main()
{
    freopen("input","r",stdin);
    freopen("output","w",stdout);

    int i, j, u, v;
    

    while(scanf("%d",&n) && n!=-1){
        for(i=1;i<=n;++i)adj[i][0]=0;
        max_dist = 0;
        
        for(i=0, u = 2;i<n-1;++i, ++u){
            scanf("%d",&v);
            adj[u][ ++adj[u][0] ] = v;
            adj[v][ ++adj[v][0] ] = u;
        }

        bfs(1);
        max_dist=0;
        bfs(max_v);
        printf("%d\n",(max_dist+1)/2);
    }



    return 0;
}
