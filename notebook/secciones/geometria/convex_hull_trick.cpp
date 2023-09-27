struct CHT{
	vector<pto> hull, normal;
	T f; int pos;
	
	void init(vector<pto> lines, bool mini){
		f = mini ? 1 : -1;
		pos = 0;
		forn(i,sz(lines)) lines[i] = lines[i]*f;
		sort(lines.begin(),lines.end()); // if lines aren't sorted
		forn(i,sz(lines)) add(lines[i]);
	}
	void add(pto l) { // y = mx+b => pto(m,b)
		while(sz(normal) && normal.back()*(l-hull.back())<0) {
			hull.pop_back();
			normal.pop_back();
		}
		if(sz(hull)){
			pto n = (l-hull.back());
			normal.pb({-n.y,n.x});
		}
		hull.pb(l);
	}
	T get(T x) { // lg(sz(hull))
		pto q = {x,1};
		int idx = int(lower_bound(normal.begin(),normal.end(),q,[](pto a, pto b){
			return (a^b)>0;
		}) - normal.begin());
		return f*(q*hull[idx]);
	}
	vector<T> get(vector<T> q){ // O(1) if queries are sorted
		vector<T> ret;
		forn(i,sz(q)){
			while(pos<sz(normal)-1 && (normal[pos]^pto(q[i],1))>0) pos++;
			ret.pb(hull[pos]*pto(q[i],1)*f);
		}
		return ret;
	}
};
