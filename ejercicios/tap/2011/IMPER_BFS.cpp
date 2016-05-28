#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define INF -1

int adj[10001][10001];
int d[10001];

int bfs(int n, int s)
{
    memset(d,-1,(n+1)*4);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    int i,v,f, w;
    while(!q.empty()){
        v = q.front(); q.pop();
        for(i=1,f=adj[v][0];i<=f;++i){
            w = adj[v][i];
            if(d[w]==INF){
                d[w]=d[v]+1;
                q.push(w);
            }
        }
    }
    return v;
}


int main()
{
    // freopen("input","r",stdin);
    //freopen("output","w",stdout);

    int n,i,v,w;
    while(scanf("%d",&n) && n!=-1)
    {
            
        for(i=1;i<=n;++i) adj[i][0]=0;

        for(i=1, v=2;i<n;++i,++v){
            scanf("%d",&w);
            adj[v][++adj[v][0]] = w;
            adj[w][++adj[w][0]] = v;
        }
        
        printf("%d\n",(d[bfs(n,bfs(n,1))]+1)/2);
    }
    


    return 0;
}
