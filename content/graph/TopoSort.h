/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Топологический порядок ориентированного графа. Если есть цикл, размер ответа меньше n; вершины циклов и достижимые из них не попадут в ответ.

 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
#pragma once

vector<int> topoSort(const vector<vector<int>> &gr) {
    vector<int> indeg(sz(gr)), q;
    for (auto &li : gr)
        for (int x : li)
            indeg[x]++;
    for (int i = 0; i < (sz(gr)); ++i)
        if (indeg[i] == 0)
            q.eb(i);
    for (int j = 0; j < (sz(q)); ++j)
        for (int x : gr[q[j]])
            if (--indeg[x] == 0)
                q.eb(x);
    return q;
}
