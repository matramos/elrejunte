typedef long double T;
typedef long double ld;
const T EPS = 1e-9; // if T is integer, set to 0

struct pto{
	T x, y;
	
	pto() : x(0), y(0) {}
	pto(T _x, T _y) : x(_x), y(_y) {}
	
	pto operator+(pto b){ return pto(x+b.x, y+b.y); }
	pto operator-(pto b){ return pto(x-b.x, y-b.y); }
	pto operator+(T k){ return pto(x+k, y+k); }
	pto operator*(T k){ return pto(x*k, y*k); }
	pto operator/(T k){ return pto(x/k, y/k); }
	
	//dot product
	T operator*(pto b){ return x*b.x+y*b.y; }
	//cross product, a^b>0 if angle_cw(u,v)<180
	T operator^(pto b){ return x*b.y-y*b.x; }
	pto proy(pto b) { return b*((*this)*b)/(b*b); }

	T norm_sq(){ return x*x+y*y; }
	ld norm(){ return sqrtl(x*x+y*y); }
	ld dist(pto b){ return (b-(*this)).norm(); }

	//rotate by theta rads CCW w.r.t. origin (0,0)
	pto rotate(T theta) { return pto(x*cosl(theta)-y*sinl(theta),x*sinl(theta)+y*cosl(theta)); }
	
	// true if this is at the left side of line qr
	bool left(pto a, pto b){return ((a-*this)^(b-*this))>0;}
	bool operator<(const pto &b) const{return x<b.x-EPS || (abs(x-b.x)<=EPS && y<b.y-EPS);}
	bool operator==(pto b){return abs(x-b.x)<=EPS && abs(y-b.y)<=EPS;}
};

ld angle(pto a, pto o, pto b){
	pto oa=a-o, ob=b-o;
	return atan2l(oa^ob, oa*ob);
}

ld angle(pto a, pto b){
	ld cost = (a*b)/a.norm()/b.norm();
	return acosl(max(ld(-1.), min(ld(1.), cost)));
}
