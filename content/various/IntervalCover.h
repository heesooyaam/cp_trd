/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Индексы минимального числа полуинтервалов, покрывающих заданный [l,r). Для замкнутых отрезков добавить в (A) условие || R.empty(). Пустой ответ означает неудачу либо пустой целевой интервал.

 * Time: O(N \log N)
 * Status: Tested on kattis:intervalcover
 */
#pragma once

template <class T>
vector<int> cover(pair<T, T> G, vector<pair<T, T>> I) {
    vector<int> S(sz(I)), R;
    iota(all(S), 0);
    sort(all(S), [&](int a, int b) { return I[a] < I[b]; });
    T cur = G.first;
    int at = 0;
    while (cur < G.second) { // (A)
        pair<T, int> mx = make_pair(cur, -1);
        while (at < sz(I) && I[S[at]].first <= cur) {
            mx = max(mx, make_pair(I[S[at]].second, S[at]));
            at++;
        }
        if (mx.second == -1)
            return {};
        cur = mx.first;
        R.eb(mx.second);
    }
    return R;
}
