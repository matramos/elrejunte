#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector <string> mapa;

bool sorround(int i, int j){
	bool flag=false;
	if (j>0) {if (mapa[i][j-1]=='T') flag=true;}
	if (j<(mapa[i].size()-1)) if (mapa[i][j+1]=='T') flag=true;
	if (i>0) if(mapa[i-1][j]=='T') flag=true;
	if (i<(mapa.size()-1)) if (mapa[i+1][j]=='T') flag=true;
	return flag;
}

int main(int argc, char *argv[]) {
	
	string aux;
	int lines, colum;
	bool change;
	
	cin>>lines>>colum;
	while(lines != 0){
		
		for(int i=0;i<lines;i++) { 
			cin>>aux;
			mapa.push_back(aux);
		};
		
		change=true;
		while(change){
			change=false;
			for(int i=0;i<lines;i++) { 
				for(int j=0;j<colum;j++) { 
					if(mapa[i][j]=='A' && sorround(i,j)){
						mapa[i][j]='T';
						change=true;
					}
				}
			}
		}
			
		for(int i=0;i<lines;i++) { 
			cout<<mapa[i]<<endl;
		}
		cout<<endl;
		mapa.clear();
		cin>>lines>>colum;
	}
	return 0;
}

