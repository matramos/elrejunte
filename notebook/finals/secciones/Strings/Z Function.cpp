// z[i] = length of longest substring starting from S[i]
// that is prefix of S. z[i] = max k: S[0,k) == S[i,i+k)
vector<int> zFunction(string& s) {
  int l = 0, r = 0, n = sz(s); vector<int> z(n, 0);
  forr(i, 1, n) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}
void match(string& T, string& P) {//Text, Pattern O(|T|+|P|)
  string s = P + '$' + T; vector<int> z = zFunction(s);
  forr(i,sz(P)+1,sz(s)) if(z[i]==sz(P));//match at i-sz(P)-1
}
