/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Двумерный Фенвик: сумма по i<I, j<J и прибавление в точке. Координаты всех обновлений известны заранее: для каждой вызвать fakeUpdate(), затем init().

 * Time: $O(\log^2 N)$. (Персистентное ДО даёт $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
    vector<vector<int>> ys;
    vector<FT> ft;
    FT2(int limx) : ys(limx) {}
    void fakeUpdate(int x, int y) {
        for (; x < sz(ys); x |= x + 1)
            ys[x].eb(y);
    }
    void init() {
        for (vector<int> &v : ys)
            sort(all(v)), ft.eb(sz(v));
    }
    int ind(int x, int y) {
        return (int)(lower_bound(all(ys[x]), y) -
                     ys[x].begin());
    }
    void update(int x, int y, ll dif) {
        for (; x < sz(ys); x |= x + 1)
            ft[x].update(ind(x, y), dif);
    }
    ll query(int x, int y) {
        ll sum = 0;
        for (; x; x &= x - 1)
            sum += ft[x - 1].query(ind(x - 1, y));
        return sum;
    }
};
