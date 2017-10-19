#define MAXP 100000 //no necesariamente primo
int criba[MAXP+1];
void crearCriba()
{
	int w[] = {4,2,4,2,4,6,2,6};
	for(int p=25;p<=MAXP;p+=10) criba[p]=5;
	for(int p=9;p<=MAXP;p+=6) criba[p]=3;
	for(int p=4;p<=MAXP;p+=2) criba[p]=2;
	for(int p=7,cur=0;p*p<=MAXP;p+=w[cur++&7]) if (!criba[p])
	for(int j=p*p;j<=MAXP;j+=(p<<1)) if(!criba[j]) criba[j]=p;
}
vector<int> primos;
void buscarPrimos()
{
	crearCriba();
	forr (i,2,MAXP+1) if (!criba[i]) primos.push_back(i);
}

//factoriza bien numeros hasta MAXP^2
void fact(ll n,map<ll,ll> &f) //O (cant primos)
{ //llamar a buscarPrimos antes
	forall(p, primos){
		while(!(n %*p))
		{
			f[*p]++;//divisor found
			n/=*p;
		}
	}
	if(n>1) f[n]++;
}

//factoriza bien numeros hasta MAXP
void fact2(ll n,map<ll,ll> &f) //O (lg n)
{ //llamar a crearCriba antes
	while (criba[n])
	{
		f[criba[n]]++;
		n/=criba[n];
	}
	if(n>1) f[n]++;
}

//Usar asi: divisores(fac, divs, fac.begin()); NO ESTA ORDENADO
void divisores(map<ll,ll> &f,vector<ll> &divs,map<ll,ll>::iterator it,ll n=1)
{
	if(it==f.begin()) divs.clear();
	if(it==f.end())
	{
		divs.pb(n);
		return;
	}
	ll p=it->fst, k=it->snd; ++it;
	forn(_, k+1) divisores(f, divs, it, n), n*=p;
}
ll cantDivs(map<ll,ll> &f)
{
	ll ret=1;
	forall(it, f) ret*=(it->second+1);
	return ret;
}
ll sumDivs(map<ll,ll> &f)
{
	ll ret=1;
	forall(it, f) 
	{
		ll pot=1, aux=0;
		forn(i, it->snd+1) aux+=pot, pot*=it->fst;
		ret*=aux;
	}
	return ret;
}

ll eulerPhi(ll n) // con criba: O(lg n)
{
	map<ll,ll> f;
	fact(n,f);
	ll ret=n;
	forall(it, f) ret-=ret/it->first;
	return ret;
}
ll eulerPhi2(ll n) // O (sqrt n)
{ 
	ll r = n;
	forr(i,2,n+1)
	{
		if((ll)i*i>n) break;
		if(n%i==0)
		{
			while(n%i==0) n/=i;
			r -= r/i;
		}
	}
	if (n != 1) r-= r/n;
	return r;
}
