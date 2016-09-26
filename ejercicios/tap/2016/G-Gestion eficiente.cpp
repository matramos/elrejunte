#include <iostream>
#include <vector>
using namespace std;

typedef pair<int,int> conexion;
vector<conexion> *grafo;
int calcular (int estacion,int acumulado,int previa);

int main()
{
	ios_base::sync_with_stdio(false);
	int n,a,b,c;
	cin >> n;
	grafo=new vector<conexion>[n];
	for (int i=0;i<n-1;i++)
	{
		cin >> a >> b >> c;
		grafo[a-1].push_back(make_pair(b-1,c));
		grafo[b-1].push_back(make_pair(a-1,c));
	}
	for (int i=0;i<n;i++) cout << calcular(i,0,-1) << "\n";
	return 0;
}

int calcular (int estacion,int acumulado,int previa)
{
	if (previa!=-1 && grafo[estacion].size()==1) return acumulado;
	int max=acumulado,aux;
	for (int i=0;i<grafo[estacion].size();i++)
	{
		if (grafo[estacion][i].first!=previa)
		{
			aux=calcular(grafo[estacion][i].first,acumulado^grafo[estacion][i].second,estacion);
			if (aux>max) max=aux;
		}
	}
	return max;
}
