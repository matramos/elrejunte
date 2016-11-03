#include <bits/stdc++.h>

using namespace std;


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
    //freopen("input","r",stdin);
    //freopen("output","w",stdout);
	bitset <181> angulos;
	int ang;
	int hour = 1;

	int dif = 0;
	
	for (int mins = 0; mins<720; ++mins)
	{
		if(mins % 60 == 0) dif = hour * 30;
		if(mins % 12 != 0) dif +=6;
		if(dif>180) angulos.set(360-dif);
		else angulos.set(dif);
	}

	
	while (cin>>ang){
		if(angulos[ang]) cout<<"Y\n";
		else cout<<"N\n";
	}


    return 0;
}