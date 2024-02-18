// returns convex hull of p in CCW order
// left must return >=0 to delete collinear points
vector<pto> CH(vector<pto>& p) {
	if(sz(p) < 3) return p; // edge case, keep line or point
	vector<pto> ch;
	sort(p.begin(), p.end());
	forn(i, sz(p)) { // lower hull
		while(sz(ch)>=2 && ch[sz(ch)-1].left(ch[sz(ch)-2], p[i])) ch.pop_back();
		ch.pb(p[i]);
	}
	ch.pop_back();
	int k = sz(ch);
	dforn(i, sz(p)) { // upper hull
		while(sz(ch)>=k+2 && ch[sz(ch)-1].left(ch[sz(ch)-2],p[i]))ch.pop_back();
		ch.pb(p[i]);
	}
	ch.pop_back();
	return ch;
}
