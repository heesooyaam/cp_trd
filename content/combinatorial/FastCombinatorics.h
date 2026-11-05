/**
 * Author: heesooyaam, adapted for cp_trd
 * Source: AlgoTemplates/Math/fast_mint.cpp
 * Description: Factorials and binomial coefficients modulo prime
 *  mint::get\_mod(). Requires 0 <= n < modulus. C(n,k)=0 for
 *  k outside [0,n]. Reuse one object; build at maximum n once.
 * Time: init O(n+\log mod), C O(1).
 * Status: Tested against Pascal's triangle.
 */
#pragma once
#include "../number-theory/FastMint.h"
struct combinations {
    vector<mint> fact, inv_fact;
    combinations(int n) : fact(n + 1, 1), inv_fact(n + 1) {
        assert(0 <= n && uint32_t(n) < mint::get_mod());
        for (int i = 1; i < n + 1; ++i)
            fact[i] = fact[i - 1] * i;
        inv_fact[n] = fact[n].inverse();
        for (int i = n; i; --i)
            inv_fact[i - 1] = inv_fact[i] * i;
    }
    mint C(int n, int k) const {
        return k < 0 || k > n
                   ? 0
                   : fact[n] * inv_fact[k] * inv_fact[n - k];
    }
};
