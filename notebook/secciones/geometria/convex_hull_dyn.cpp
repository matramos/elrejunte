struct semi_chull {
    set<pto> pt; // maintains semi chull without collinears points
    // in case we want them on the set, make the changes commented below
    bool check(pto p) {
        if(pt.empty()) return false;
        if(*pt.rbegin() < p) return false;
        if(p < *pt.begin()) return false;
        auto it = pt.lower_bound(p);
        if(it->x == p.x) return p.y <= it->y; // remove for counting collinears
        pto b = *it;
        pto a = *prev(it);
        return ((b-p)^(a-p)) + EPS >= 0; // change here for counting collinears
    }
 
    void add(pto p) {
        if(check(p)) return;
        pt.erase(p); pt.insert(p);
        auto it = pt.find(p);
        while(true) {
            if(next(it) == pt.end() || next(next(it)) == pt.end()) break;
            pto a = *next(it), b = *next(next(it));
            if(((b-a)^(p-a)) + EPS >= 0) {// change here for counting collinears
                pt.erase(next(it));
            } else break;
        }
 
        it = pt.find(p);
        while(true) {
            if(it == pt.begin() || prev(it) == pt.begin()) break;
            pto a = *prev(it), b = *prev(prev(it));
            if(((b-a)^(p-a)) - EPS <= 0) {// change here for counting collinears
                pt.erase(prev(it));
            } else break;
        }
    }
};
struct CHD{
    semi_chull sup, inf;
    void add(pto p) { sup.add(p); inf.add(p*(-1)); }
    bool check(pto p) { return sup.check(p) && inf.check(p*(-1)); }
};
