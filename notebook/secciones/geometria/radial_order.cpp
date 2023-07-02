struct Cmp { // radial sort around point O
	pto o;
	Cmp (pto no) : o(no) {}
	bool half(pto p) const{
		assert(!(p.x == 0 && p.y == 0)); // (0,0) isn't well defined
		return p.y > 0 || (p.y == 0 && p.x < 0); 
	}
	
	bool operator() (pto & p1, pto & p2) const {
		return mp(half(p1-o), 0LL) < mp(half(p2-o), ((p1-o)^(p2-o)));
	}
};
