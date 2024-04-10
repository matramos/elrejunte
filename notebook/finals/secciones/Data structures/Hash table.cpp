struct Hash {  // similar logic for any other data type
  size_t operator()(const vector<int>& v) const {
    size_t s = 0;
    for (auto& e : v)
      s ^= hash<int>()(e) + 0x9e3779b9 + (s<<6) + (s>>2);
    return s;
  }
};
unordered_set<vector<int>, Hash> s;  // map<key, val, Hash>
