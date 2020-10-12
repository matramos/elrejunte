struct Line{tipo m,h;};
//Coordenada X de la interseccion
tipo inter(Line a, Line b){
    tipo x=b.h-a.h, y=a.m-b.m;
    return x/y+(x%y?!((x>0)^(y>0)):0);//==ceil(x/y)
}
struct CHT {
	vector<Line> c;
	bool mx;
	int pos;
	CHT(bool mx=0):mx(mx),pos(0){}//mx=1 si las query devuelven el max
	//Indexar de der a izq si se inserto con m/-m creciente (min/max)
	inline Line acc(int i){return c[c[0].m>c.back().m? i : sz(c)-1-i];}
	inline bool irre(Line x, Line y, Line z){
		return c[0].m>z.m? inter(y, z) <= inter(x, y)
                         : inter(y, z) >= inter(x, y);
	}
	void add(tipo m, tipo h) {//O(1), los m tienen que entrar ordenados
        if(mx) m*=-1, h*=-1; //max f_i(x) == min -f_i(x)
		Line l=(Line){m, h};
		//Manejar caso igual pendiente
        if(sz(c) && m==c.back().m) { l.h=min(h, c.back().h), c.pop_back(); if(pos) pos--; }
        while(sz(c)>=2 && irre(c[sz(c)-2], c[sz(c)-1], l)) { c.pop_back(); if(pos) pos--; }
        c.pb(l);
	}
	inline bool fbin(tipo x, int m) {return inter(acc(m), acc(m+1))>x;}
	tipo eval(tipo x){
		int n = sz(c);
		//query con x no ordenados O(lgn)
		int a=-1, b=n-1;
		while(b-a>1) { int m = (a+b)/2;
			if(fbin(x, m)) b=m;
			else a=m;
		}
		return (acc(b).m*x+acc(b).h)*(mx?-1:1);
        //query O(1), con x ordenado
		while(pos>0 && fbin(x, pos-1)) pos--;
		while(pos<n-1 && !fbin(x, pos)) pos++;
		return (acc(pos).m*x+acc(pos).h)*(mx?-1:1);
	}
} ch;
