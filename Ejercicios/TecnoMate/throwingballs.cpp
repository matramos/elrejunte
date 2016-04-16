#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	int v, n;
	int v2;
	bool listo;
	
	int pos;
	
	cin>>n>>v;
	
	while(n != 0 || v != 0){
		
		listo = false;
		while(v > 0 && !listo){
			
			v2 = v;
			pos = 0;
			
			while(v2 > 0 && !listo){
				for(int i=0;i<v2;i++) { 
					pos += v2;
					if(pos == n){
						cout<<"possivel"<<endl;
						listo = true;
						break;
					}
				}
				v2--;
			}
			v--;
		}
		if(v == 0){
			cout<<"impossivel"<<endl;
		}
		
		cin>>n>>v;
	}
	
	
	
	return 0;
}
