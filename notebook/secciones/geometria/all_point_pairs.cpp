// after each step() execution pt is sorted by dot product of the event processed 
struct all_point_pairs { // O(n*n*log(n*n)), must add id, u, v to pto
	vector<pto> pt, ev; 
	vector<int> idx;
	int cur_step;
	
	all_point_pairs(vector<pto> pt_): pt(pt_) {
		idx = vector<int>(sz(pt));
		forn(i,sz(pt)) forn(j,sz(pt)) if(i!=j) { 
			pto p = pt[j]-pt[i]; p.u = pt[i].id, p.v = pt[j].id; ev.pb(p); 
		}
		sort(ev.begin(),ev.end(),cmp(pto(0,0),pto(1,0))); pto start(ev[0].y,-ev[0].x); 
		sort(pt.begin(), pt.end(), [&](pto &u, pto &v) { return u*start < v*start; });
		forn(i,sz(idx)) idx[pt[i].id] = i;
		cur_step = 0;
	}
	
	bool step() {
		if(cur_step>=sz(ev)) return false;
		int u = ev[cur_step].u, v = ev[cur_step].v;
		swap(pt[idx[u]],pt[idx[v]]);
		swap(idx[u],idx[v]);
		cur_step++;
		return true;
	}
};
