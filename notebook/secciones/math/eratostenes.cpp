ll sieve_size;
bitset<10000010> bs; // 10^7
vi primes;

void sieve(ll upperbound)
{
    sieve_size = upperbound + 1;
    bs.set(); bs[0] = bs[1] = 0;
    for (ll i = 2; i <= sieve_size; i++) 
        if (bs[i]) 
        {
            for (ll j = i * i; j <= sieve_size; j += i) 
                bs[j] = 0;
            primes.push_back((int)i);
        }
}

bool isPrime(ll N) 
{
    if (N <= sieve_size) return bs[N];
    for (int i = 0; i < (int)primes.size(); i++)
        if (N % primes[i] == 0) return false;
    return true;
}