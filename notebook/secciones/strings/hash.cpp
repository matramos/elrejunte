struct Hash {
	int P=1777771, MOD[2], PI[2];
	vector<int> h[2], pi[2];
	vector<ll> vp[2];
	Hash(string& s) {
		MOD[0]=999727999; MOD[1]=1070777777;
		PI[0]=325255434; PI[1]=10018302;
		forn(k,2) h[k].resize(s.size()+1), pi[k].resize(s.size()+1), vp[k].rsz(s.size()+1);
		forn(k,2) {
			h[k][0] = 0; pi[k][0] = vp[k][0] = 1;
			ll p=1;
			forr(i, 1, s.size()+1) {
				h[k][i] = (h[k][i-1] + p*s[i-1]) % MOD[k];
				pi[k][i] = (1LL * pi[k][i-1] * PI[k]) % MOD[k];
				vp[k][i] = p = (p*P) % MOD[k];
			}
		}
	}
	ll get(int s, int e) { // get hash value of the substring [s, e)
		ll h0 = (h[0][e] - h[0][s] + MOD[0]) % MOD[0];
		h0 = (1LL * h0 * pi[0][s]) % MOD[0];
		ll h1 = (h[1][e] - h[1][s] + MOD[1]) % MOD[1];
		h1 = (1LL * h1 * pi[1][s]) % MOD[1];
		return (h0<<32)|h1;
	}
	//get hash value of [s, e) if origVal in pos is changed to val
	//Assumes s <= pos < e. If multiple changes are needed, 
    //do what is done in the for loop for every change
    ll getChanged(int s, int e, int pos, int val, int origVal) {
        ll hv = get(s,e), h[2];
        h[1] = hv & ((1LL<<32)-1);
        h[0] = hv >> 32;
        forn(i,2) h[i] = (h[i] + vp[i][pos] * (val - origVal + MOD[i])) % MOD[i];
        return (h[0]<<32)|h[1];
    }
};