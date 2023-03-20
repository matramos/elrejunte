typedef long long T;
const T INF = 1000'000'100;

struct line{
	T m, b;
	
	line(){}
	line(T nm, T nb){ m = nm; b = nb; }
	
	T f(T x){ return m*x + b; }
};

struct li_chao{
	line cur_line;
	li_chao* lnode;
	li_chao* rnode;
	
	li_chao(line nline, li_chao* nlnode = nullptr, li_chao* nrnode = nullptr){
		cur_line = nline;
		lnode = nlnode; 
		rnode = nrnode; 
	}
	
	void add(line new_line, T l, T r){ // for persistent, use li_chao* instead of void 
		T m = (l+r) / 2;
		
		bool lef = new_line.f(l) < cur_line.f(l); // for max, use >
		bool mid = new_line.f(m) < cur_line.f(m); // for max, use >
		
		//~ uncomment for persistent
		//~ line to_push = new_line, to_keep = cur_line; 
		//~ if(mid) swap(to_push,to_keep);
		if(mid) swap(new_line,cur_line);
		
		if(r - l == 1){
			//~ uncomment for persistent
			//~ return new li_chao(to_keep);
			return;
		}else if(lef != mid){
			if(lnode == nullptr) lnode = new li_chao(line(0,INF)); // for min, use -INF
			//~ uncomment for persistent
			//~ return new li_chao(to_keep, lnode->add(to_push, l, m), rnode);
			lnode->add(new_line,l,m);
		}else{
			if(rnode == nullptr) rnode = new li_chao(line(0,INF)); // for min, use -INF
			//~ uncomment for persistent
			//~ return new li_chao(to_keep, lnode, rnode->add(to_push, m, r));
			rnode->add(new_line,m,r);
		}
	}
	
	T get(T x, T l, T r){
		T m = (r+l)/2;
		
		if(r - l == 1) return cur_line.f(x);
		else if(x < m){
			return min(cur_line.f(x), lnode == nullptr ? INF : lnode->get(x, l, m)); // for max, use max and -INF
		}else{
			return min(cur_line.f(x), rnode == nullptr ? INF : rnode->get(x, m, r)); // for max, use max and -INF
		}
	}
};
