// http://www.spoj.com/problems/ANAG/
//  ACC

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define MAX 10

vector<char> data;
unsigned tam_entrada;
map<char,unsigned> mapa;
string entrada;
	
void process_solution() {
	for(int i=0; i<data.size(); i++){
		cout << data.at(i);
	}
	cout << "\n";
}
 
bool is_solution(unsigned n){
	 if(tam_entrada==n)return true;
	 else return false;
}

void get_candidates(vector<char> &candidates);

void backtracking(string entrada){
	
	if(is_solution(data.size())){
		process_solution();
	}
	else{
		vector<char> candidates;
		get_candidates(candidates);
		for(unsigned i = 0; i < candidates.size(); i++){
			data.push_back(candidates[i]);
			mapa[candidates[i]]--;
			backtracking(entrada);
			data.pop_back();
			mapa[candidates[i]]++;
		}
	}
}

void get_candidates(vector<char> &candidates){
	
	for(map<char,unsigned>:: iterator it=mapa.begin(); it!=mapa.end(); it++){
		if(it->second>0){
			candidates.push_back(it->first);
		}
	}
}

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

int main () {
	unsigned n_cases;

	cin >> n_cases;

	for (unsigned i=0; i<n_cases; i++) {
		cin >> entrada;
		cout << endl;
		sort(entrada.begin(),entrada.end(),compare);
		tam_entrada=entrada.size();
		for(int i=0;i<entrada.size();i++){
			mapa[entrada.at(i)]++;
		}
		backtracking(entrada);
		cout << endl;
		data.clear();
		mapa.clear();
	}
}
