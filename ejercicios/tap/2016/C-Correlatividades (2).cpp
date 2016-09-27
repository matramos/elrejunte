#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

bitset<50000> noensistema;
vector<int> *grafo,faltan;
int resp;
bool f(int);

int main()
{
	ios_base::sync_with_stdio(false);
	int n,m,aprobada,a,b;
	while (cin >> n >> m)
	{
		resp=0;
		grafo=new vector<int>[n];
		faltan.resize(n,0);
		noensistema.reset();
		for (int i=0;i<m;i++)
		{
			cin >> a >> b;
			faltan[b-1]++;
			grafo[a-1].push_back(b-1);
		}
		for (int i=0;i<n;i++)
		{
			cin >> aprobada;
			if(!f(--aprobada)) noensistema.set(aprobada);
			cout << resp << "\n";
		}
	}
	return 0;
}

bool f(int aprobada)
{
	if (faltan[aprobada]==0)
	{
		resp++;
		for (int i=grafo[aprobada].size()-1;i>=0;i--)
		{
			faltan[grafo[aprobada][i]]--;
			if (noensistema[grafo[aprobada][i]] && f(grafo[aprobada][i])) noensistema.reset(grafo[aprobada][i]);
		}
		return true;
	}
	return false;
}
