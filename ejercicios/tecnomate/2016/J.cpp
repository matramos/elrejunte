#include <iostream>
#include <bitset>
using namespace std;

int main(int argc, char *argv[]) {
    //freopen("input/K.in","r",stdin);
	ios_base::sync_with_stdio(false);
    bitset<1000> focos;
    int t,n,m,a,b,aux,resp;
    cin >> t;
    for (int j=0;j<t;j++)
    {
        cin >> n >> m;
        focos.reset();
        resp=0;
        for (int i=0;i<m;i++)
        {
            cin >> a >> b;
            if (b<a) {aux=a;a=b;b=aux;}
            while (a<=b)
            {
                focos.flip(a);
                a++;
            }
        }
        for (int i=0;i<n;i++)
        {
            if (focos[i]) resp++;
        }
        cout << resp << "\n";
    }
	return 0;
}
