const int MAXN  = ...;
const int MAXST = (int) (2*exp2(ceil(log2(MAXN)))+1);

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define OP(a,b) (max(a,b)) // operador binario asociativo
#define NEUTRO 0		   // elemento neutro del operador

#define left(x) ((x)<<1)
#define right(x) (((x)<<1)+1)
#define middle(a,b) (((a)+(b))>>1)

int st[MAXST], lazy[MAXST], arr[MAXN+1];

void build(int node, int a, int b)
{
	if(a>b) return;
	if(a==b) {st[node] = arr[a]; return;}
	int l = left(node), r = right(node), m = middle(a,b);
	build(l,a,m);
	build(r,m+1,b);
	st[node] = OP(st[l], st[r]);
}

void update(int node, int a, int b, int i, int j, int value)
{
	int l = left(node), r = right(node), m = middle(a,b);

	if(lazy[node]!=0)
	{
		st[node] = lazy[node]; // SET [a,b] to value
		//      += lazy[node]; // ADD value to [a,b]
		if(a!=b) lazy[l] = lazy[r] = lazy[node]; // SET
		//	     lazy[l] +=lazy[node], lazy[r] += lazy[node]; // ADD
		lazy[node] = 0;
	}

	if(a>b || a>j || b<i) return;

	if(a>=i && b<=j)
	{
		st[node] = value; // SET
		//		+= value; // ADD
		if(a!=b) lazy[l] = lazy[r] = value; // SET
		//		 lazy[l] += value, lazy[r] += value; // ADD
		return;
	}

	update(l,a,m,i,j,value);
	update(r,m+1,b,i,j,value);

	st[node] = OP(st[l], st[r]);
}

int query(int node, int a, int b, int i, int j)
{
	if(a>b || a>j || b<i) return NEUTRO; 

	int l = left(node), r = right(node), m = middle(a,b);

	if(lazy[node]!=0)
	{
		st[node] = lazy[node]; // SET [a,b] to value
		//      += lazy[node]; // ADD value to [a,b]
		if(a!=b) lazy[l] = lazy[r] = lazy[node]; // SET
		//		 lazy[l] +=lazy[node], lazy[r] += lazy[node]; // ADD
		lazy[node] = 0;
	}

	if(a>=i && b<=j) return st[node];

	int ql = query(l,a,m,i,j);
	int qr = query(r,m+1,b,i,j);

	return OP(ql, qr);
}
