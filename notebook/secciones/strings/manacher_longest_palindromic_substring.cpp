string s;
int d1[MAXN];//d1[i]=long del maximo palindromo impar con centro en i
int d2[MAXN];//d2[i]=analogo pero para longitud par
//0 1 2 3 4
//a a b a a <--d1[2]=3
//a a a a <--d2[2]=2 (estan uno antes)
void manacher() // O(|S|) - find longest palindromic substring
{
	int l=0, r=-1, n=sz(s);
	forn(i, n)
	{
		int k=(i>r? 1 : min(d1[l+r-i], r-i));
		while(i+k<n && i-k>=0 && s[i+k]==s[i-k]) ++k;
		d1[i] = k--;
		if(i+k > r) l=i-k, r=i+k;
	}
	l=0, r=-1;
	forn(i, n)
	{
		int k=(i>r? 0 : min(d2[l+r-i+1], r-i+1))+1;
		while(i+k-1<n && i-k>=0 && s[i+k-1]==s[i-k]) k++;
		d2[i] = --k;
		if(i+k-1 > r) l=i-k, r=i+k-1;
	}
}
