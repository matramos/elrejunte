//Compilar: g++ --std=c++11
struct Hash{
	size_t operator()(const ii &a)const
	{
		size_t s=hash<int>()(a.fst);
		return hash<int>()(a.snd)+0x9e3779b9+(s<<6)+(s>>2);
	}
	size_t operator()(const vector<int> &v)const
	{
		size_t s=0;
		for(auto &e : v) s^=hash<int>()(e)+0x9e3779b9+(s<<6)+(s>>2);
		return s;
	}
};
unordered_set<ii, Hash> s;
unordered_map<ii, int, Hash> m;//map<key, value, hasher>
