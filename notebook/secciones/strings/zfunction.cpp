// z[i] = length of longest substring starting from s[i] that is prefix of s
// z[i] = max k: s[0,k) == s[i,i+k)
vector<int> zFunction(string& s) {
  int l = 0, r = 0, n = sz(s);
  vector<int> z(n, 0);
  forr(i, 1, n) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}
void match(string& T, string& P) {  // Text, Pattern -- O(|T|+|P|)
  string s = P + '$' + T;  //'$' should be a character that is not present in T
  vector<int> z = zFunction(s);
  forr(i, sz(P) + 1, sz(s)) if (z[i] == sz(P));  // match found, idx = i-sz(P)-1
}
