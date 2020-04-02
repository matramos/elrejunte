//Dado un arreglo y una operacion asociativa con neutro
#define operacion(x,y) ((x)+(y))
const Elem neutro=0; const Alt neutro2=0;
#define MAXN 100010//Cambiar segun el N del problema
struct RMQ{
	int sz;
	Elem t[4*MAXN];
	Alt dirty[4*MAXN];//las alteraciones pueden ser de tipo distinto a Elem
	Elem &operator[](int p) {return t[sz+p];}
	void init(int n){//O(nlgn)
		sz = 1 << (32-__builtin_clz(n));
		forn(i, 2*sz) t[i] = neutro;
		forn(i, 2*sz) dirty[i] = neutro2;
	}
	void push(int n, int a, int b) {//propaga el dirty a sus hijos
		if(dirty[n] != neutro2) {// n = node of range [a,b)
			t[n] += dirty[n]*(b-a);//altera el nodo, modificar segun el problema
			if(n<sz){
				dirty[2*n] += dirty[n];
				dirty[2*n+1] += dirty[n];
			}
			dirty[n] = neutro2;
		}
	}
	Elem get(int i, int j, int n, int a, int b) {//O(lgn)
		if(j<=a || i>=b) return neutro;
		push(n, a, b);//corrige el valor antes de usarlo
		if(i<=a && b<=j) return t[n];//n = node of range [a,b)
		int c = (a+b)/2;
		return operacion(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	Elem get(int i, int j) {return get(i,j,1,0,sz);}
	//altera los valores en [i, j) con una alteracion de val
	void alterar(Alt val, int i, int j, int n, int a, int b) {//O(lgn)
		push(n, a, b);
		if(j<=a || i>=b) return;
		if(i<=a && b<=j){
			dirty[n] += val; // modificar segun el problema
			push(n, a, b);
			return;
		}
		int c = (a+b)/2;
		alterar(val, i, j, 2*n, a, c), alterar(val, i, j, 2*n+1, c, b);
		t[n] = operacion(t[2*n], t[2*n+1]);//por esto es el push de arriba
	}
	void alterar(Alt val, int i, int j){alterar(val,i,j,1,0,sz);}
};//Use: definir operacion, neutros, Alt, Elem, uso de dirty, MAXN
//cin >> n; rmq.init(n);