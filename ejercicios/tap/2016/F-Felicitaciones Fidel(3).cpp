#include <iostream>
#include <string>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	bool d,ya1,prim,ult;
	int f,cantd,cantr,cantrd,cantdr;
	string s;
	while (cin >> f)
	{
		cantd=0;cantr=0;cantrd=0;cantdr=0;
		for (int i=0;i<f;i++)
		{
			cin >> s;
			d=false;
			ya1=false;
			prim=false;
			ult=false;
			for (int j=0;j<s.size();j++)
			{
				if (s[j]=='D') {d=true;ya1=true;ult=true;}
				else if (s[j]=='R')
				{
					if (!ya1) prim=true;
					if (d) {d=false;cantdr++;ult=false;}
					ya1=true;
				}
			}
			if (prim && ult) cantrd++;
			else
				{
					if (prim) cantr++;
					else if (ult) cantd++;
				}
		}
		if (cantrd)
		{
			cantdr+=cantrd-1;
			if (cantd) cantdr++;
			if (cantr) cantdr++;
			cantd--;
			cantr--;
		}
		if (cantd>cantr && cantr>0) 
			cantdr+=cantr;
		if (cantr>=cantd && cantd>0) 
			cantdr+=cantd;
		cout << cantdr << "\n";
	}
}

