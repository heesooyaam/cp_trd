/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Фенвик: сумма a[0..pos) и прибавление в точке. Для присваивания передать разность нового и старого значения.

 * Time: Обе операции: $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) { // a[pos] += dif
        for (; pos < sz(s); pos |= pos + 1)
            s[pos] += dif;
    }
    ll query(int pos) { // сумма на [0,pos)
        ll res = 0;
        for (; pos > 0; pos &= pos - 1)
            res += s[pos - 1];
        return res;
    }
    int
    lower_bound(ll sum) { // минимальный pos с суммой [0,pos] >= sum
        // n, если не найдено; -1, если подходит пустой префикс.
        if (sum <= 0)
            return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
                pos += pw, sum -= s[pos - 1];
        }
        return pos;
    }
};
