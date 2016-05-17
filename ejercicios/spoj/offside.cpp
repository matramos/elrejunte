//  http://www.spoj.com/problems/OFFSIDE/
//  ACC

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int a,d;
	int temporal, contador=0;
	int att;
	vector <int> atacantes;
	vector <int> defensores;
	
	cin >> a >> d;
	while ((a != 0) && (d !=0)){
		for (int i =0; i<a; i++){
			cin >> temporal ;
			if(i==0)att=temporal;
			else if (temporal < att){
				att = temporal;
			}
		}
		
		for (int i =0; i<d; i++){
			cin >> temporal ;
			if( temporal <= att) contador++;
		}
		
		if (contador >= 2){
			cout << "N" << endl;
		}
		else{
			cout << "Y" << endl;
		}
		
		cin >> a >> d;
		contador = 0;
	}
	
	return 0;
}

