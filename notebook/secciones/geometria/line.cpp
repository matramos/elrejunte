int sgn(ll x){return x<0? -1 : !!x;}
struct line{
	line() {}
	double a,b,c;//Ax+By=C
//pto MUST store float coordinates!
	line(double a, double b, double c):a(a),b(b),c(c){}
	// TO DO chequear porque paso problema metiendo negativo el C (-(todo el calculo como esta))
	line(pto p, pto q): a(q.y-p.y), b(p.x-q.x), c(a*p.x+b*p.y) {}
	int side(pto p){return sgn(ll(a) * p.x + ll(b) * p.y - c);}
};
bool parallels(line l1, line l2){return abs(l1.a*l2.b-l2.a*l1.b)<EPS;}
pto inter(line l1, line l2){//intersection
	double det=l1.a*l2.b-l2.a*l1.b;
	if(abs(det)<EPS) return pto(INF, INF);//parallels
	return pto(l2.b*l1.c-l1.b*l2.c, l1.a*l2.c-l2.a*l1.c)/det;
}
