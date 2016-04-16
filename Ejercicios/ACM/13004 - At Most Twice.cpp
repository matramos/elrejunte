#include <iostream>
#include <cstring>
using namespace std;

int digitos[]={0,0,0,0,0,0,0,0,0,0};
char a[18];
int i=0;
int cifras=0;
int b[100];
long long int numero=0;

long long power(int base, int exp){
	long long result=1;
	for(int i=0;i<exp;i++){
		result=result*base;
	}
	return result;
}

int pos_ult_cero(int pos_actual){
	pos_actual--;
	int digito=b[pos_actual];
	while(digito==0){
		pos_actual--;
		digitos[0]--;
		digito=b[pos_actual];
	}
	return pos_actual;
}

int prox_dig(int dig_actual){
	
	while((digitos[dig_actual]==2) && (dig_actual>0)){
		dig_actual--;
	}
	return dig_actual;
}

void rellenar(int pos_actual){
	int i=9;
	int digitos_aux[10];
	
	for(int k=0;k<10;k++){
		digitos_aux[k]=digitos[k];
	}
	
	if((b[pos_actual]==0) && (pos_actual==0)) cifras--;
	else
		pos_actual++;
	
	while(pos_actual<=cifras){
		if(digitos_aux[i]==2) i--;
		else{
			b[pos_actual]=i;
			digitos_aux[i]++;
			pos_actual++;
			
		}
	}
}

int main(int argc, char *argv[]) {
	while(cin>>a){
		i=0;
		cifras=strlen(a);
		int aux;
		while(i<=cifras){
			aux=(int)a[i];
			b[i]=aux-'0';
			i++;
		}
		
		i=0;
		int terminar=0;
		
		while(i<cifras){
			
			if(digitos[b[i]]<2) {
				digitos[b[i]]++;
				if(terminar==1) {
					rellenar(i);
					i=cifras;
				}
				else
					i++;
			}
			else{
				if(b[i]!=0){
					b[i]--;
					rellenar(i);
					
				}
				else{
					int j=pos_ult_cero(i);
					digitos[b[j]]--;
					b[j]--;
					terminar=1;
					i=j;
				}
			}
		}
		numero=0;
		for(i=cifras-1;i>=0;i--){
			numero=numero+b[i]*power(10,cifras-i-1);
		}
		cout<<numero<<endl;
		
		for(int i=0;i<10;i++) { 
			digitos[i]=0;
		}
		
	}
	return 0;
}
