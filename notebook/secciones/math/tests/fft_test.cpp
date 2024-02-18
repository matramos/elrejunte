// https://algo.sk/br24/problem.php?problem=d3-badsquare
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(auto it=v.begin(); it!=v.end(); it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef ANARAP

#else

#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef ll T;
typedef double ld; 
typedef vector<T> poly;
const T MAXN = (1<<21); // MAXN must be power of 2, 
// MOD-1 needs to be a multiple of MAXN, big mod and primitive root for NTT
// const T MOD = 2305843009255636993LL, RT = 5; 
// const T MOD = 998244353, RT = 3;

/* NTT
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

T expMod(T b,T e, T m=MOD) {
	if(e<0) return 0;
	T ret = 1;
	while(e){
		if(e&1) ret=ret*b%m; 
		b=b*b%m; 
		e>>=1;
	}
	return ret;
}


vector<T> rts(MAXN+9, -1);
CD root(int n, bool inv) { 
	T r = rts[n]<0 ? rts[n] = expMod(RT, (MOD-1)/n) : rts[n];
	return CD(inv ? expMod(r, MOD-2) : r);
}
*/

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


CD cp1[MAXN+9], cp2[MAXN+9];
int R[MAXN+9];
void dft(CD *a, int n, bool inv) {
	forn(i,n) if(R[i] < i) swap(a[R[i]], a[i]);
	for(int m = 2; m<=n; m*=2) {
        ld z=2*pi/m*(inv?-1:1); // FFT
		CD wi=CD(cos(z),sin(z)); // FFT
		// CD wi = root(m, inv); NTT
		for(int j = 0; j<n; j+=m) {
			CD w(1);
			for(int k = j, k2 = j+m/2; k2<j+m; k++, k2++) {
				CD u = a[k]; CD v = a[k2]*w; a[k] = u+v; a[k2] = u-v; w = w*wi;
			}
		}	
	}
    if(inv) forn(i,n) a[i]/=n; // FFT
	// if(inv) { NTT
	//	CD z(expMod(n,MOD-2));
	// 	forn(i,n) a[i] = a[i]*z;
	// }
}

poly multiply (poly &p1, poly &p2) {
	int n = sz(p1)+sz(p2);
	int m = 1, cnt = 0;
	while(m <= n) m += m, cnt++;
	forn(i,m) { R[i] = 0; forn(j,cnt) R[i] = (R[i] << 1) | ((i>>j)&1); }
	forn(i,m) cp1[i] = 0, cp2[i] = 0;
	forn(i,sz(p1)) cp1[i] = ld(p1[i]);
	forn(i,sz(p2)) cp2[i] = ld(p2[i]);
	dft(cp1, m, false); dft(cp2,m,false);
	forn(i,m) cp1[i] = cp1[i] * cp2[i];
	dft(cp1, m, true);
	poly res;
	n -= 2;
    forn(i,n) res.pb((T) floor(cp1[i].real()+0.5)); // FFT
	// forn(i,n) res.pb(cp1[i].x); NTT
	return res;
}


int main(){
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n; cin >> n;
	poly a(n), b(n);
	forn(i,n) {
		int x; cin >> x;
		a[i] = x;
	}
	forn(i,n) {
		int x; cin >> x;
		b[i] = x;
	}
	forn(i,n) a.pb(a[i]);
	
	poly abad = a; forn(i,sz(a)) abad[i] = abad[i] == 47 ? 1 : 0;
	poly bbad = b; forn(i,sz(b)) bbad[i] = bbad[i] == 47 ? 1 : 0;
	
	reverse(b.begin(), b.end());
	poly matching = multiply(a,b);
	
	reverse(bbad.begin(), bbad.end());
	poly bad = multiply(abad, bbad);
	
	T ans =  0;
	forn(i,n) {
		if(bad[i+n-1] > 0 ) continue;
		ans = max(ans, matching[i+n-1]); 
	}
	
	cout << ll(ans) << "\n";
	
	return 0;
}
