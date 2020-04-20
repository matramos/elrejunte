pair<int, int> sf[MAXN];
bool sacomp(int lhs, int rhs) {return sf[lhs] < sf[rhs];}
vector<int> constructSA(string& s) { // O(n log^2(n))
	int n = s.size();                   // (sometimes fast enough)
	vector<int> sa(n), r(n);
	forn(i,n) r[i] = s[i]; //r[i]: equivalence class of s[i..i+m)
	for(int m=1; m<n; m*=2) {
		//sf[i] = {r[i], r[i+m]}, used to sort for next equivalence classes
		forn(i,n) sa[i] = i, sf[i] = {r[i], i+m<n ? r[i+m] : -1};
		stable_sort(sa.begin(), sa.end(), sacomp); //O(n log(n))
		r[sa[0]] = 0;
		//if sf[sa[i]] == sf[sa[i-1]] then same equivalence class
		forr(i,1,n) r[sa[i]] = sf[sa[i]]!=sf[sa[i-1]] ? i : r[sa[i-1]];
	}
	return sa;
}