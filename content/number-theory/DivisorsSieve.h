/**
 * Author: heesooyaam, adapted for cp_trd
 * Source: AlgoTemplates/Math/DivisorsSieve.cpp
 * Description: Все делители каждого x из [1,n] по возрастанию в общем массиве. Представление диапазона действительно до уничтожения структуры.

 * Usage: divisors_sieve_t s(n); for (int d : s.get(x)) { ... }
 * Time: O(n \log n) time and память.
 * Status: Tested against enumeration.
 */
#pragma once
struct divisors_sieve_t {
    vector<int> data, off;
    struct range_t {
        vector<int>::const_iterator l, r;
        auto begin() const { return l; }
        auto end() const { return r; }
    };
    divisors_sieve_t(int n) : off(n + 2) {
        assert(n >= 0);
        for (int d = 1; d < n + 1; ++d)
            for (int x = d; x <= n; x += d)
                ++off[x + 1];
        for (int x = 1; x < n + 2; ++x)
            off[x] += off[x - 1];
        data.resize(off.back());
        vector<int> cur = off;
        for (int d = 1; d < n + 1; ++d)
            for (int x = d; x <= n; x += d)
                data[cur[x]++] = d;
    }
    range_t get(int x) const {
        return {data.begin() + off[x],
                data.begin() + off[x + 1]};
    }
};
