#include <cstdio>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

#define INF 100000000

typedef vector<short> vi;
typedef pair<int,int> ii;

map<int, set<ii> > g;
map<int,int> dist;
int movs[10][2] = {{10000000,1000000},{10000000,1000},{1000000,100000},{1000000,100},{100000,10000},{100000,10},{10000,1},{1000,100},{100,10},{10,1}};
vi pstart, pend;

set<ii> get_adj(int inicio){
    int i,a,b,r,p0,p1;
    set<ii> ret;
    for(i=0;i<10;++i){
        r = inicio;
        p0 = movs[i][0];
        p1 = movs[i][1];
        a = (inicio / p0) % 10;
        b = (inicio / p1) % 10;
        r -= ((a*p0) + (b*p1));
        r += ((a*p1) + (b*p0));
        ret.insert(ii(r, pstart[a-1]+pstart[b-1]));
    }
    return ret;
}


void make_graph(int node)
{
    if(g.find(node) == g.end())
    {
        dist[node]=INF;
        set<ii> s = get_adj(node);
        g[node]  = s;
        for(set<ii>::iterator i=s.begin(); i!=s.end(); ++i )
        {
//            printf("i->second: %d\n",i->second);
            make_graph(i->first);
        }
    }
}

int index(int o, vi& v)
{
    for(int i=0;i<v.size();++i)
        if(o==v[i]) return i;
    return -1;
}


int main()
{
    //freopen("input","r",stdin);
    //freopen("output","w",stdout);
    int s=0,e=0, m, tmp, ix;
    bool flag;

    m=10000000; flag=true;
    for(int i=0;i<8;++i)
    {
        scanf("%d",&tmp);
        pstart.push_back(tmp);

        ix = index(tmp, pstart);
        if(ix==-1) s+=(pstart.size() * m);
        else s+= (ix+1)*m;
        m/=10;
    }

    m=10000000; flag=true;
    for(int i=0;i<8;++i)
    {
        scanf("%d",&tmp);
        pend.push_back(tmp);
        ix = index(tmp, pstart);
        e+= ((ix+1)*m);
        m/=10;
    }

    make_graph(s);

    dist[s] = 0;                    // INF = 1B to avoid overflow
    priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0,s));
                             // ^to sort the pairs by increasing distance from s
      while (!pq.empty()) {                                             // main loop
        ii front = pq.top(); pq.pop();     // greedy: pick shortest unvisited vertex
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;   // this check is important, see the explanation
        for(set<ii>::iterator sit=g[u].begin(); sit!=g[u].end(); ++sit){
        //for (int j = 0; j < (int)AdjList[u].size(); j++) {
          ii v = *sit;                       // all outgoing edges from u
          if (dist[u] + v.second < dist[v.first]) {
            dist[v.first] = dist[u] + v.second;                 // relax operation
            pq.push(ii(dist[v.first], v.first));
      } } }  // note: this variant can cause duplicate items in the priority queue

    
    printf("%d\n",dist[e]);

    return 0;
}