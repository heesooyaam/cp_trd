/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Минимальное вершинное покрытие двудольного графа. Размер равен максимальному паросочетанию; дополнение — максимальное независимое множество.

 * Status: stress-tested
 */
#pragma once

#include "Kuhn.h"

vi cover(vector<vi> &g, int n, int m) {
    kuhn matcher;
    int res = matcher.solve(g, m);
    const vi &match = matcher.match;
    vector<bool> lfound(n, true), seen(m);
    for (int it : match)
        if (it != -1)
            lfound[it] = false;
    vi q, cover;
    for (int i = 0; i < (n); ++i)
        if (lfound[i])
            q.eb(i);
    while (!q.empty()) {
        int i = q.back();
        q.pop_back();
        lfound[i] = 1;
        for (int e : g[i])
            if (!seen[e] && match[e] != -1) {
                seen[e] = true;
                q.eb(match[e]);
            }
    }
    for (int i = 0; i < (n); ++i)
        if (!lfound[i])
            cover.eb(i);
    for (int i = 0; i < (m); ++i)
        if (seen[i])
            cover.eb(n + i);
    assert(sz(cover) == res);
    return cover;
}
