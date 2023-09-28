#define sqr(a) ((a)*(a))

pto perp(pto a){return pto(-a.y, a.x);}

line bisector(pto a, pto b){
	line l=line(a, b); pto m=(a+b)/2;
	return line(-l.b, l.a, -l.b*m.x+l.a*m.y);
}

struct circle{
	pto o; T r;
	
	circle(pto o_=pto(INF,INF), T r_=INF) : o(o_), r(r_) {}
	
	circle(pto a, pto b, pto c){
		o=bisector(a, b).inter(bisector(b, c))[0];
		r=o.dist(a);
	}
	
	// circle containing p1 and p2 with radius r
	// swap p1, p2 to get snd solution
	circle(pto a, pto b, T r_){
        ld d2=(a-b).norm_sq(), det=r_*r_/d2-ld(0.25);
        if(det<0) return;
        o=(a+b)/ld(2)+perp(b-a)*sqrt(det);
        r=r_;
	}
	
	pair<pto, pto> tang(pto p){
		pto m=(p+o)/2;
		ld d=o.dist(m);
		ld a=r*r/(2*d);
		ld h=sqrtl(r*r-a*a);
		pto m2=o+(m-o)*a/d;
		pto per=perp(m-o)/d;
		return make_pair(m2-per*h, m2+per*h);
	}
	
	vector<pto> inter(line l){
		ld a = l.a, b = l.b, c = l.c - l.a*o.x - l.b*o.y;
		
		pto xy0 = pto(a*c/(a*a+b*b),b*c/(a*a+b*b));
		if(c*c > r*r*(a*a+b*b)+EPS){
			return {};
		}else if(abs(c*c-r*r*(a*a+b*b))<EPS){
			return {xy0+o};
		}else{
			ld m = sqrtl((r*r - c*c/(a*a+b*b))/(a*a+b*b));
			pto p1 = xy0 + (pto(-b,a)*m);
			pto p2 = xy0 + (pto(b,-a)*m);
			return {p1+o,p2+o};
		}
	}
	
	vector<pto> inter(circle c){
		line l;
		l.a = o.x-c.o.x;
		l.b = o.y-c.o.y;
		l.c = (sqr(c.r)-sqr(r)+sqr(o.x)-sqr(c.o.x)+sqr(o.y)
		-sqr(c.o.y))/ld(2.0);
		return (*this).inter(l);
	}
};
