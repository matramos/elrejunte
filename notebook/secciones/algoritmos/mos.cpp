// Commented code should be used if updates are needed
int n, sq, nq;  // array size, sqrt(array size), #queries
struct Qu {     //[l, r)
  int l, r, id;
  // int upds; // # of updates before this query
};
Qu qs[MAXN];
ll ans[MAXN];  // ans[i] = answer to ith query
// struct Upd{
//   int p, v, prev; // pos, new_val, prev_val
// };
// Upd vupd[MAXN];

// Without updates
bool qcomp(const Qu &a, const Qu &b) {
  if (a.l / sq != b.l / sq) return a.l < b.l;
  return (a.l / sq) & 1 ? a.r < b.r : a.r > b.r;
}

// With updates
// bool qcomp(const Qu &a, const Qu &b){
//   if(a.l/sq != b.l/sq) return a.l<b.l;
//   if(a.r/sq != b.r/sq) return a.r<b.r;
//   return a.upds < b.upds;
// }

// Without updates: O(n^2/sq + q*sq)
// with sq = sqrt(n): O(n*sqrt(n) + q*sqrt(n))
// with sq = n/sqrt(q): O(n*sqrt(q))
//
// With updates: O(sq*q + q*n^2/sq^2)
// with sq = n^(2/3): O(q*n^(2/3))
// with sq = (2*n^2)^(1/3) may improve a bit
void mos() {
  forn(i, nq) qs[i].id = i;
  sq = sqrt(n) + .5;  // without updates
  // sq=pow(n, 2/3.0)+.5; // with updates
  sort(qs, qs + nq, qcomp);
  int l = 0, r = 0;
  init();
  forn(i, nq) {
    Qu q = qs[i];
    while (l > q.l) add(--l);
    while (r < q.r) add(r++);
    while (l < q.l) remove(l++);
    while (r > q.r) remove(--r);
    // while(upds<q.upds){
    //   if(vupd[upds].p >= l && vupd[upds].p < r) remove(vupd[upds].p);
    //   v[vupd[upds].p] = vupd[upds].v; // do update
    //   if(vupd[upds].p >= l && vupd[upds].p < r) add(vupd[upds].p);
    //   upds++;
    // }
    // while(upds>q.upds){
    //   upds--;
    //   if(vupd[upds].p >= l && vupd[upds].p < r) remove(vupd[upds].p);
    //   v[vupd[upds].p] = vupd[upds].prev; // undo update
    //   if(vupd[upds].p >= l && vupd[upds].p < r) add(vupd[upds].p);
    // }
    ans[q.id] = get_ans();
  }
}
