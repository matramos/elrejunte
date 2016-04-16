//http://www.spoj.com/problems/ONP/
//  ACC


#include <iostream>
#include <stack>
#include <string.h>

using namespace std;

int main (){
	
	int cantidad;
	char expression[400];
	stack <char> S;

	cin>>cantidad;

	for (int i = 1; i <= cantidad; i++)
	{
		int ca=1; //parentesis abiertos
		int j=1;

		cin >> expression;
		while(ca!=0){
			if (expression[j] == '(') ca++;
			else
				if((expression[j] >= 'a') && (expression[j] <= 'z'))
					cout << expression[j];
				else
					if (expression[j] == ')'){
						cout << S.top();
						S.pop();
						ca--;
					}
					else //es un operador
						S.push(expression[j]);
			j++;
		}

		while (S.size() != 0){
			cout << S.top();
			S.pop();
		}
		cout << endl;
	}

	return 0;
}