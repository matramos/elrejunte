#include <cstdio>
#include <cstring>

using namespace std;
char adn[4] = {'A','C','G','T'};
char sol[11];
char all[100000][11];
char input[11];
int n, k, c;

void gen(int nn, int kk)
{
    if(nn == n)
    {
        strncpy(all[c++],sol,n);
        return;
    }
    int diff, i;
    for(i=0;i<4;++i)
    {
        sol[nn]=adn[i];
        diff = sol[nn] != input[nn];
        if(kk+diff > k) continue;
        gen(nn+1, kk+diff);
    }
}

int main()
{
    // freopen("input","r",stdin);
    // freopen("output","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d%*c",&n,&k);
        scanf("%s%*c",input);
        c = 0;
        gen(0,0);
        printf("%d\n",c);
        for(int i=0;i<c;++i)
            printf("%s\n",all[i]);
    }

    return 0;
}
