struct Cmp { // radial sort around point O in counter-clockwise direction starting from vector v
	pto o, v;
	Cmp (pto no, pto nv) : o(no), v(nv) {}
	bool half(pto p) {
		assert(!(p.x == 0 && p.y == 0)); // (0,0) isn't well defined
		return (v^p) > 0 || ((v^p) == 0 && (v*p) > 0); 
	}
	
	bool operator() (pto & p1, pto & p2) {
		return mp(half(p1-o), 0LL) < mp(half(p2-o), ((p1-o)^(p2-o)));
	}
};
