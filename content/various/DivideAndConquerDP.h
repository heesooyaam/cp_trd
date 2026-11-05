/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: Codeforces
 * Description: Вычисляет $a_i=\min_{lo(i)\le k<hi(i)} f(i,k)$ для i в [L,R), если минимальный оптимальный k не убывает с i.

 * Time: O((N + (hi-lo)) \log N)
 * Status: tested on http://codeforces.com/contest/321/problem/E
 */
#pragma once

struct DP { // изменить под задачу:
    int lo(int ind) { return 0; }
    int hi(int ind) { return ind; }
    ll f(int ind, int k) { return dp[ind][k]; }
    void store(int ind, int k, ll v) { res[ind] = pii(k, v); }

    void rec(int L, int R, int LO, int HI) {
        if (L >= R)
            return;
        int mid = (L + R) >> 1;
        pair<ll, int> best(LLONG_MAX, LO);
        for (int k = max(LO, lo(mid)); k < (min(HI, hi(mid)));
             ++k)
            best = min(best, make_pair(f(mid, k), k));
        store(mid, best.second, best.first);
        rec(L, mid, LO, best.second + 1);
        rec(mid + 1, R, best.second, HI);
    }
    void solve(int L, int R) { rec(L, R, INT_MIN, INT_MAX); }
};
