#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
//<key,mapped type,comparator,...>
typedef tree<int,null_type,less<int>,rb_tree_tag,
	tree_order_statistics_node_update> indexed_set;
// find_by_order(i) returns iterator to the i-th elemnt
// order_of_key(k): returns position of the lower bound of k (0-indexed)
// Ej: 12, 100, 505, 1000, 10000.
// order_of_key(10) == 0, order_of_key(100) == 1,
// order_of_key(707) == 3, order_of_key(9999999) == 5
