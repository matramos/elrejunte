#include <cstdio>
#include <cstring>
using namespace std;

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define abs(x) ((x)<0?(-(x)):(x))

int n, cnt=0, r=0,rd=0,d=0, e=0;
char s[101], *p;

char check()
{
    char eq=0;
    p=s;
    e=0;
    while(*p){

        //D
        if(*p == 'D'){
            if(e==0) eq='D',e=1;
            else if(e==2) eq='X',e=3;
            
        } else if (*p == 'R') {
            if(e==0) eq='R', e=2;
            else if(e==1) eq=0, e=0, ++cnt;
            else if(e==3) eq='R', e=2, ++cnt;
        }
        ++p;
    }
    return eq;
}

int main(int argc, char const *argv[])
{
    freopen("input","r",stdin);
    scanf("%d\n", &n);
    char ret;
    int  t;
    while(n--){
        scanf("%s\n",s);

        ret = check();
        printf("(%s) = [%c] [cnt = %d] \n", s, ret , cnt);
        if(ret=='D') ++d;
        else if(ret=='R') ++r;
        else if(ret=='X') ++rd;
    }

    t = min(rd, min(d,r));
    cnt += (2*t);
    d -= t;
    r -= t;
    rd -= t;

    if(r == 0){
        cnt += min(d,rd);
        cnt += (rd / 2);
    }else if (d == 0){
        cnt += min(r,rd);
        cnt += (rd / 2);
    }else {
        cnt += min(d,r);
    }


    printf("%d\n", cnt );

    return 0;
}