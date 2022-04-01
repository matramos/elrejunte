// declaration (mt19937_64 for 64-bits version)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// usage
rng()%k // random value [0,k)
shuffle(v.begin(), v.end(), rng); // vector random shuffle
