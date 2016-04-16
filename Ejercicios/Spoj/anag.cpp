// http://www.spoj.com/problems/ANAG/
//  ACC

#include <iostream>
#include <map>
#include <string>

using namespace std;

main (){
	int casos;
	string s1, s2;

	cin >> casos;

	for (int c = 1; c <= casos; c++)
	{
		cin >> s1 >> s2;

		if (s1.length() == s2.length()){
			map<char, int> ss1, ss2;

			for (int i = 0; i < s1.length(); i++){
				ss1[s1[i]]++;
				ss2[s2[i]]++;
			}

			if (ss1 == ss2) cout << "YES" << endl;
			else cout << "NO" << endl;
		}
		else cout << "NO" << endl;
	}
}