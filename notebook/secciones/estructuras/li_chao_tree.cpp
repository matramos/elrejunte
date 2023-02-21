typedef long long T;
const int MAXN = 100000;
const T INF = LLONG_MAX;

struct line{
	T m, b;
	
	line(){}
	line(T nm, T nb){ m = nm; b = nb; }
	
	T f(T x){ return m*x + b; }
};

struct li_chao_tree{
	int sz;
	line neutro = line(0,INF); // for max, use line(0,-INF)
	line t[4*MAXN];
	
	void init(int n){
		sz = 1 << (32 - __builtin_clz(n));
		forn(i,2*sz) t[i] = neutro;
	}
	
	void add(line new_line, int v, int l, int r){
		int m = (l+r) / 2;
		
		bool lef = new_line.f(l) < new_line.f(l); // for max, use >
		bool mid = new_line.f(m) < new_line.f(m); // for max, use >
		
		if(mid) swap(new_line,t[v]);
		
		if(r - l == 1) return;
		else if(lef != mid) add(new_line, v*2, l, m);
		else add(new_line, v*2+1, m, r);
	}
	
	T get(int x, int v, int l, int r){
		int m = (r+l)/2;
		
		if(r - l == 1) return t[v].f(x);
		else if(x < m) return min(t[v].f(x), get(x, v*2, l, m)); // for max, use max
		else return min(t[v].f(x), get(x, v*2+1, m, r)); 		 // for max, use max
	}
};
