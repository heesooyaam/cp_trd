/**
 * Author: heesooyaam, adapted for cp_trd
 * Source: AlgoTemplates/Math/FactorizationSieve.cpp
 * Description: Линейное решето на [1,n]. lp[x] — минимальный простой делитель, lp[1]=1; primes — простые. factor(x) возвращает пары (простой,степень) по возрастанию простого.

 * Time: Построение O(n), factor O(\log x). Память O(n).
 * Status: Stress-tested against trial division.
 */
#pragma once
struct factorization_sieve_t {
    vector<int> lp, primes;
    factorization_sieve_t(int n) : lp(n + 1) {
        assert(n >= 1);
        lp[1] = 1;
        for (int i = 2; i < n + 1; ++i) {
            if (!lp[i])
                lp[i] = i, primes.eb(i);
            for (int p : primes) {
                if (p > lp[i] || p > n / i)
                    break;
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
            res.eb(p, e);
        }
        return res;
    }
};
