#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

struct nodo{
    int n;
    nodo *izq;
    nodo *der;
};

int numeros[8]={7,8,2,4,3,5,6,1};
void generar(nodo *r,int nivel, int pos)
{
    if (nivel==6) {
        r->izq = r->der = NULL;
        return;
    }
    int a,b;
    a=(pos-nivel)%8; if(a<0)a+=8;
    b=(pos+nivel)%8;if(b<0)b+=8;
    
    nodo* ni = (nodo* )malloc(sizeof(nodo));
    nodo* nd = (nodo* )malloc(sizeof(nodo));
    
    r->izq=ni;
    r->der=nd;
    
    
    r->izq->n=numeros[a];
    r->der->n=numeros[b];
    
    generar(r->izq,nivel+1,a);
    generar(r->der,nivel+1,b);
    
    return;
}

int cases = 0;
int suma = 0;

void dfs(nodo* r, int x, int cam, int acum)
{
    
    if(r->der == NULL){
        if(acum + r->n == x && cam*10+r->n != suma) {++cases; suma = cam*10+r->n;}
        return;
    }
    
    dfs(r->izq, x, cam*10 + r->n, acum+ r->n);

    dfs(r->der, x, cam*10 + r->n, acum+ r->n);
}



int main()
{
    //freopen("input/H.in","r",stdin);
    //freopen("output","w",stdout);
    
    nodo *raiz;
    raiz=new nodo;
    raiz->n=7;
    generar(raiz,1,0);
    int x;
    cin >> x;
    
    dfs(raiz, x, 0, 0);

    
    if(cases==0) cout << "Impossible\n";
    else if(cases==1) cout << suma << endl;
    else cout << "Duplicated\n";
    return 0;
}
