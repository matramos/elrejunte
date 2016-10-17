#include <iostream>
using namespace std;
struct M22{
    int64_t a,b,c,d;
    M22 operator*(const M22 &p) const {
        return (M22) {a*p.a+b*p.c,a*p.b+b*p.d,c*p.a+d*p.c,c*p.b+d*p.d};
    }
};

M22 operator^(const M22 &p, int64_t n){
    if(!n) return (M22){1,0,0,1};
    M22 q = p^(n/2); q=q*q;
    return n%2?p*q:q;
}

int64_t f0 = 0, f1;


int64_t fibo(int64_t n){
    M22 mat = (M22){0,1,1,1}^n;
    return mat.a*f0+mat.b*f1;
}


 int main(){
    int t;
    
    int64_t w;
    cin >> t;
    while(t--){
        cin >> w>>f1; 
        int64_t f = fibo(0);
        int64_t i=0;
        while(f<w){
            f=fibo(++i);
            //cout << i<< " f: "<< f << endl;
        }
        i+=2;
        cout << (i/2) + (i%2) << endl;
    }
    

    return 0;
 }
