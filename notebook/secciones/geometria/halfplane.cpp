struct halfplane:line{ // left half plane
	pto u, uv;
	ld angle;
	halfplane(){}
	halfplane(pto u_, pto v_): u(u_), uv(v_-u_), angle(atan2l(uv.y,uv.x)) {}
	bool operator<(halfplane h) const { return angle<h.angle; }
	bool out(pto p){ return (uv^(p-u))<-EPS; }
};

vector<pto> intersect(vector<halfplane> h){
	pto box[4] = {{INF,INF}, {-INF,INF}, {-INF,-INF}, {INF,-INF}};
	forr(i,0,4) h.pb(halfplane(box[i],box[(i+1)%4]));
	sort(h.begin(), h.end());
	deque<halfplane> dq;
	int len = 0;
	forn(i,sz(h)){
		while(len>1 && h[i].out(dq[len-1].inter(dq[len-2]))){ dq.pop_back(); len--; }
		while(len>1 && h[i].out(dq[0].inter(dq[1]))) { dq.pop_front(); len--; }
		
		if(len>0 && abs(h[i].uv^dq[len-1].uv)<=EPS) {
			if(h[i].uv*dq[len-1].uv<0.){
				return vector<pto>();
			}
			if(h[i].out(dq[len-1].u)){
				dq.pop_back();
				len--;
			}else continue;
		}
		
		dq.pb(h[i]);
		len++;
	}
	while(len>2 && dq[0].out(dq[len-1].inter(dq[len-2]))) { dq.pop_back(); len--; }
	while(len>2 && dq[len-1].out(dq[0].inter(dq[1]))) { dq.pop_front(); len--; }
	if(len<3) return vector<pto>();
	vector<pto> inter;
	forr(i,1,len) inter.pb(dq[i].inter(dq[i-1]));
	return inter;
}
