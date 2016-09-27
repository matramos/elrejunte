#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

typedef pair<int,int> ref;
typedef pair<int,ref> clave;
map<clave,double> mapa;

double calcular(int,int,int);

int main()
{
	ios_base::sync_with_stdio(false);
	int n,x,y;
	map<clave,double>::iterator it;
	while (cin >> n >> x >> y) cout << fixed << setprecision(4) << calcular(n,x,n-y) << "\n";
	return 0;
}

double calcular(int cant,int num,int dentrodecuantopierdo)
{
	if (num==1)
	{
		if (dentrodecuantopierdo==cant-1) return 1;
		else return 0;
	}
	if (dentrodecuantopierdo==cant-1) return 0;
	int casos=cant*(cant-1)/2;
	int casosenquepierdo=num-1;
	if (dentrodecuantopierdo==0) return casosenquepierdo/(double)casos;
	map<clave,double>::iterator it;
	clave key=make_pair(cant,make_pair(num,dentrodecuantopierdo));
	it=mapa.find(key);
	if (it!=mapa.end()) return (*it).second;
	int casosenquemejoro=(num-1)*(num-2)/2;
	int casosenquesigoigual=casos-casosenquemejoro-casosenquepierdo;
	double resp=0;
	if (casosenquemejoro!=0) resp+=casosenquemejoro*calcular(cant-1,num-1,dentrodecuantopierdo-1);
	if (casosenquesigoigual!=0) resp+=(casosenquesigoigual)*calcular(cant-1,num,dentrodecuantopierdo-1);
	resp/=casos;
	mapa.insert(make_pair(key,resp));
	return resp;
}
