typedef __int128 T;
typedef double ld; 
typedef vector<T> poly;
const T MAXN = (1<<21); // MAXN must be power of 2, 
// MOD-1 needs to be a multiple of MAXN, big mod and primitive root for NTT
const T MOD = 2305843009255636993LL, RT = 5; 
// const T MOD = 998244353, RT = 3;

struct CD {
	T x;
	CD(T x_) : x(x_) {}
	CD () {}
};

T mulmod(T a, T b) { return a*b%MOD; } 
T addmod(T a, T b) { T r = a+b; if(r>=MOD) r-= MOD; return r; } 
T submod(T a, T b) { T r = a-b; if(r<0) r+= MOD; return r; } 
CD operator * (const CD &a, const CD &b) { return CD(mulmod(a.x, b.x) ); } 
CD operator + (const CD &a, const CD &b) { return CD(addmod(a.x, b.x) ); } 
CD operator - (const CD &a, const CD &b) { return CD(submod(a.x, b.x) ); }

vector<T> rts(MAXN+9, -1);
CD root(int n, bool inv) { 
	T r = rts[n]<0 ? rts[n] = expMod(RT, (MOD-1)/n) : rts[n];
	return CD(inv ? expMod(r, MOD-2) : r);
}

/* FFT
struct CD { 
	ld r,i;
	CD(ld r_=0, ld i_=0):r(r_),i(i_){}
	ld real()const{return r;}
	void operator/=(const int c){r/=c, i/=c;}
};
CD operator*(const CD& a, const CD& b){ return CD(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r); }
CD operator+(const CD& a, const CD& b){return CD(a.r+b.r,a.i+b.i);}
CD operator-(const CD& a, const CD& b){return CD(a.r-b.r,a.i-b.i);}
const ld pi=acos(-1.0);
*/

CD cp1[MAXN+9], cp2[MAXN+9];
int R[MAXN+9];
void dft(CD *a, int n, bool inv) {
	forn(i,n) if(R[i] < i) swap(a[R[i]], a[i]);
	for(int m = 2; m<=n; m*=2) {
        // ld z=2*pi/m*(inv?-1:1); FFT 
		// CD wi=CD(cos(z),sin(z)); FFT
		CD wi = root(m, inv); // NTT
		for(int j = 0; j<n; j+=m) {
			CD w(1);
			for(int k = j, k2 = j+m/2; k2<j+m; k++, k2++) {
				CD u = a[k]; CD v = a[k2]*w; a[k] = u+v; a[k2] = u-v; w = w*wi;
			}
		}	
	}
    // if(inv) forn(i,n) a[i]/=n; FFT
	if(inv) { // NTT
		CD z(expMod(n,MOD-2));
		forn(i,n) a[i] = a[i]*z;
	}
}

poly multiply (poly &p1, poly &p2) {
	int n = sz(p1)+sz(p2)+1;
	int m = 1, cnt = 0;
	while(m <= n) m += m, cnt++;
	forn(i,m) { R[i] = 0; forn(j,cnt) R[i] = (R[i] << 1) | ((i>>j)&1); }
	forn(i,m) cp1[i] = 0, cp2[i] = 0;
	forn(i,sz(p1)) cp1[i] = p1[i];
	forn(i,sz(p2)) cp2[i] = p2[i];
	dft(cp1, m, false); dft(cp2,m,false);
	forn(i,m) cp1[i] = cp1[i] * cp2[i];
	dft(cp1, m, true);
	poly res;
	n -= 2;
    // forn(i,n) res.pb((T) floor(cp1[i].real()+0.5)); FFT
	forn(i,n) res.pb(cp1[i].x); // NTT
	return res;
}
