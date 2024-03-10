// 1- Random number generator (mt19937_64 for 64-bits version)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// usage
rng()%k // random value [0,k)
shuffle(v.begin(), v.end(), rng); // vector random shuffle

// 2- Pragma
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// 3- Custom comparator for set/map
struct comp {
	bool operator()(const double& a, const double& b) const {
		return a+EPS<b;}
};
set<double,comp> w; // or map<double,int,comp>

// 4- Iterate over non empty subsets of bitmask
for(int s=m;s;s=(s-1)&m) // Decreasing order
for (int s=0;s=s-m&m;) 	 // Increasing order

// 5- Other bits operations
// Return the numbers the numbers of 1-bit in x
int __builtin_popcount (unsigned int x)
// Returns the number of trailing 0-bits in x. x=0 is undefined.
int __builtin_ctz (unsigned int x)
// Returns the number of leading 0-bits in x. x=0 is undefined.
int __builtin_clz (unsigned int x)
// x of type long long just add 'll' at the end of the function.
int __builtin_popcountll (unsigned long long x)
// Get the value of the least significant bit that is one.
v=(x&(-x))

// 6- Comparing floats
const double EPS = 1e-9 // usually correct, but not always
abs(x-y) < EPS // use this instead of x == y
x > y + EPS // use this instead of x > y (EPS "against" comparison)
x > y - EPS // use this instead of x >= y (EPS "in favor" of comparison)

// 7- string stream, convert types easily
string int_to_str(int x) {
  stringstream ss;
  ss << x;
  string ret;
  ss >> ret;
  return ret;
}

// 8- Output
cout << setprecision(2) << fixed; // print floats with 2 decimal digits
cout << setfill(' ') << setw(3) << 2 << endl; // add spaces to the left

// 9- Input
string line;
getline(cin, line); // read whole line

cin >> noskipws; // make cin stop skipping white spaces
cin >> skipws; // make cin start skipping white spaces (on by default)

inline void Scanf(int& a) { // sometimes faster, only for positive integers
	char c = 0;
	while(c<33) c = getc(stdin);
	a = 0;
	while(c>33) a = a*10 + c - '0', c = getc(stdin);
}

// 10- Type limits
#include <limits>
numeric_limits<T>
	::max()
	::min()
	::epsilon()
// double inf
const double DINF=numeric_limits<double>::infinity();
