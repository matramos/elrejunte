#include <iostream>
#include <vector>

using namespace std;

int main(){
	vector<vector<int> > ocurrencias;
	int tam, quer;
	

	while(cin>>tam>>quer){

		ocurrencias.resize(1000000);

		int num;
		for (int i = 1; i <= tam; i++)
		{
			cin>>num;
			ocurrencias[num].push_back(i);
		}

		int ocur;
		for (int i = 0; i < quer; ++i)
		{
			cin>>ocur>>num;

			if(ocurrencias[num].size() < ocur) cout<<0<<endl;
			else cout<<ocurrencias[num][ocur-1]<<endl;
		}

		ocurrencias.clear();
	}
	return 0;
	
}