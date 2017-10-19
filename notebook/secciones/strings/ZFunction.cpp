//z[i]=length of longest substring starting from s[i] that is prefix of s
vector<int> z;
void zFunction(string &s)
{
	int n=s.size();
	for(int i=1,l=0,r=0;i<n;i++)
	{
		if(i<=r)
		z[i]=min(r-i+1,z[i-l]);
		while(i+z[i]<n && s[z[i]]==s[i+z[i]])
		z[i]++;
		if(i+z[i]-1>r)
		l=i, r=i+z[i]-1;
	}
}
void match(string &T,string &P) //Text, Pattern -- O(|T|+|P|)
{
	string s=P;
	s+='$'; //here append a character that is not present in T
	s.append(T);
	z.clear();
	z.rsz(s.size(),0);
	zFunction(s);
	forr(i,P.size()+1,s.size())
		if(z[i]==P.size()) //match found, idx = i-P.size()-1
}
