#include <bits/stdc++.h>

using namespace std;


typedef long long ll;

#define MAXST 262146
#define left(x) (x<<1)
#define right(x) ((x<<1)+1)
#define middle(l,r) (((l)+(r))>>1)
#define pb(x) push_back(x)

ll st[MAXST], lazy[MAXST];
vector <int> arr;

inline void build(int node, int a, int b){
	if(a>b) return;
	if(a==b) {st[node] = arr[a]; return;}
	int l = left(node), r = right(node), m = middle(a,b);
	build(l,a,m);
	build(r,m+1,b);
	st[node] = st[l] * st[r];
}

void update(int node, int a, int b, int i, ll value)
{
    int l = left(node), r=right(node), m=middle(a,b);
    
    if(a>i || b<i || a>b) return;

     
    if(a == b){
		st[node] = value;
    // if(a!=b){lazy[l] += value; lazy[r] += value;}
    	return;
	}

    update(l, a, m, i, value);
    update(r, m+1,b,i, value);

    st[node] = st[r]*st[l];
}


ll query(int node, int a, int b, int i, int j)
{
    
    if(a>b or a>j or b<i) return 1;

    int l = left(node), r=right(node), m=middle(a,b);    

    if(a>=i && b<=j) return st[node];

    ll ql = query(l, a, m, i, j);
    ll qr = query(r, m+1, b, i, j);
    return ql * qr;
}

int main()  
{
    
    //freopen("input","r",stdin);
    // freopen("output","w",stdout);

    int n, k, pos;
    ll j, sal;
    char op;

    while(cin>>n>>k)
    {
    	arr.resize(n+1);
        for (int i = 1; i <= n; ++i)
        {
        	cin>>arr[i];
        	if(arr[i] != 0) arr[i] /= abs(arr[i]);
        }

        build(1,1,n);
        while(k--)
        {
            cin>>op>>pos>>j;
            if(op == 'C') {
            	if(j != 0) j /= abs(j);
            	update(1,1,n,pos,j);
            }

            else
            {
                sal = query(1,1,n,pos, j);
                if(sal>0) cout<<"+";
                else if (sal<0) cout<<"-";
                else cout<<"0";
            }
        }
        cout<<"\n";
        arr.clear();
    }


    return 0;
}
