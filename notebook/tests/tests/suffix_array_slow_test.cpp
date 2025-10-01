//Problem: https://codeforces.com/gym/102428/problem/G
#include <bits/stdc++.h>
#define sqr(a) ((a)*(a))
#define rsz resize
#define forr(i,a,b) for(int i=(a);i<(b);i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1;i>=0;i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();it++)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define fst first
#define snd second
#define MAXN 500010

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

pair<int, int> sf[MAXN];
bool sacomp(int lhs, int rhs) {return sf[lhs] < sf[rhs];}
vector<int> constructSA(string& s) { // O(n log^2(n))
    int n = s.size();                   // (sometimes fast enough)
    vector<int> sa(n), r(n);
    forn(i,n) r[i] = s[i]; //r[i]: equivalence class of s[i..i+m)
    for(int m=1; m<n; m*=2) {
        //sf[i] = {r[i], r[i+m]}, used to sort for next equivalence classes
        forn(i,n) sa[i] = i, sf[i] = {r[i], i+m<n ? r[i+m] : -1};
        stable_sort(sa.begin(), sa.end(), sacomp); //O(n log(n))
        r[sa[0]] = 0;
        //if sf[sa[i]] == sf[sa[i-1]] then same equivalence class
        forr(i,1,n) r[sa[i]] = sf[sa[i]]!=sf[sa[i-1]] ? i : r[sa[i-1]];
    }
    return sa;
}

string s;
vector<int> sa;

bool isSmaller(string &a, int froma, string &b, int fromb, int sz)
{
    forn(i,sz)
    {
        assert(fromb+i < b.size());
        if(froma+i == a.size()) return true;
        if(a[froma+i] != b[fromb+i]) return a[froma+i] < b[fromb+i];
    }
    return false;
}

bool can(int sz, int from, string &x)
{
    //cout << "can " << sz << ":\n";
    int L = 0,R = sa.size()-1,M;
    while(L < R)
    {
        M = (L+R)/2;
        if(isSmaller(s, sa[M], x, from, sz)) L = M+1;
        else R = M;
    }
    assert(from+sz <= x.size());
    if(from+sz > x.size() || sa[L]+sz > s.size()) return false;
    forn(i,sz)
    {
        //cout << from+i << ' ' << sa[L]+i << '\n';
        //cout << x[from+i] << ' ' << s[sa[L]+i] << '\n';
        if(x[from+i] != s[sa[L]+i]) return false;
    }
    return true;
}

int main()
{
    #ifdef REJUNTE
    freopen("input.in","r",stdin);
    //freopen("output.out","w",stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> s;
    sa = constructSA(s);
    int q;
    cin >> q;
    forn(i,q)
    {
        string x;
        cin >> x;
        int pos = 0, ans = 0;
        while(pos < x.size())
        {
            int L = 0, R = x.size()-pos,M;
            while(L < R)
            {
                M = (L+R+1)/2;
                if(can(M, pos, x)) L = M;
                else R = M-1;
            }
            //cout << pos << ' ' << L << '\n';
            if(L == 0)
            {
                ans = -1;
                break;
            }
            pos+=L;
            ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}