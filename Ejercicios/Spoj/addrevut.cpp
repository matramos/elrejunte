// http://www.spoj.com/problems/ADDREVUT/
//  ACC

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

bool is_palindro (string N){
	if (N.length() == 1)
		return true;
	else if(N.length()==2){
		if (N[0] == N[1])
			return true;
		else
			return false;
	}
	else{
		if (N[0]==N[N.length()-1]){
			return is_palindro(N.substr(1,N.length()-2));
		}
		else
			return false;
	}
}

string suma_esp (string N){
	string salida, reversa;
	stringstream ss;
	int N_int=0, reversa_int=0, salida_int;

	for (int i = N.length()-1; i>=0; i--){
		reversa.push_back(N[i]);
		reversa_int += pow(10, i) * (N[i] - '0');
	}

	//N a entero
	for(int i = 0; i < N.length(); i++){
		N_int += pow(10, N.length() -1 -i) * (N[i] - '0');
	}

	salida_int =  N_int + reversa_int;

	ss << salida_int;

	salida = ss.str();

	return salida;
}

main (){

	string entrada;
	int iteration, palin;

	int casos;

	cin >> casos;

	for(int c = 1; c <= casos; c++){

		cin >> entrada;
		iteration = 0;

		while(!is_palindro(entrada)){
			entrada = suma_esp (entrada);
			iteration++;
		}

		cout << iteration << " " << entrada << endl;

	}
}