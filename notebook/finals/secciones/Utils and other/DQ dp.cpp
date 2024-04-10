vector<vector<int>> dp; //maybe replace dim of K with only 2
int n;
// d&q DP: go down the range [l,r) like merge sort, but also
// making sure to iterate over [from,to) in each step, and
// spliting the [from,to) in 2 parts when goind down:
// [from, best] and [best, to)
void solve(int l, int r, int k, int from, int to) {
	if(l >= r) return;
	int cur = (l+r)/2;
	int bestpos = cur-1;
	int best = INF; // assumes we want to minimize cost
	forr(i,from,min(cur, to)) {
		// cost function that usually depends on dp[i][k-1]
		int c = fcost(i, k); 
		if(c < best) best = c, bestpos = i;
	}
	dp[cur][k] = best;
	solve(l, cur, k, from, bestpos+1);
	solve(cur+1, r, k, bestpos, to);
}
