/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: Множество непересекающихся полуинтервалов [l,r): вставка объединяет пересекающиеся интервалы, удаление вырезает заданный участок.

 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

set<pii>::iterator addInterval(set<pii> &is, int L, int R) {
    if (L == R)
        return is.end();
    auto it = is.lower_bound({L, R}), before = it;
    while (it != is.end() && it->first <= R) {
        R = max(R, it->second);
        before = it = is.erase(it);
    }
    if (it != is.begin() && (--it)->second >= L) {
        L = min(L, it->first);
        R = max(R, it->second);
        is.erase(it);
    }
    return is.emplace_hint(before, L, R);
}

void removeInterval(set<pii> &is, int L, int R) {
    if (L == R)
        return;
    auto it = addInterval(is, L, R);
    auto r2 = it->second;
    if (it->first == L)
        is.erase(it);
    else
        (int &)it->second = L;
    if (R != r2)
        is.emplace(R, r2);
}
