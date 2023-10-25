#define sqr(a) ((a)*(a))
pto perp(pto a){return pto(-a.y, a.x);}
line bisector(pto a, pto b){
	line l = line(a, b); pto m = (a+b)/2;
	return line(-l.b, l.a, -l.b*m.x+l.a*m.y);
}
struct circle{
	pto o; T r;
	circle(){}
	circle(pto a, pto b, pto c) {
		o = bisector(a, b).inter(bisector(b, c));
		r = o.dist(a);
	}
	bool inside(pto p) { return (o-p).norm_sq() <= r*r+EPS; }
	bool inside(circle c) { // this inside of c
		T d = (o - c.o).norm_sq();
		return d <= (c.r-r) * (c.r-r) + EPS;
	}
	// circle containing p1 and p2 with radius r
	// swap p1, p2 to get snd solution
	circle* circle2PtoR(pto a, pto b, T r_) {
        ld d2 = (a-b).norm_sq(), det = r_*r_/d2 - ld(0.25);
        if(det < 0) return nullptr;
		circle *ret = new circle();
        ret->o = (a+b)/ld(2) + perp(b-a)*sqrt(det);
        ret->r = r_;
		return ret;
	}
	pair<pto, pto> tang(pto p) {
		pto m = (p+o)/2;
		ld d = o.dist(m);
		ld a = r*r/(2*d);
		ld h = sqrtl(r*r - a*a);
		pto m2 = o + (m-o)*a/d;
		pto per = perp(m-o)/d;
		return make_pair(m2 - per*h, m2 + per*h);
	}
	vector<pto> inter(line l) {
		ld a = l.a, b = l.b, c = l.c - l.a*o.x - l.b*o.y;
		pto xy0 = pto(a*c/(a*a + b*b), b*c/(a*a + b*b));
		if(c*c > r*r*(a*a + b*b) + EPS) {
			return {};
		}else if(abs(c*c - r*r*(a*a + b*b)) < EPS) {
			return { xy0 + o };
		}else{
			ld m = sqrtl((r*r - c*c/(a*a + b*b))/(a*a + b*b));
			pto p1 = xy0 + (pto(-b,a)*m);
			pto p2 = xy0 + (pto(b,-a)*m);
			return { p1 + o, p2 + o };
		}
	}
	vector<pto> inter(circle c) {
		line l;
		l.a = o.x - c.o.x;
		l.b = o.y - c.o.y;
		l.c = (sqr(c.r)-sqr(r)+sqr(o.x)-sqr(c.o.x)+sqr(o.y)-sqr(c.o.y))/2.0;
		return (*this).inter(l);
	}
	ld inter_triangle(pto a, pto b) { // area of intersection with oab
		if(abs((o-a)^(o-b)) <= EPS) return 0.;
		vector<pto> q = {a}, w = inter(line(a,b));
		if(sz(w) == 2) forn(i,sz(w)) if((a-w[i])*(b-w[i]) < -EPS) q.pb(w[i]);
		q.pb(b);
		if(sz(q) == 4 && (q[0]-q[1])*(q[2]-q[1]) > EPS) swap(q[1], q[2]);
		ld s = 0;
		forn(i, sz(q)-1){
			if(!inside(q[i]) || !inside(q[i+1])) s += r*r*angle((q[i]-o),q[i+1]-o)/T(2);
			else s += abs((q[i]-o)^(q[i+1]-o)/2);
		}
		return s;
	}
};
vector<ld> inter_circles(vector<circle> c){
	vector<ld> r(sz(c)+1); // r[k]: area covered by at least k circles
	forn(i, sz(c)) {      // O(n^2 log n) (high constant)
		int k = 1; 
		cmp s(c[i].o, pto(1,0));
		vector<pair<pto,int>> p = {
			{c[i].o + pto(1,0)*c[i].r, 0},
			{c[i].o - pto(1,0)*c[i].r, 0}};
		forn(j, sz(c)) if(j != i) {
			bool b0 = c[i].inside(c[j]), b1 = c[j].inside(c[i]);
			if(b0 && (!b1 || i<j)) k++;
			else if(!b0 && !b1) {
				vector<pto> v = c[i].inter(c[j]);
				if(sz(v) == 2) {
					p.pb({v[0], 1}); p.pb({v[1], -1});
					if(s(v[1], v[0])) k++;
				}
			}
		}
		sort(p.begin(), p.end(), [&](pair<pto,int> a, pair<pto,int> b) {
			return s(a.fst,b.fst); });
		forn(j,sz(p)) {
			pto p0 = p[j? j-1: sz(p)-1].fst, p1 = p[j].fst;
			ld a = angle(p0 - c[i].o, p1 - c[i].o);
			r[k]+=(p0.x-p1.x)*(p0.y+p1.y)/ld(2)+c[i].r*c[i].r*(a-sinl(a))/ld(2);
			k += p[j].snd;
		}
	}
	return r;
}
