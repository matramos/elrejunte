#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > map;
vector<vector<bool> > visitada;

void visitar(int f, int c, int i, int j){
	int h=map[i][j];
	visitada[i][j]=1;
	
	if((i>0)&&(h==map[i-1][j])&&(!visitada[i-1][j])) visitar(f,c,i-1,j);
	if((i<f-1)&&(h==map[i+1][j])&&(!visitada[i+1][j])) visitar(f,c,i+1,j);
	if((j>0)&&(h==map[i][j-1])&&(!visitada[i][j-1])) visitar(f,c,i,j-1);
	if((j<c-1)&&(h==map[i][j+1])&&(!visitada[i][j+1])) visitar(f,c,i,j+1);
	
}
int superior(int f, int c){
	int caras=0;
	
	for(int i=0;i<f;i++) { 
		for(int j=0;j<c;j++) { 
			if(visitada[i][j]==0){
				caras++;
				visitar(f,c,i,j);
			}
		}
	}
	return caras;
}
int norte(int f, int c){
	int caras=0;
	
	for(int i=0;i<f-1;i++) { 
		for(int j=0;j<c;j++) { 
			
			//Existe cara mirando hacia el norte
			if(map[i][j]<map[i+1][j]){
				caras++;
				j++;
				//No contarla si es la misma cara
				while((j<c)&&(map[i][j]<map[i+1][j])){
					if((map[i][j-1]>=map[i+1][j])||(map[i+1][j-1]<=map[i][j])){
						j--;
						break;
					}
					j++;
				}
			}
		}
	}
	
	return caras;
}
int sur(int f, int c){
	int caras=0;
	
	for(int i=0;i<f-1;i++) { 
		for(int j=0;j<c;j++) { 
			
			if(map[i][j]>map[i+1][j]){
				caras++;
				j++;
				while((j<c)&&(map[i][j]>map[i+1][j])){
					if((map[i][j-1]<=map[i+1][j])||(map[i+1][j-1]>=map[i][j])){
						j--;
						break;
					}
					j++;
				}
			}
		}
	}
	
	return caras;
}

int oeste(int f, int c){
	int caras=0;
	
	for(int j=0;j<c-1;j++) { 
		for(int i=0;i<f;i++) { 
			
			if(map[i][j]<map[i][j+1]){
				caras++;
				i++;
				while((i<f)&&(map[i][j]<map[i][j+1])){
					if((map[i][j]>=map[i-1][j+1])||(map[i-1][j]>=map[i][j+1])){
						i--;
						break;
					}
					i++;
				}
			}
		}
	}
	
	return caras;
}
int este(int f, int c){
	int caras=0;
	
	for(int j=0;j<c-1;j++) { 
		for(int i=0;i<f;i++) { 
			
			if(map[i][j]>map[i][j+1]){
				caras++;
				i++;
				while((i<f)&&(map[i][j]>map[i][j+1])){
					if((map[i][j]<=map[i-1][j+1])||(map[i-1][j]<=map[i][j+1])){
						i--;
						break;
					}
					i++;
				}
			}
		}
	}
	
	return caras;
}

int main(int argc, char *argv[]) {

	int f, c;
	
	while(cin>>f>>c){
		map.assign(f,vector<int>(c,0));
		visitada.assign(f,vector<bool>(c,0));
		for(int i=0;i<f;i++) { 
			for(int j=0;j<c;j++) { 
				cin>>map[i][j];
			}
		}
		
		cout<<norte(f,c)+oeste(f,c)+sur(f,c)+este(f,c)+superior(f,c)+5<<endl;
	}
	return 0;
}

