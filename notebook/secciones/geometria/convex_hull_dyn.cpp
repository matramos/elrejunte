// Superior
struct Semi_Chull {
    set<pto> pts; // this set maintains the convex hull without collinears points
    //in case that we want to have them on the set, make the changes commented below
    bool check(pto p) {
        if(pts.empty()) return false;
        if(*pts.rbegin() < p) return false;
        if(p < *pts.begin()) return false;
        auto it = pts.lower_bound(p);
        if(it->x == p.x) return p.y <= it->y; //ignore it to take in count collinears points too
        pto b = *it;
        pto a = *prev(it);
        return ((b-p)^(a-p))+EPS >= 0; //> 0 to take in count collinears points too
    }
 
    void add(pto p) {
        if(check(p)) return;
        pts.erase(p); pts.insert(p);
        auto it = pts.find(p);
 
        while(true) {
            if(next(it) == pts.end() || next(next(it)) == pts.end()) break;
            pto a = *next(it);
            pto b = *next(next(it));
            if(((b-a)^(p-a))+EPS >= 0) { //> 0 to take in count collinears points too
                pts.erase(next(it));
            } else break;
        }
 
        it = pts.find(p);
 
        while(true) {
            if(it == pts.begin() || prev(it) == pts.begin()) break;
            pto a = *prev(it);
            pto b = *prev(prev(it));
            if(((b-a)^(p-a))-EPS <=0) { //< 0 to take in count collinears points too
                pts.erase(prev(it));
            } else break;
        }
    }
};
 
struct Chull {
    Semi_Chull sup, inf;
    void add(pto p) {
        sup.add(p);
        pto np = {-1*p.x, -1*p.y};
        inf.add(np);
    }
    bool check(pto p) {
		pto np = {-1*p.x, -1*p.y};
        return sup.check(p) && inf.check(np);
    }
};
