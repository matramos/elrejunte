#include <cstdio>
#include <cstring>

using namespace std;

#define NG 1
#define BL 2
#define NB 3
#define WH 0

char m[501][501];
int cb,cn,i,j,k,p,n,f,tcb,tcn;
char x;


int main(int argc, char const *argv[])
{
	//freopen("input","r",stdin);
	//memset(m,WH,sizeof m);
	scanf("%d %d",&n,&p);
	for(k=0;k<p;++k){scanf("%d %d",&i,&j);m[i][j]=NG;}
	for(k=0;k<p;++k){scanf("%d %d",&i,&j);m[i][j]=BL;}

	cn = cb = p;
	for(k=2;k<n;++k)
	{
		f = n-k+1;
		tcn = tcb = 0;
		for(i=1;i<=f;++i)
			for(j=1;j<=f;++j)
			{
				m[i][j] = x = m[i][j] | m[i][j+1] | m[i+1][j+1] | m[i+1][j];
				
				if(x==NG) ++tcn;
				else if(x==BL) ++tcb;
			}
		// for(i=1;i<=f;++i){
		// 	for(j=1;j<=f;++j)printf("%c",m[i][j] == 0?'@': m[i][j] == 1? 'N' : m[i][j] == 2? 'B' : 'X');
		// 	printf("\n");
		// }
		// printf("\n");
		if(tcn!=0 || tcb!=0) cn+=tcn, cb+=tcb;
		else break;
	}

	printf("%d %d\n",cn, cb);

	return 0;
}
