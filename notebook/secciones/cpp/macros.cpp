//buffers
#define MEMZ(mem) memset(mem, 0, sizeof mem) // memset => <cstring / string.h >
#define MEMX(mem,x) memset(mem, (x), sizeof mem)

//loops
#define forall(i,a,b) for(int (i)=(a);(i)<(b);++(i))
#define foreach(i,v) for(typeof((v).begin()) (i) = (v).begin(); (i) != (v).end(); ++(i))

//map/pairs
#define mp make_pair
#define fi first
#define se second

//vector
#define pb push_back

//queries
#define in(a,v) ((v).find((a))!=(v).end()) // <algorithm>