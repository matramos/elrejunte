#include <iostream>
#include <vector>
using namespace std;

#define MAX 10

vector<int> data;

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
	unsigned n_cases;

	cin >> n_cases;

	for (unsigned i=0; i<n_cases; i++) {
		cin >> l;
	}
	// USAR: data.push_back()
	// para cada caso de prueba usar data.clear() y first_solution = false
	return 0;
}
