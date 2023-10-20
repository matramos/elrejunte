typedef long double T;

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
