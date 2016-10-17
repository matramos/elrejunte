#include <cstdio>
#include <map>
using namespace std;


int main()
{
    
    //freopen("output","w",stdout);

    int t, n,x ;
    map<int,bool> m;
    scanf("%d",&t);
    
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i){scanf("%d",&x); m[x] ^= true;}
        for(map<int,bool>::iterator i = m.begin(); i!=m.end(); ++i)
            if(i->second == true) {printf("%d\n",i->first); break;}
        m.clear();
    }



    return 0;
}
