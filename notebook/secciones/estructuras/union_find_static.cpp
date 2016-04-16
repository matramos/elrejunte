#define MAXN ...
int p[MAXN], rank[MAXN], setSize[MAXN], numSets;

inline void init(int n)
{
    memset(rank,0, sizeof(int)*n);
    for(int i=0;i<n;++i) p[i]=i, setSize[i]=1;
    numSets = n;
}
inline int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
inline bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i, int j) 
{ 
    int x = findSet(i), y = findSet(j);
    if (!(x==y)) 
    { 
        numSets--; 
        if (rank[x] > rank[y]) 
        { 
            p[y] = x; 
            setSize[x] += setSize[y];
        }
        else 
        { 
            p[x] = y;
            setSize[y] += setSize[x];
            if (rank[x] == rank[y]) rank[y]++; 
        } 
    }
}
inline int numDisjointSets() { return numSets; }
inline int sizeOfSet(int i) { return setSize[findSet(i)]; }