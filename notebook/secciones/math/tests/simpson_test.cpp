// problem: https://codeforces.com/gym/104196/problem/D
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i = a; i<b; i++)
#define forn(i,n) forr(i,0,n)
#define dfornt(i,n) for(int i = n-1; i>-1; i--)
#define forall(i,v) for(auto i = v.begin(); i != v.end(); i++)
#define sz(v) ((int) v.size()) 
#define pb push_back
#define fst first
#define snd second
#define lb lower_bound
#define ub upper_bound
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef long double T;
const T pi = acosl(-1.0);

// polar coordinates: x=r*cos(theta), y=r*sin(theta),  f=(r*r)/2
T simpson(std::function<T(T)> f, T a, T b, int n=10000) { // O(n)
	T area=0, h=(b-a)/T(n), fa=f(a), fb;
	forn(i, n)
	{
		fb = f(a+h*T(i+1));
		area += fa +T(4)*f(a+h*T(i+0.5)) +fb; fa=fb;
	}
	return area*h/T(6.);
}

struct pto{
	T x,y;
	
	pto(T nx=0, T ny=0): x(nx), y(ny) {}
	pto operator-(pto b) { return pto(x-b.x, y-b.y); }
	T operator*(pto b) {return x*b.x + y*b.y; }
	T operator^(pto b) {return x*b.y - y*b.x; }
	T norm() { return sqrtl(x*x+y*y); }
};

T angle(pto a, pto b){
	T ans = atan2l(a^b, a*b);
	return (ans < 0 ? ans + 2*pi : ans);
}

struct line{
	T a, b, c;
	
	line() {}
	line(pto p, pto q): a(q.y-p.y), b(p.x-q.x), c(a*p.x+b*p.y) {}
};

int main () {
	#ifdef JP
		freopen("input.txt", "r", stdin);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	T X,Y,R; cin >> X >> Y >> R;
	int n; cin >> n;
	vector<pto> ptos(n);
	forn(i,n) {
		cin >> ptos[i].x >> ptos[i].y;
		ptos[i].x -= X;
		ptos[i].y -= Y;
	}
	
	T suma = 0, sumb = 0;
	pto axis = {1,0};
	forn(i,n) {
		pto a = ptos[i];
		pto b = ptos[(i+1)%n];
		
		line cur = line(a,b);
		T t1 = angle(axis,a);
		T t2 = angle(axis,b);
		
		if(fabsl(t1-t2) > pi){
			if(fabsl(t1+T(2)*pi-t2) < pi) t1 += T(2)*pi;
			else if(fabsl(t2+T(2)*pi-t1) < pi) t2 += T(2)*pi;
		}
		
		assert(fabsl(t1-t2) < pi);
		auto f = [&](T x) { // (r^2)/2 para funciones polares, con r la funcion a integrar
			T r = R*R*(cur.a*cosl(x) + cur.b*sinl(x))/cur.c;
			return (r*r)/T(2);
		};
		if(t1<t2) {
			suma += simpson(f,t1,t2);
		}else if(t2<t1){
			sumb += simpson(f,t2,t1);
		}
	}
	
	cout << fixed << setprecision(9) << fabsl(suma-sumb) << "\n";
	
	#ifdef JP
		cerr << "Time elapsed: " <<  clock() * 1000 / CLOCKS_PER_SEC << " ms\n";
	#endif
}
