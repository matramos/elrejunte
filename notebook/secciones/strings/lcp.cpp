//LCP(sa[i], sa[j]) = min(lcp[i+1], lcp[i+2], ..., lcp[j])
//example: "banana", sa = {5,3,1,0,4,2}, lcp = {0,1,3,0,0,2}
//Num of dif substrings: (n*n+n)/2 - (sum over lcp array)
//Build suffix array (sa) before calling
vector<int> computeLCP(string& s, vector<int>& sa) {
	int n = s.size(), L = 0;
	vector<int> lcp(n), plcp(n), phi(n);
	phi[sa[0]] = -1;
	forr(i, 1, n) phi[sa[i]] = sa[i-1];
	forn(i, n) {
		if(phi[i]<0) {plcp[i] = 0; continue;}
		while(s[i+L] == s[phi[i]+L]) L++;
		plcp[i] = L;
		L = max(L-1, 0);
	}
	forn(i,n) lcp[i] = plcp[sa[i]];
	return lcp; // lcp[i]=LCP(sa[i-1],sa[i])
}