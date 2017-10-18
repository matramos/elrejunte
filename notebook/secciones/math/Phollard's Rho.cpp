bool es_primo_prob(ll n, int a)
{
	if(n==a) return true;
	ll s=0,d=n-1;
	while(d%2==0) s++,d/=2;
	ll x=expmod(a,d,n);
	if((x==1) || (x+1==n)) return true;
	forn(i,s-1)
	{
		x=mulmod(x, x, n);
		if(x==1) return false;
		if(x+1==n) return true;
	}
	return false;
}
bool rabin (ll n)  //devuelve true si n es primo
{
	if(n==1) return false;
	const int ar[]={2,3,5,7,11,13,17,19,23};
	forn(j,9) if(!es_primo_prob(n,ar[j])) return false;
	return true;
}
ll rho(ll n)
{
	if((n&1)==0) return 2;
	ll x=2,y=2,d=1;
	ll c=rand()%n+1;
	while(d==1)
	{
		x=(mulmod(x,x,n)+c)%n;
		y=(mulmod(y,y,n)+c)%n;
		y=(mulmod(y,y,n)+c)%n;
		if(x-y>=0) d=gcd(x-y,n);
		else d=gcd(y-x,n);
	}
	return d==n? rho(n):d;
}
void factRho (ll n,map<ll,ll> &f) //O (lg n)^3 un solo numero
{
	if (n == 1) return;
	if (rabin(n))
	{
		f[n]++;
		return;
	}
	ll factor = rho(n);
	factRho(factor);
	factRho(n/factor);
}
