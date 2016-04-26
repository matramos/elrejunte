#include <cstdio>
#include <cstring>
#include <bitset>
#include <vector>
using namespace std;

typedef long long ll;

ll _sieve_size;
bitset<1000000> bs;
int primes[100000];

void sieve(ll upperbound) 
{
    _sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i <= _sieve_size; i++) if (bs[i]) 
    {
        for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;
        primes[++primes[0]] = (int)i;
    }
}

bool isPrime(ll N)
{
    int psz = primes[0];
    if (N <= _sieve_size) return bs[N];
    for (int i = 0; i < psz; i++)
        if (N % primes[i] == 0) return false;
    return true;
}

ll EulerPhi(ll N) 
{
    ll PF_idx = 1, PF = primes[PF_idx], ans = N;
    while (PF * PF <= N) 
    {
        if (N % PF == 0) ans -= ans / PF;
        while (N % PF == 0) N /= PF;
        PF = primes[++PF_idx];
    }
    if (N != 1) ans -= ans / N;
    return ans;
}


int main()
{
    freopen("input","r",stdin);
    freopen("output","w",stdout);
    primes[0]=0;
    sieve(100000);

    unsigned N;
    while(scanf("%u",&N)!=EOF)
    {
        printf("%lld\n", EulerPhi(N)>>1);
    }


    return 0;
}
