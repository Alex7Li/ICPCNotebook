/**
 * Author: Hakan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Description: Precompute the number of positive integers coprime to N up to a given limit.
 * - The sum phi(d) for all divisors d of n is equal to n.
 * - The sum of all positive numbers less than n that are coprime to n is n phi(n) / 2 (n > 1)
 * - For any a, n coprime, a^(phi(n)) = 1 mod n
 * - Specifically, for any prime p, any number a, a^{p-1} = 1 mod p
 * Status: Tested
 */
#pragma once

const int LIM = 5000000;
int phi[LIM];

void calculatePhi() {
    rep(i,0,LIM) phi[i] = i&1 ? i : i/2;
    for (int i = 3; i < LIM; i += 2) if(phi[i] == i)
            for (int j = i; j < LIM; j += i) phi[j] -= phi[j] / i;
}