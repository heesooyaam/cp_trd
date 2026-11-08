/**
 * Author: Mårten Wiman
 * License: CC0
 * Source: Pisinger 1999, "Linear Time Algorithms for Knapsack Problems with Bounded Weights"
 * Description: Для неотрицательных целых весов w и границы t находит максимальную сумму подмножества, не превосходящую t.

 * Time: O(N \max(w_i))
 * Status: Tested on kattis:eavesdropperevasion, stress-tested
 */
#pragma once

int knapsack(vector<int> w, int t) {
    int a = 0, b = 0, x;
    while (b < sz(w) && a + w[b] <= t)
        a += w[b++];
    if (b == sz(w))
        return a;
    int m = *max_element(all(w));
    vector<int> u, v(2 * m, -1);
    v[a + m - t] = b;
    for (int i = b; i < (sz(w)); ++i) {
        u = v;
        for (int x = 0; x < (m); ++x)
            v[x + w[i]] = max(v[x + w[i]], u[x]);
        for (x = 2 * m; --x > m;)
            for (int j = max<int>(0, u[x]); j < (v[x]); ++j)
                v[x - w[j]] = max(v[x - w[j]], j);
    }
    for (a = t; v[a + m - t] < 0; a--)
        ;
    return a;
}
