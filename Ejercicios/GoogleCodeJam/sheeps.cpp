#include <iostream>
#include <vector>

using namespace std;

vector <bool> digitos;

void verDigitos (long unsigned int num){

	if (num / 10 == 0) {
		if(!digitos[num]) digitos[num]=true;
	}
	else{
		if(!digitos[num%10]) digitos[num%10]=true;
		verDigitos(num/10);
	}
}

bool chequearDigitos(void){
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		if(digitos[i]) count++;
		else break;
	}
	if (count == 10) return true;
	else return false;
}

int main(){
	int t;
	long unsigned int n;

	cin >> t;
	for (int i = 0; i < t; i++)
	{
		digitos.clear();
		digitos.assign(10, false);
		int j = 1;

		cin >> n;
		
		if (n != 0){
			verDigitos(n);
			while(!chequearDigitos()){
				j++;
				verDigitos(n * j);
			}

			cout << "Case #" << i+1 << ": " << n * j << endl;
		}
		else{
			cout << "Case #" << i+1 << ": INSOMNIA" << endl;
		}
	}

	return 0;
}
	