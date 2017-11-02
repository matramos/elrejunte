ll mulMod(ll a,ll b,ll m=MOD) //O(log b)
{ //returns (a*b) %c, and minimize overfloor
	ll x=0, y=a%m;
	while(b>0)
	{
		if(b%2==1) x=(x+y)%m;
		y=(y*2)%m;
		b/=2;
	}
	return x%m;
}
ll expMod(ll b,ll e,ll m=MOD) //O(log b)
{
	if(!e) return 1;
	ll q=expMod(b,e/2,m);
	q=mulMod(q,q,m);
	return e%2? mulMod(b,q,m) : q;
}
ll sumMod(ll a,ll b,ll m=MOD)
{
	a%=m;
	b%=m;
	if(a<0) a+=m;
	if(b<0) b+=m;
	return (a+b)%m;
}
ll difMod(ll a,ll b,ll m=MOD)
{
	a%=m;
	b%=m;
	if(a<0) a+=m;
	if(b<0) b+=m;
	ll ret=a-b;
	if(ret<0) ret+=m;
	return ret;
}
ll divMod(ll a,ll b,ll m=MOD)
{
	return mulMod(a,inverso(b),m);
}

