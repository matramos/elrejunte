#include <iostream>
#include <string>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	int i;
	string s;
	while (cin >> s)
	{for (i=s.size()-1;i>=0;i--) if (s[i]=='i') {cout << "N\n";return 0;}
	cout << "S\n";}
	return 0;
}

