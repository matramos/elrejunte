// https://algo.sk/br24/problem.php?problem=d3-badsquare
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=(n)-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin(); it!=v.end(); it++)
#define sz(c) ((int)c.size())
#define pb push_back
#define rsz resize
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef long long T;

template<typename T> void rec_kara(T* a, int one, T* b, int two, T* r) { 
	if(min(one, two) <= 20) { // must be at least "<= 1"
		forn(i, one) forn(j, two) r[i+j] += a[i] * b[j];
		return;
	}
	const int x = min(one, two);
	if(one < two) rec_kara(a, x, b + x, two - x, r + x);
	if(two < one) rec_kara(a + x, one - x, b, x, r + x);
	const int n = (x + 1) / 2, right = x / 2;
	vector<T> tu(2 * n);
	rec_kara(a, n, b, n, tu.data());
	forn(i, 2*n-1) {
		r[i] += tu[i];
		r[i+n] -= tu[i];
		tu[i] = 0;
	}
	rec_kara(a + n, right, b + n, right, tu.data());
	forn(i, 2*right-1) r[i+n] -= tu[i], r[i+2*n] += tu[i];
	tu[n-1] = a[n-1]; tu[2*n-1] = b[n-1];
	forn(i, right) tu[i] = a[i]+a[i+n], tu[i+n] = b[i]+b[i+n];
	rec_kara(tu.data(), n, tu.data() + n, n, r + n);
}
template<typename T> vector<T> multiply(vector<T> a, vector<T> b) {
	if(a.empty() || b.empty()) return {};
	vector<T> r(a.size() + b.size() - 1);
	rec_kara(a.data(), a.size(), b.data(), b.size(), r.data());
	return r;
}

int main(){
	#ifdef JP
		freopen("input.in", "r", stdin);
	#endif
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n; cin >> n;
	vector<T> a(n), b(n);
	forn(i,n) {
		int x; cin >> x;
		a[i] = x;
	}
	forn(i,n) {
		int x; cin >> x;
		b[i] = x;
	}
	forn(i,n) a.pb(a[i]);
	
	vector<T> abad = a; forn(i,sz(a)) abad[i] = abad[i] == 47 ? 1 : 0;
	vector<T> bbad = b; forn(i,sz(b)) bbad[i] = bbad[i] == 47 ? 1 : 0;
	
	reverse(b.begin(), b.end());
	vector<T> matching = multiply(a,b);
	
	reverse(bbad.begin(), bbad.end());
	vector<T> bad = multiply(abad, bbad);
	
	T ans =  0;
	forn(i,n) {
		if(bad[i+n-1] > 0 ) continue;
		ans = max(ans, matching[i+n-1]); 
	}
	
	cout << ll(ans) << "\n";
	
	return 0;
}

