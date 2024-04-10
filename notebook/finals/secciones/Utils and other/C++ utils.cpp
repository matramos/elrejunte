// 1- (mt19937_64 for 64-bits version)
mt19937 rng(
    chrono::steady_clock::now().time_since_epoch().count());
shuffle(v.begin(), v.end(), rng);  // vector random shuffle
// 2- Pragma
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// 3- Custom comparator for set/map
struct comp {
  bool operator()(const double& a, const double& b) const {
    return a + EPS < b;
  }
};
set<double, comp> w;  // or map<double,int,comp>
// 4- Iterate over non empty subsets of bitmask
for (int s = m; s; s = (s - 1) & m)  // Decreasing order
for (int s = 0; s = s - m & m;)      // Increasing order
// 5- Other bits operations
int __builtin_popcount(unsigned int x) // # of bits on in x
int __builtin_popcountll(unsigned long long x) // ll version
int __builtin_ctz(unsigned int x) //# of trailing 0 (x != 0)
int __builtin_clz(unsigned int x) // # of leading 0 (x != 0)
v = (x & (-x)) // Find the least significant bit that is on
// 6- Input
inline void Scanf(int& a) { // only positive ints
  char c = 0;
  while (c < 33) c = getc(stdin);
  a = 0;
  while (c > 33) a = a * 10 + c - '0', c = getc(stdin);
}
