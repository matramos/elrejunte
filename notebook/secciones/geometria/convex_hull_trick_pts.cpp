struct pto{
	tipo x,y;
	pto operator-(pto a){return {x-a.x, y-a.y};}
	//dot product, producto interno:
	tipo operator*(pto a){return x*a.x+y*a.y;}
	//module of the cross product or vectorial product:
	//if a is less than 180 clockwise from b, a^b>0
	tipo operator^(pto a){return x*a.y-y*a.x;}
	//returns true if this is at the left side of line qr
	bool left(pto &q, pto &r){return ((q-*this)^(r-*this))>0;}
};
typedef pto vec;
struct CHT{
	deque<pto> c;
	bool mn;
	int pos;
	CHT(bool mn=0):mn(mn),pos(0){}//mn=1 si querys de min
	void add(tipo m, tipo h) {//O(1)
		//Querys max f_i, necesitamos capsula inferior
		if(mn) m*=-1, h*=-1; //min f_i(x) == max -f_i(x)
		pto p = {-m,-h}; //Line(m,h) == pto(-m,-h)
		if(c.empty()) {c.pb(p); return;}
		//el nuevo m tiene que ser el menor o el mayor (m "ordenados")
		assert(p.x <= c[0].x || p.x >= c.back().x);
		if(p.x <= c[0].x) {
			if(p.x == c[0].x) p.y = min(p.y, c[0].y), c.pop_front(), pos--;
			while(c.size() > 1 && !c[1].left(p, c[0])) c.pop_front(), pos--;
			c.push_front(p);
		}
		else {
			if(p.x == c.back().x) p.y = min(p.y, c.back().y), c.pop_back();
			while(c.size() > 1 && !p.left(c[sz(c)-2], c[sz(c)-1])) c.pop_back();
			c.pb(p);
		}
		pos = min(max(0,pos), sz(c)-1);
	}
	tipo eval(tipo x){ //max f_i(x) == max p_i*(-x,-1) (dot prod)
		vec vx = {-x,-1};
		//querys O(log), para x desordenado
		int L = 0,R = sz(c)-1, M;
		while(L < R) {
			M = (L+R)/2;
			if(c[M+1]*vx > c[M]*vx) L = M+1;
			else R = M;
		}
		return c[L]*vx*(mn?-1:1);
		//querys O(1), para x "ordenados"
		while(pos > 0 && c[pos-1]*vx > c[pos]*vx) pos--;
		while(pos < sz(c)-1 && c[pos+1]*vx > c[pos]*vx) pos++;
		return c[pos]*vx*(mn?-1:1);
	}
};
