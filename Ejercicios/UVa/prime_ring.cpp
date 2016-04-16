// http://uva.onlinejudge.org/external/5/524.html
// ACC

#include <iostream>
#include <vector>
using namespace std;

#define MAX 10

vector<unsigned> data;

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


bool is_solution(unsigned n){
	if(data.size() == n){
		return true;
	}
	//si corresponde hacer: first_solution = true;
	else{
		return false;
	}
}

void process_solution(){
	for(unsigned i=0;i<data.size();i++){
		cout << data[i] << " ";
	}
	cout << endl;
}

bool is_primo(unsigned i){
	return (3==i || 5==i || 7==i || 11==i || 13==i || 17==i ||19==i || 23==i || 29==i || 31==i);
}
void get_candidates(vector<int> &candidates, unsigned n){
	
	vector <bool> cands (n+1,true);
	cands[0]=false;
	unsigned last=data.back();
	
	bool first = (data.size() + 1 == n)? true: false;
	
	for(unsigned i=0; i<data.size();i++){
		cands[data[i]]=false;
	}
	
	for(unsigned i=2; i<cands.size(); i++){
		if(!is_primo(last + i)){
			cands[i] = false;
		}
		if(first){
			if(!is_primo(i + 1)){
				cands[i] = false;
			}
		}
	}
	for(unsigned i=0;i<cands.size();i++){
		if(cands.at(i)==true)
			candidates.push_back(i);
	}
	
}

void backtracking(unsigned n){
	if(is_solution(n)){
		process_solution();
	}
	else{
		//if(first_solution) return;
			
		vector<int> candidates;

		get_candidates(candidates,n);
		
		for(unsigned i = 0; i < candidates.size(); i++){
			data.push_back(candidates[i]);
			backtracking(n);
			data.pop_back();
		}
	}
}

int main(){
	unsigned n;

	while(cin >> n){
		data.push_back(1);
		backtracking(n);
		data.clear();
	}
	/*for (unsigned i=0; i<n; i++) {
		cin >> l;
	}*/

	
	// USAR: data.push_back()
	// para cada caso de prueba usar data.clear() y first_solution = false
	return 0;
}
