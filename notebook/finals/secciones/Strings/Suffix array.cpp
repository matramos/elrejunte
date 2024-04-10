#define RB(x) (x < n ? r[x] : 0)
void csort(vector<int>& sa, vector<int>& r, int k) {
  int n = sa.size();
  vector<int> f(max(255, n), 0), t(n);
  forn(i, n) f[RB(i + k)]++;
  int sum = 0;
  forn(i, max(255, n)) f[i] = (sum += f[i]) - f[i];
  forn(i, n) t[f[RB(sa[i] + k)]++] = sa[i];
  sa = t;
}
vector<int> constructSA(string& s) {  // O(n logn)
  int n = s.size(), rank;
  vector<int> sa(n), r(n), t(n);
  // r[i]: equivalence class of s[i..i+k)
  forn(i, n) sa[i] = i, r[i] = s[i];  
  for (int k = 1; k < n; k *= 2) {
    csort(sa, r, k);
    csort(sa, r, 0); // counting sort, O(n)
    // t : equiv classes array for next size
    t[sa[0]] = rank = 0; 
    forr(i, 1, n) {
      // check if sa[i] and sa[i-1] are in same equiv class
      if (r[sa[i]] != r[sa[i - 1]] ||
          RB(sa[i] + k) != RB(sa[i - 1] + k))
        rank++;
      t[sa[i]] = rank;
    }
    r = t;
    if (r[sa[n - 1]] == n - 1) break;
  }
  return sa;
}
