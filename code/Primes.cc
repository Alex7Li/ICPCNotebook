# include <bits/stdc++.h>
using namespace std;
#define EPS 1e-7
typedef long long LL;

bool IsPrime(LL x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (!(x % 2) || !(x % 3)) return false;
    LL s = (LL) (sqrt((double) (x)) + EPS);
    for (LL i = 5; i <= s; i += 6) {
        if (!(x % i) || !(x % (i + 2))) return false;
    }
    return true;
}

// Factor every number up until n in O(n) time.
// minFact[i] = the minimum factor of i higher than 1. minFact[0] = minFact[1] = 0
// primes[i] = the ith prime.
vector<int> factorAll(int n) {
    vector<int> primes(0);
    vector<int> minFact(n + 1);
    for (int i = 2; i <= n; i++) {
        if (minFact[i] == 0) {
            primes.push_back(i);
            minFact[i] = i;
        }
        for (int j = 0; j < primes.size() && primes[j] <= minFact[i] && i * primes[j] <= n; ++j) {
            minFact[i * primes[j]] = primes[j];
        }
    }
    return primes;
}
// Primes close to 1e9: 999'999'937, 1'000'000'007, 1'000'000'009
