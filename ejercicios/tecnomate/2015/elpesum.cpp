//TecnoMate 2015

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;


int suma(vector<int> &secuencia){
	int resultado = 0;
	
	for(int i=1;i<secuencia.size();i++) { 
		resultado += abs(secuencia[i]-secuencia[i-1]);
	}
	
	return resultado;
}

int main(int argc, char *argv[]) {
	
	int N;
	int cant;
	int aux;
	int max;
	vector<int> secuencia, mitad1, mitad2, lista;
	
	cin>>N;
	
	for(int i=0;i<N;i++) {
		
		secuencia.clear();
		mitad1.clear();
		mitad2.clear();
		lista.clear();
		
		cin>>cant;
		max = 0;
		
		for(int i=0;i<cant;i++) { 
			cin>>aux;
			secuencia.push_back(aux);
		}
		
		sort(secuencia.begin(), secuencia.end());
		
		if(secuencia.size() %2 == 0){
		
			for(int j=0;j<secuencia.size()/2;j++) { 
				mitad1.push_back(secuencia[j]);
			}
			
			for(int j= secuencia.size()/2; j<secuencia.size();j++) { 
				mitad2.push_back(secuencia[j]);
			}
			
			int j = 0;
			
			while(j+1 <= mitad1.size() && j+1 <= mitad2.size()){
				lista.push_back(mitad2[j]);
				lista.push_back(mitad1[j]);
				j++;
			};
			
			if(mitad1.size() > mitad2.size()){
				lista.push_back(mitad2[j]);
			}
			
			cout<<"Case "<<i+1<<": "<<suma(lista)<<endl;
		
		}
		else{
			
			max = suma(secuencia);
			
			while(next_permutation(secuencia.begin(), secuencia.end())){
				aux = suma(secuencia);
				if(max < aux){
					max  = aux;
				}
			}
			
			cout<<"Case "<<i+1<<": "<<max<<endl;
			
		}
		
	}
	
	return 0;
}


