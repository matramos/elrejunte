#include <iostream>
#include <string>

using namespace std;

string pancakes;

int minFlip(string p){
	int cuenta = 1;
	if(p.size() == 1){
		if(p[0]=='+') return 0;
		else return 1;
	}
	else{
		for (unsigned int i = 0; i < p.size(); ++i)
		{
			if ((p[i]=='+' && p[i+1]=='-') || 
				(p[i]=='-' && p[i+1]=='+'))
				cuenta++;
		}
		if(p[p.size()-1] == '-') return cuenta;
		else return cuenta-1;
	}

}

int main(){
	int n;

	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> pancakes;

		cout << "Case #" << i << ": "<< minFlip(pancakes) << endl;
	}


	return 0;
}