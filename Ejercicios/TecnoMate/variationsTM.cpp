#include <iostream>
#include <vector>
using namespace std;

int contador;

string palabra;

vector<char> data;

bool is_solution(){
	return data.size() == palabra.size();
}


void get_candidates(vector<char> &candidates){
	int posicion = data.size();
	
	candidates.push_back(tolower(palabra[posicion]));
	candidates.push_back(toupper(palabra[posicion]));
	
	switch(tolower(palabra[posicion])){
	case 'a': {candidates.push_back('4');
	break;}
	case 'e': {candidates.push_back('3');
	break;}
	case 'i': {candidates.push_back('1');
	break;}
	case 'o': {candidates.push_back('0');
	break;}
	case 's': {candidates.push_back('5');
	break;}
	}

}

void process_solution(){
	contador++;
}

void backtracking(){
	if(is_solution()){
		process_solution();
	}
	else
	{
		vector<char> candidates;
		
		get_candidates(candidates);
		
		for(int i=0;i<candidates.size();i++) { 
			data.push_back(candidates[i]);
			backtracking();
			data.pop_back();
		}
	}
}


int main(int argc, char *argv[]) {
	int T;
	
	cin>>T;
	
	for(int i=0;i<T;i++) { 
		
		cin>>palabra;
		contador = 0;
		
		backtracking();
		
		cout<<contador<<endl;
		
	}
	return 0;
}
