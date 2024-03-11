// The substrings of S can be decomposed into equivalence classes
// 2 substr are of the same class if they have the same set of endpos
// Example: endpos("bc") = {2, 4, 6} in "abcbcbc"
// Each class is a node of the automaton.
// Len is the longest substring of each class
// Link in state X is the state where the longest suffix of the longest
// substring in X, with a different endpos set, belongs
// The links form a tree rooted at 0
// last is the state of the whole string after each extention
struct state {
  int len, link;
  map<char, int> next;
};  // clear next!!
state st[MAXN];
int sz, last;
void sa_init() {
  last = st[0].len = 0;
  sz = 1;
  st[0].link = -1;
}
void sa_extend(char c) {
  int k = sz++, p;  // k = new state
  st[k].len = st[last].len + 1;
  // while c is not present in p assign it as edge to the new state and
  // move through link (note that p always corresponds to a suffix state)
  for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
    st[p].next[c] = k;
  if (p == -1) st[k].link = 0;
  else {
    // state p already goes to state q through char c. Then, link of k
    // should go to a state with len = st[p].len + 1 (because of c)
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) st[k].link = q;
    else {
      // q is not the state we are looking for. Then, we
      // create a clone of q (w) with the desired length
      int w = sz++;
      st[w].len = st[p].len + 1;
      st[w].next = st[q].next;
      st[w].link = st[q].link;
      // go through links from p and while next[c] is q, change it to w
      for (; p != -1 && st[p].next[c] == q; p = st[p].link) st[p].next[c] = w;
      // change link of q from p to w, and finally set link of k to w
      st[q].link = st[k].link = w;
    }
  }
  last = k;
}
//  input: abcbcbc
//  i,link,len,next
//  0 -1 0 (a,1) (b,5) (c,7)
//  1 0 1 (b,2)
//  2 5 2 (c,3)
//  3 7 3 (b,4)
//  4 9 4 (c,6)
//  5 0 1 (c,7)
//  6 11 5 (b,8)
//  7 0 2 (b,9)
//  8 9 6 (c,10)
//  9 5 3 (c,11)
//  10 11 7
//  11 7 4 (b,8)