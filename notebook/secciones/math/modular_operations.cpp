const ll MOD = 1000000007; // Change according to problem

// Only needed for MOD > 2^31
// Actually, for 2^31 < MOD < 2^63 it's usually better to use __int128
// and normal multiplication (* operator) instead of mulMod
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
ll expMod(ll b,ll e,ll m=MOD) //O(log e)
{
	if(e<0) return 0;
	ll ret = 1;
	while(e){
		if(e&1) ret=ret*b%m; // ret = mulMod(ret,b,m); //if needed
		b=b*b%m; // b = mulMod(b,b,m);
		e>>=1;
	}
	return ret;
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

