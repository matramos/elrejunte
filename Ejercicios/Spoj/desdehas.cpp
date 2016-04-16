// http://www.spoj.com/problems/DESDEHAS/
// ACC


#include <iostream>
#include <string>
#include <vector>

using namespace std;

main (){

	string entrada;
	vector <string> texto;

	int columnas, filas;

	cin >> columnas;

	while (columnas!=0){
		cin >> entrada;

		filas = entrada.length() / columnas;

		texto.resize(filas);

		for (int i = 0; i < filas; i++){
			if (i%2 != 0){
				for(int j = (columnas * (i+1) - 1 ); j >= (columnas * (i+1) - columnas); j--){
					texto[i].push_back(entrada[j]);
				}
			}
			else{
				for(int j = columnas * i; j < (columnas * i + columnas); j++){
				texto[i].push_back(entrada[j]);
				}
			}
		}

		for (int i = 0; i < columnas; i++){
			for(int j = 0; j < filas; j++){
				cout << texto[j][i];
			}
		}

		cout << endl;

		texto.clear();

		cin >> columnas;
	}

}