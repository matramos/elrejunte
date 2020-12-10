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
