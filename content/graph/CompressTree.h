/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Виртуальное дерево для множества S: добавить не более |S|-1 попарных LCA и сжать цепочки. Возвращает (родитель,исходная вершина); корень имеет индекс 0 и ссылается на себя.

 * Time: $O(|S| \log |S|)$
 * Status: Tested at CodeForces
 */
#pragma once

#include "LCA.h"

vector<pair<int, int>> compressTree(LCA &lca,
                                    const vector<int> &subset) {
    static vector<int> rev;
    rev.resize(sz(lca.time));
    vector<int> li = subset, &T = lca.time;
    auto cmp = [&](int a, int b) { return T[a] < T[b]; };
    sort(all(li), cmp);
    int m = sz(li) - 1;
    for (int i = 0; i < (m); ++i) {
        int a = li[i], b = li[i + 1];
        li.eb(lca.lca(a, b));
    }
    sort(all(li), cmp);
    li.erase(unique(all(li)), li.end());
    for (int i = 0; i < (sz(li)); ++i)
        rev[li[i]] = i;
    vector<pair<int, int>> ret = {pair<int, int>(0, li[0])};
    for (int i = 0; i < (sz(li) - 1); ++i) {
        int a = li[i], b = li[i + 1];
        ret.eb(rev[lca.lca(a, b)], b);
    }
    return ret;
}
