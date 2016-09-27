#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	bool perdio,aumentando;
	int n,k,*luces;
	while (cin >> n >> k)
	{
		luces=new int[k];
		perdio=false;
		cin >> luces[0];
		aumentando=true;
		for (int i=1;i<k;i++)
		{
			cin >> luces[i];
			if (!perdio)
			{
				if (luces[i]<luces[i-1])
				{
					aumentando=false;
					if (i>1 && luces[i]==luces[i-2]) perdio=true;
				}
				if ((abs(luces[i]-luces[i-1])!=1 && abs(luces[i]-luces[i-1])!=2) || (!aumentando && luces[i]>luces[i-1])) perdio=true;
			}
		}
		if (perdio) cout << "N\n";
		else cout << "S\n";
	}
}

