/**
 * Author: Mattias de Zalenski, Fredrik Niemelä, Per Austrin, Simon Lindholm
 * Date: 2002-09-26
 * Source: Max Bennedich
 * Description: Мультиномиальный коэффициент $\binom{k_1+\dots+k_n}{k_1,\dots,k_n}=(\sum k_i)!/\prod k_i!$.

 * Status: Tested on kattis:lexicography
 */
#pragma once

ll multinomial(vector<int> &v) {
    ll c = 1, m = v.empty() ? 1 : v[0];
    for (int i = 1; i < (sz(v)); ++i)
        for (int j = 0; j < (v[i]); ++j)
            c = c * ++m / (j + 1);
    return c;
}
