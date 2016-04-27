#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

void gcd_ext(int a, int b, int&x, int& y, int& gcd) 
{
    if (b == 0) { x = 1; y = 0; gcd = a; return; }
    gcd_ext(b, a % b,x,y,gcd);
    int x1 = y;
    int y1 = x - (a / b) * y;
    x = x1;
    y = y1;
}



int main()
{
    // freopen("input","r",stdin);
    // freopen("output","w",stdout);

    int x,y, d=1;
    gcd_ext(99,78,x,y,d);
    printf("%d %d %d\n", x,y,d);


    return 0;
}
