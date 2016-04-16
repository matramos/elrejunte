//  http://www.spoj.com/problems/SALTOS/
//  ACC

#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

#define MAX 10

vector<int> data;
int soluciones;

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


bool is_solution(int n){
	if(data.size() == n){
		return true;
	}
	//si corresponde hacer: first_solution = true;
	else{
		return false;
	}
}

void process_solution(){
	soluciones++;
	//cout << "solucion..." << endl;
}

void get_candidates(vector<int> &candidates, int n){
	vector <bool> cands (n+1,true);
	vector <bool> diferencias (n, true);
	cands[0]= false;
	diferencias[0]= false;
	
	bool first = (data.size() == 0) ? true : false;
	
	for (int i=0; i < data.size(); i++){
		cands[data[i]]=false;
	}
	
	
	
	if (!first){
		for (int i = 0; i < (data.size()-1); i++){
			int dif = abs(data[i] - data[i+1]);
			diferencias[dif]=false;
		}
		
		int last = data.back();
		
		for(int i=1; i<cands.size(); i++){
			int dif = abs(i-last);
			
			
			if (!(diferencias[dif])){
				cands[i] = false;
			}
		}
		
	}
		
	for(int i=0;i<cands.size();i++){
		if(cands.at(i)==true)
			candidates.push_back(i);
	}
	
		
}

void backtracking(int n){
	if(is_solution(n)){
		process_solution();
	}else{
		//if(first_solution) return;
		
		vector<int> candidates;
		
		get_candidates(candidates, n);
		
		for(unsigned i = 0; i < candidates.size(); i++){
			data.push_back(candidates[i]);
			backtracking(n);
			data.pop_back();
		}
	}
}

int main(){
	int n;
	
	cin >> n;
	
	while(n!=0){
		soluciones = 0;
		backtracking(n);
		cout<<soluciones<<endl;
		data.clear();
		cin >> n;
	}
	
	
	// USAR: data.push_back()
	// para cada caso de prueba usar data.clear() y first_solution = false
	return 0;
}
