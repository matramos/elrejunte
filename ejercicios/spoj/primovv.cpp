//  http://www.spoj.com/problems/PRIMOVV/
// ACC

#include <iostream>
#include <vector>
using namespace std;

#define MAX 10

vector<int> data;

vector<int> primos;

/*
* Bandera de parada del backtracking.
* Inicialmente en false.
*/ bool first_solution;

// c < d ?
// A a true
// A b true
// A A false
// a A false
// b A false

void generar_primos(){
	primos.push_back(2)
	for(i=3; i<100; i++){
		if(isprimo(i) primos.push_back(i);
	}
}

bool isprimo (int n){
	bool salida = true;
	for(int i=2; i<n; i++){
		if (n/i == 0){
			salida = false;
		}
	}
	
	return salida;
}
bool compare (char c, char d) {
	if (c == d) return false;
	if (toupper(c) == toupper(d)) return c < d;
	
	return toupper(c) < toupper(d);
}


bool is_solution(){
	//si corresponde hacer: first_solution = true;
	return false;
}

void process_solution(){
	cout << "solucion..." << endl;
}

void get_candidates(vector<int> &candidates){
	
}

void backtracking(){
	if(is_solution()){
		process_solution();
	}else{
		if(first_solution) return;
		
		vector<int> candidates;
		
		get_candidates(candidates);
		
		for(unsigned i = 0; i < candidates.size(); i++){
			data.push_back(candidates[i]);
			backtracking();
			data.pop_back();
		}
	}
}

int main(){
	int n;
	
	//cin >> n;
	generar_primos();
	for(int i = 0; i< primos.size(); 
	/*while(n!=0){
		backtracking(n);
		cout<<soluciones<<endl;
		data.clear();
		cin >> n;
	}*/
	
	
	// USAR: data.push_back()
	// para cada caso de prueba usar data.clear() y first_solution = false
	return 0;
}
