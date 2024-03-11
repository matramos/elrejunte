// stores disjoint intervals as [first, second)
// the final result is the union of the inserted intervals
// [1, 5), [2, 4), [10, 13), [11, 15) -> [1, 5), [10, 15)
struct disjoint_intervals {
  set<ii> s;
  void insert(ii v) {
    if (v.fst >= v.snd) return;
    auto at = s.lower_bound(v);
    auto it = at;
    if (at != s.begin() && (--at)->snd >= v.fst) v.fst = at->fst, --it;
    for (; it != s.end() && it->fst <= v.snd; s.erase(it++))
      v.snd = max(v.snd, it->snd);
    s.insert(v);
  }
};