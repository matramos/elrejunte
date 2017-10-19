vector<int> b; //back table b[i] maximo borde de [0..i)
void kmppre(string &P) //by gabina with love
{
	b.clear();
	b.rsz(P.size());
	int i =0, j=-1; b[0]=-1;
	while(i<sz(P))
	{
		while(j>=0 && P[i] != P[j]) j=b[j];
		i++, j++;
		b[i] = j;
	}
}
void kmp(string &T,string &P) //Text, Pattern -- O(|T|+|P|)
{
	kmppre(P);
	int i=0, j=0;
	while(i<sz(T))
	{
		while(j>=0 && T[i]!=P[j]) j=b[j];
		i++, j++;
		if(j==sz(P))
		{
			//P encontrado en T empezando en [i-j,i)
			j=b[j];
		}
	}
}
