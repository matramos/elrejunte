//http://www.spoj.com/problems/VARYINGFOCUS/

#include <iostream>
//#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

bool menor(pair<int,int> a, pair<int,int> b){
	return a.first < b.first;
}

int main(int argc, char *argv[]) {
	int N;
	int limite;
	int ultimo;
	int fotos;
	int aux1, aux2;
	
	vector<pair<int,int> > intervalos;
	while(cin>>N){
		
		intervalos.clear();
		
		//leo los intervalos
		for(int i=0;i<N;i++) { 
			cin>>aux1>>aux2;
			intervalos.push_back(make_pair(aux1,aux2));
		}
		
		//ordeno los intervalos
		sort(intervalos.begin(), intervalos.end(), menor);
		
		//inicializo las variables
		limite = intervalos[0].second;	//el limite comienza siendo el final del primer intervalo
		ultimo = 0;	//ultimo intervalo procesado
		fotos = 1;	//cantidad de fotos
		
		//mientras no se hayan procesado todos los intervalos
		while(ultimo < intervalos.size()-1){
			
			//si el siguiente intervalo comienza antes del limite (va en la misma foto que el anterior)
			if(intervalos[ultimo+1].first <= limite){
				
				//si el siguiente intervalo además termina antes del limite
				if(intervalos[ultimo+1].second < limite){
					
					//el nuevo limite es el final de ese intervalo
					limite = intervalos[ultimo+1].second;
				}
			}
			//pero si el siguiente intervalo comienza despues del limite
			else{
				
				//se necesitará sacar otra foto
				fotos++;
				
				//el nuevo limite será el final de este intervalo
				limite = intervalos[ultimo+1].second;
			}
			
			//marcamos el intervalo como procesado
			ultimo++;
		}
		
		//mostramos la cantidad de fotos sacadas
		cout<<fotos<<endl;
		
	}
	return 0;
}

