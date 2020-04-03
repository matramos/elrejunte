//stores pairs (benefit,cost) (erases non-optimal pairs)
//Note that these pairs will be increasing by g and increasing by c
//If we insert a pair that is included in other, the big one will be deleted
//For lis 2d, create a GCS por each posible length, use as (-g, c) and
//binary search looking for the longest length where (-g, c) could be added
struct GCS {
	set<ii> s;
	void add(int g, int c){
		ii x={g,c};
		auto p=s.lower_bound(x);
		if(p!=s.end()&&p->snd<=x.snd)return;
		if(p!=s.begin()) {//erase pairs with less or equal benefit and more cost
			--p;
			while(p->snd>=x.snd){
				if(p==s.begin()){s.erase(p);break;}
				s.erase(p--);
			}
		}
		s.insert(x);
	}
	int get(int gain){ // min cost for the benefit greater or equal to gain
		auto p=s.lower_bound((ii){gain,-INF});
		int r=p==s.end()?INF:p->snd;
		return r;
	}
};