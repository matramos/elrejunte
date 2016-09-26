#include <cstdio>
#include <vector>
using namespace std;

int cnt=0;

vector<bool> a;
vector<int> pap;
vector<vector<int> > g;

void dfs(int x){
    if(!a[x] || pap[x]!=0) return;
    ++cnt;
    for(int i=0, j=g[x].size(); i<j; ++i) dfs(g[x][i]);
}


int main()
{
    freopen("input","r",stdin);
    //freopen("output","w",stdout);
    int n, e, u, v, i, j, x;
    scanf("%d %d\n",&n,&e);

    pap.assign(n+1,0);
    a.assign(n+1,false);
    g.assign(n+1, vector<int>());
    
    while(e--){
        scanf("%d %d\n",&u,&v);
        g[u].push_back(v);
        ++pap[v];
    }

    for(i=0;i<n;++i){
        scanf("%d",&x);
        a[x]=true;
        for (std::vector<int>::iterator it = g[x].begin(); it!= g[x].end(); ++it)
            --pap[*it];
        //for(i=0, j=g[x].size(); i<j; ++i) --pap[g[x][i]];
        dfs(x);
        printf("%d\n", cnt);
    }



/*    for(i=1;i<=n;++i){
        printf("[%d] =>", i);
        for(j=0;j<g[i].size();++j)printf(" %d",g[i][j]);
        printf("\n");
    }
    
    for(i=1;i<=n;++i){
        printf("%d",pap[i]);
    }
*/

    return 0;
}


