//Problem: https://codeforces.com/contest/1476/problem/G
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
#define MAXN 1000
#else
#define MAXN 100010
#endif

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;


int n,sq,nq; // array size, sqrt(array size), #queries
struct Qu{ //[l, r)
	int l,r,id;
	int upds; // # of updates before this query
	int k;
}; 
Qu qs[MAXN];
ll ans[MAXN]; // ans[i] = answer to ith query
struct Upd{
	int p, v, prev;
};
Upd vupd[MAXN];

//Without updates
/*bool qcomp(const Qu &a, const Qu &b){
    if(a.l/sq!=b.l/sq) return a.l<b.l;
    return (a.l/sq)&1?a.r<b.r:a.r>b.r;
}*/

//With updates
bool qcomp(const Qu &a, const Qu &b){
	if(a.l/sq != b.l/sq) return a.l<b.l;
	if(a.r/sq != b.r/sq) return a.r<b.r;
	return a.upds < b.upds;
}

int v[MAXN],cnt[MAXN],lmofcnt[MAXN],rmofcnt[MAXN],cntofcnt[MAXN], used[MAXN], curq;
vector<int> changes;
vector<ii> cur;

void add(int idx){
	int x = v[idx];
	int cntval = cnt[x];
	int cntpos = rmofcnt[cntval]--;
	--cntofcnt[cntval];
	cnt[x]++;
	cntval++;
	lmofcnt[cntval] = cntpos;
	if(++cntofcnt[cntval] == 1)
	{
		rmofcnt[cntval] = cntpos;
		if(used[cntval] < curq) used[cntval] = curq, changes.pb(cntval);
	}
}

void remove(int idx){
	int x = v[idx];
	int cntval = cnt[x];
	int cntpos = lmofcnt[cntval]++;
	--cntofcnt[cntval];
	cnt[x]--;
	cntval--;
	rmofcnt[cntval] = cntpos;
	if(++cntofcnt[cntval] == 1)
	{
		rmofcnt[cntval] = cntpos;
		if(used[cntval] < curq) used[cntval] = curq, changes.pb(cntval);
	}
}

int get_ans(int k){
	sort(changes.begin(), changes.end());
	forall(it, cur) it->snd = cntofcnt[it->fst];
	vector<ii> newcur;
	newcur.reserve((int)sqrt(n)+10);
	int poscur = 0, poschange = 0;
	while(poscur < sz(cur) && poschange < sz(changes))
	{
		if(cur[poscur].snd < 1) poscur++;
		else if(cntofcnt[changes[poschange]] < 1) poschange++;
		else
		{
			if(cur[poscur].fst < changes[poschange])
			{
				newcur.pb(cur[poscur]);
				poscur++;
			}
			else if(cur[poscur].fst > changes[poschange])
			{
				newcur.pb(mp(changes[poschange], cntofcnt[changes[poschange]]));
				poschange++;
			}
			else
			{
				newcur.pb(cur[poscur]);
				poscur++;
				poschange++;
			}
		}
	}
	while(poscur < sz(cur))
	{
		if(cur[poscur].snd > 0) newcur.pb(cur[poscur]);
		poscur++;
	}
	while(poschange < sz(changes))
	{
		if(cntofcnt[changes[poschange]] > 0) newcur.pb(mp(changes[poschange], cntofcnt[changes[poschange]]));
		poschange++;
	}
	cur = newcur;
	vector<ii>::iterator l,r;
	l = r = cur.begin();
	//cout << "counters:\n";
	//forall(it,mofcnt) cout << "val=" << it->fst << " reps=" << it->snd << '\n';
	int ans = -1, sum = 0;
	if(l->fst == 0) l++,r++;
	while(r != cur.end())
	{
		while(r != cur.end() && sum < k){
			sum += r->snd;
			r++;
		}
		while(l != cur.end() && sum - l->snd >= k){
			sum -= l->snd;
			l++;
		}
		if(sum >= k && (ans == -1 || prev(r)->fst - l->fst < ans)) ans = prev(r)->fst - l->fst;
		if(l != cur.end())
		{
			sum -= l->snd;
			l++;
		}
	}
	//cout << "ans=" << ans << '\n';
	changes.clear();
	return ans;
}

void init(){
	lmofcnt[0] = 0;
	rmofcnt[0] = n-1;
	cntofcnt[0] = n;
}

//Without updates: O(n^2/sq + q*sq)
//with sq = sqrt(n): O(n*sqrt(n) + q*sqrt(n))
//with sq = n/sqrt(q): O(n*sqrt(q))
//
//With updates: O(sq*q + q*n^2/sq^2)
//with sq = n^(2/3): O(q*n^(2/3))
//with sq = (2*n^2)^(1/3) may improve a bit
void mos(){
    forn(i,nq)qs[i].id=i;
    //sq=sqrt(n)+.5; // without updates
    sq=pow(n, 2/3.0)+.5; // with updates
    sort(qs,qs+nq,qcomp);
    int l=0,r=0,upds=0;
    forn(i,nq){
        Qu q=qs[i];
        curq = i+1;
        while(l>q.l)add(--l);
        while(r<q.r)add(r++);
        while(l<q.l)remove(l++);
        while(r>q.r)remove(--r);
        while(upds<q.upds){
			if(vupd[upds].p >= l && vupd[upds].p < r) remove(vupd[upds].p);
			v[vupd[upds].p] = vupd[upds].v; // do update
			if(vupd[upds].p >= l && vupd[upds].p < r) add(vupd[upds].p);
			upds++;
		}
		while(upds>q.upds){
			upds--;
			if(vupd[upds].p >= l && vupd[upds].p < r) remove(vupd[upds].p);
			v[vupd[upds].p] = vupd[upds].prev; // undo update
			if(vupd[upds].p >= l && vupd[upds].p < r) add(vupd[upds].p);
		}
        //cout << "for query " << q.id << ": " << q.l << ' ' << q.r << ' ' << q.k << '\n';
        ans[q.id]=get_ans(q.k);
    }
}



int main()
{
	#ifdef ANARAP
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> nq;
	int auxv[MAXN];
	forn(i,n) cin >> v[i];
	forn(i,n) auxv[i] = v[i];
	int nupds = 0;
	forn(i,nq)
	{
		int t;
		cin >> t;
		if(t == 1)
		{
			int l,r,k;
			cin >> l >> r >> k;
			qs[i-nupds] = {l-1,r,i-nupds,nupds,k};
		}
		else
		{
			int p,x;
			cin >> p >> x;
			p--;
			vupd[nupds++] = {p,x,auxv[p]};
			auxv[p] = x;
		}
	}
	nq -= nupds;
	mos();
	forn(i,nq) cout << ans[i] << '\n';
	return 0;
}
