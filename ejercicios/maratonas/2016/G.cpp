#include <cstdio>
#include <cstring>

using namespace std;

char m[501][501];
int cb,cn,i,j,k,n,p,f;
char s;

int main()
{
    memset(m1,'*', sizeof m1);
    
    freopen("input","r",stdin);
    //freopen("output","w",stdout);
    
    scanf("%d %d",&n,&p);
    for(k=0;k<p;++k){scanf("%d %d",&i,&j); m[i][j]='N';}
    for(k=0;k<p;++k){scanf("%d %d",&i,&j); m[i][j]='B';}
    
    cn=cb=p;
    for(k=2;k<n;++k)
    {
        f = n-k;
        if(k&1){

        }
        else{
            for(i=1;i<f;++i)
            {
                for(j=1;j<f;++j)
                {
                    s = m1[i][j];

                    m2[i][j] = 
                }
            }
        }
    }

    return 0;
}