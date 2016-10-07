#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef pair<vi,int> pvii;
typedef vector<pvii> vpvii;
typedef pair<int,vi> pivi;

#define INF 100000000
#define pb push_back
#define fi first
#define se second

map<vi, vector<pvii> > g;
map<vi, int> dist;
vi ws, we;

int movs[10][2] = {{0,1},{1,2},{2,3},{4,5},{5,6},{6,7},{0,4},{1,5},{2,6},{3,7}};

vpvii get_adj(vi node)
{
    vpvii ret;
    for(int i=0,a,b,x; i<10;++i)
    {
        a = movs[i][0], b = movs[i][1];
        x = node[a], node[a]=node[b], node[b]=x;
        ret.pb(pvii(node,node[a]+node[b]));
        x = node[a], node[a]=node[b], node[b]=x;
    }
    return ret;
}

void make_graph(vi node)
{
    if(g.find(node)==g.end())
    {
        g[node] = get_adj(node);
        dist[node] = INF;
        for(vpvii::iterator i=g[node].begin();i!=g[node].end();++i)
            make_graph(i->first);
    }
}

int main()
{
    // freopen("input","r",stdin);
    //freopen("output","w",stdout);
    g.get_allocator().allocate(40320);
    dist.get_allocator().allocate(40320);

    int i,tmp;
    for(i=0;i<8;++i){scanf("%d",&tmp);ws.pb(tmp);}
    for(i=0;i<8;++i){scanf("%d",&tmp);we.pb(tmp);}

    make_graph(ws);

    priority_queue< pivi, vector<pivi>, greater<pivi> > pq;
    dist[ws] = 0;
    pq.push(pivi(0,ws));
    vi u; int d, du, dv;pvii v;
    while(!pq.empty())
    {
        pivi front = pq.top(); pq.pop();
        d = front.fi;  u = front.se; du = dist[u]; 
        if(d > du) continue;
        for(vpvii::iterator it=g[u].begin();it!=g[u].end();++it)
        {
            v = *it;
            dv = dist[v.fi];
            if(du+v.se < dv)
            {
                dv = du+v.se;
                dist[v.fi] = dv;
                pq.push(pivi(dv,v.fi));
            }
        }
    }
    printf("%d\n",dist[we]);
    return 0;
}