/**
 * Author: heesooyaam, adapted for cp_trd
 * Source: AlgoTemplates/Math/FactorizationSieve.cpp
 * Description: Linear sieve on [1,n]. lp[x] is the smallest
 *  prime divisor (lp[1]=1); primes contains exactly the primes.
 *  factor(x) returns (prime, exponent) pairs in increasing order.
 * Time: Build O(n), factor O(\log x). Memory O(n).
 * Status: Stress-tested against trial division.
 */
#pragma once
struct factorization_sieve_t {
    vector<int> lp, primes;
    factorization_sieve_t(int n) : lp(n + 1) {
        assert(n >= 1);
        lp[1] = 1;
        for (int i = 2; i < n + 1; ++i) {
            if (!lp[i]) lp[i] = i, primes.push_back(i);
            for (int p : primes) {
                if (p > lp[i] || p > n / i) break;
                lp[i * p] = p;
            }
        }
    }
    bool is_prime(int x) const { return x > 1 && lp[x] == x; }
    vector<pair<int, int>> factor(int x) const {
        assert(1 <= x && x < int(lp.size()));
        vector<pair<int, int>> res;
        while (x > 1) {
            int p = lp[x], e = 0;
            do {
                x /= p;
                ++e;
            } while (x % p == 0);
            res.push_back({p, e});
        }
        return res;
    }
};
