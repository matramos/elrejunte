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


void pre(){ //o(MAXMOD)
	// pay attention on MAXMOD value
	fact[0] = 1;
	forr(i,1,MAXMOD-2) fact[i] = (fact[i-1]*i)%MOD;
	invFact[MAXMOD-3] = inverso(fact[MAXMOD-3]);
	dforn(i, MAXMOD-3) invFact[i] = (invFact[i+1]*(i+1))%MOD;
	return;
}
 
// n! / k!*(n-k)!
ll comb(ll nn, ll k){
	if (k < 0 || nn < k) return 0;
	return (fact[nn]*invFact[k]%MOD)*invFact[nn-k]%MOD;
}
