int sgn(T x){return x<0? -1 : !!x;}
struct line{
	T a,b,c; // Ax+By=C
	line() {}
	line(T a_, T b_, T c_):a(a_),b(b_),c(c_){}
	// TO DO: check negative C (multiply everything by -1)
	line(pto u, pto v): a(v.y-u.y), b(u.x-v.x), c(a*u.x+b*u.y) {}
	int side(pto v){return sgn(a*v.x + b*v.y - c);}
	bool inside(pto v){ return abs(a*v.x + b*v.y - c) <= EPS; }
	bool parallel(line v){return abs(a*v.b-v.a*b) <= EPS;}
	pto inter(line v){
		T det=a*v.b-v.a*b;
		if(abs(det)<=EPS) return pto(INF, INF);
		return pto(v.b*c-b*v.c, a*v.c-v.a*c)/det;
	}
};
