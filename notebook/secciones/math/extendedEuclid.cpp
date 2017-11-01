//ecuación diofántica lineal
//sea d=gcd(a,b); la ecuación a * x + b * y = c tiene soluciones enteras si
//d|c. La siguiente función nos sirve para esto. De forma general será:
//x = x0 + (b/d)n			x0 = xx*c/d
//y = y0 - (a/d)n			y0 = yy*c/d
ll xx,yy,d;
void extendedEuclid (ll a, ll b){ //a * xx + b * yy = d
	if (!b) {xx=1; yy=0; d=a; return;}
	extendedEuclid (b,a%b);
	ll x1=yy;
	ll y1=xx-(a/b)*yy;
	xx=x1; yy=y1;
}
