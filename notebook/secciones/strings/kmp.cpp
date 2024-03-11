// b[i] = longest border of t[0,i) = length of the longest prefix of
// the substring P[0..i-1) that is also suffix of the substring P[0..i)
// For "AABAACAABAA", b[i] = {-1, 0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5}
vector<int> kmppre(string& P) {  //
  vector<int> b(sz(P) + 1);
  b[0] = -1;
  int j = -1;
  forn(i, sz(P)) {
    while (j >= 0 && P[i] != P[j]) j = b[j];
    b[i + 1] = ++j;
  }
  return b;
}
void kmp(string& T, string& P) {  // Text, Pattern -- O(|T|+|P|)
  int j = 0;
  vector<int> b = kmppre(P);
  forn(i, sz(T)) {
    while (j >= 0 && T[i] != P[j]) j = b[j];
    if (++j == sz(P)) {
      // Match at i-j+1, do something
      j = b[j];
    }
  }
}
