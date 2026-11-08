/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Виртуальное дерево сжимает большое дерево для запроса по отмеченным вершинам S. Оставляем S и необходимые точки ветвления (LCA), а цепочки между ними заменяем одним ребром. Новое ребро — целый путь исходного дерева, не обязательно соседство. Пример: 0-1-2 и 1-3-4, S=\{2,4\}: вершины \{1,2,4\}, рёбра 1-2 и 1-4. Для ДП и сумм расстояний по S: не более 2|S|-1 вершин при непустом S. Для построения достаточно LCA соседей в порядке DFS. Корень — LCA всех S, не обязательно исходная вершина 0. ret[i]=(p,v): v — исходная вершина, p — индекс её родителя в ret; ret[0].first=0, для i>0 родитель раньше ребёнка. Вес ребра i равен depth[v]-depth[ret[p].second], для взвешенного дерева — разности расстояний от исходного корня. Пустой S даёт пустой ответ, повторы удаляются.

 * Time: O(|S| \log |S|) на запрос после построения LCA; первый вызов выделяет O(n) массив rev.
 * Status: Tested at CodeForces
 */
#pragma once

#include "LCA.h"

vector<pair<int, int>> compressTree(LCA &lca,
                                    const vector<int> &subset) {
    if (subset.empty()) {
        return {};
    }
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
