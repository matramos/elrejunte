//https://cses.fi/problemset/task/1110
#include <bits/stdc++.h>
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define rsz resize
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second

#ifdef ANARAP
//local
#else
//judge
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

//Booth's algorithm
//Find lexicographically minimal string rotation in O(|S|)
int booth(string S){
    S += S;  // Concatenate string to it self to avoid modular arithmetic
    int n = sz(S);
    vector<int>f(n,-1);
    int k = 0;  // Least rotation of string found so far
    forr(j,1,n){
        char sj = S[j];
        int i = f[j - k - 1];
        while (i != -1 and sj != S[k + i + 1]){
            if (sj < S[k + i + 1])
                k = j - i - 1;
            i = f[i];
        }
        if (sj != S[k + i + 1]){
            if (sj < S[k])  
                k = j;
            f[j - k] = -1;
        }
        else{
            f[j - k] = i + 1;
        }   
	}
    return k; // Lexicographically minimal string rotation's position
}

int main() {
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out","w", stdout);
	#endif
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	string s;
	cin>>s;	
	int n = sz(s);
	int pos_minimal_rotation;
	pos_minimal_rotation = booth(s);
	s+=s;
	forr(i,pos_minimal_rotation,pos_minimal_rotation+n) cout<<s[i];
	
	return 0;
}
