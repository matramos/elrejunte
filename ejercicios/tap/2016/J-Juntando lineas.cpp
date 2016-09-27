#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	vector<int> anchos;
	bool perdio;
	int n,l,c,tl;
	while (cin >> n >> l >> c)
	{
		tl=n;
		anchos.resize(n);
		for (int i=0;i<n;i++) cin >> anchos[i];
		sort(anchos.begin(),anchos.end());
		perdio=false;
		while (!perdio && tl>0)
		{
			if (anchos[tl-1]>c) perdio=true;
			else
			{
				c-=anchos[tl-1];
				tl-=l;
			}
		}
		anchos.clear();
		if (perdio) cout << "N\n";
		else cout << "S\n";
	}
	return 0;
}

