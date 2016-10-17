#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef vector<string> vs;
typedef vector<int> vi;
typedef set<int> si;
typedef vector<si> vsi;

#define pb push_back



int main()
{
    //freopen("input/G.in","r",stdin);
    //freopen("output","w",stdout);

    vs univ;
    vi rev;
    vsi autor;
    vi problemas;
    string s;
    int reviews, papers;
    int problem= 0 ;

    while(cin >> reviews >> papers)
    {
        if(reviews == 0) return 0;
        autor.assign(papers, si());
        rev.assign(papers+1, 0);
        problemas.assign(papers+1,0);
        
        for(int i=0;i<papers;++i){
            cin >> s;
            // cout << s ;
            univ.pb(s);
            for(int j=0,x;j<reviews;++j) {
                cin >> x;
                // cout << " " << x;
                ++rev[x];
                autor[i].insert(x);
            }
            // autor reviews un mismo paper mas de una vez
            if(autor[i].size()!=reviews) problemas[i+1]=1;
        }

        // todos papers tengan mÃ¡s de un rev
        for(int i=1;i<=papers;++i) if(rev[i]<2) problemas[i]=1;

        for(int i=0;i<papers;++i){
            s = univ[i];
            for(si::iterator it=autor[i].begin(); it!=autor[i].end();++it){
                
                if(s == univ[(*it)-1]) problemas[*it]=1;
            }
        }
        problem=0;
        for(int i=1;i<=problemas.size();++i)problem+=problemas[i];
        
        if(problem==1) cout << problem << " PROBLEM FOUND\n";
        else if(problem>1) cout << problem << " PROBLEMS FOUND\n";
        else cout << "NO PROBLEMS FOUND\n";

        rev.clear();
        autor.clear();
        problem = 0;
        univ.clear();
        problemas.clear();
    }
    

    

    return 0;
}
