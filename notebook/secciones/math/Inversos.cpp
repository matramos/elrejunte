#define MAXMOD 15485867
ll inv[MAXMOD];//inv[i]*i=1 mod MOD
void calc(int p) //O(p)
{
	inv[1]=1;
	forr(i,2,p) inv[i]=p-((p/i)*inv[p%i])%p;
}
int inverso(int x) //O(log x)
{
	return expMod(x, eulerPhi(MOD)-1);//si mod no es primo(sacar a mano)
	return expMod(x, MOD-2);//si mod es primo
}

// fact[i] = i!%MOD and ifact[i] = 1/(i!)%MOD
// inv is modular inverse function
ll fact[MAXN], ifact[MAXN];
void build_facts(){ // O(MAXN)
	fact[0] = 1;
	forr(i,1,MAXN) fact[i] = fact[i-1] * i%MOD;
	ifact[MAXN-1] = inv(fact[MAXN-1]);
	dforn(i, MAXN-1) ifact[i] = ifact[i+1] * (i+1)%MOD;
	return;
}
// n! / k!*(n-k)!
// assumes 0 <= n < MAXN
ll comb(ll n, ll k){
	if (k < 0 || n < k) return 0;
	return fact[n] * ifact[k]%MOD * ifact[n-k]%MOD;
}
