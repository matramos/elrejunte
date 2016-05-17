#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void binario(long long N, vector<int> &bin){
	while(N != 0){
		bin.push_back(N%2);
		N = N/2;
	}
	
}

unsigned long long entero(vector<int> &bin){
	unsigned long long resultado = 0;
	for(int i=bin.size()-1; i >= 0; i--) { 
		resultado = resultado * 2 + bin[i];
		
	}
	
	return resultado;
}

int mayoror(int a, int b){
	return a>b? a : b;
}

int main(int argc, char *argv[]) {
	unsigned long long N;
	int K;
	int a, b, mayor, aux;
	unsigned long long maximo, minimo, temp;
	vector<int> bin;
	
	cin>>N>>K;
	
	while(N != 0 || K != 0){
	
		bin.clear();
		
	minimo = maximo = N;
	
	binario(N, bin);
	
	for(int i=0;i<K;i++) { 
		
		cin>>a>>b;
		
		mayor = mayoror(a, b);
		
		while(bin.size() < mayor+1){
			bin.push_back(0);
		}
		
		aux = bin[a];
		bin[a] = bin[b];
		bin[b] = aux;
		
		temp = entero(bin);
		
		if(maximo < temp){
			maximo = temp;
		}
		if(minimo > temp){
			minimo = temp;
		}
		
	}
	
	cout<<temp<<" "<<maximo<<" "<<minimo<<endl;
	
	cin>>N>>K;
}
	
	
	return 0;
}

