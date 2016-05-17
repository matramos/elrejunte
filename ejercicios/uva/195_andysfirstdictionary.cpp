// http://uva.onlinejudge.org/external/1/195.html
//  ACC

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char *argv[]) {
	string temporal;
	set <string> diccionario;
	
	while(cin >> temporal){
		unsigned int i;
		string temporal2 = "";
		string temporal3 = "";
		transform(temporal.begin(), temporal.end(),temporal.begin(),::tolower);
		
		for (i =0; i<temporal.length();i++){
			if (isalpha(temporal[i]))
				temporal2 += temporal[i];
			else if (temporal.length()-i>0)
			{
				diccionario.insert(temporal2);
				temporal2="";
			}
		}
		
		diccionario.insert(temporal2);
	}
	set<string>::iterator iter;
	
	for(iter=(diccionario.begin());iter!=diccionario.end();iter++){
		if (iter != diccionario.begin())
			cout << (*iter) << endl;
	}
	return 0;
}

