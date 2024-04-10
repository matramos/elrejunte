#include <ext/rope>
using namespace __gnu_cxx;
rope<int> s;
// Sequence with O(logn) access, insert, erase any pos
// s.push_back(x)
// s.append(other_rope)
// s.insert(i,x)
// s.insert(i,other_rope) // insert rope r at position i
// s.erase(i,k) // erase subsequence [i,i+k)
// s.substr(i,k) // get new rope corresponding to [i,i+k)
// s[i] // get element (cannot modify)
// s.mutable_reference_at(i) // get element (allows modif)
// s.begin() and s.end() are const iterators
// (use mutable_begin(), mutable_end() to allow modif)
