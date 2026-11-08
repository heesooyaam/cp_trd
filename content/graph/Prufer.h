/**
 * Author: cp_trd team
 * License: CC0
 * Description: Код Прюфера: биекция между деревьями на вершинах
 * 0..n-1 и последовательностями длины n-2, n>=2.
 * encode: список смежности простого неориентированного дерева;
 * удаляем минимальный лист, записываем соседа. decode: список рёбер.
 * Степень v = 1 + число v в коде; листья в коде отсутствуют.
 * Пустой код: ребро (0,1); n=1 обрабатывать отдельно.
 * Равномерный код даёт равномерное помеченное дерево.
 * Для заданных степеней перемешать d[v]-1 копий каждого v.
 * Usage: auto edges = prufer_decode({3, 3, 3}); // звезда: центр 3, n=5
 * Time: O(n\log n), память O(n).
 */
#pragma once

vector<int> prufer_encode(const vector<vector<int>> &g) {
    int n = int(g.size());
    assert(n >= 2);
    vector<int> degree(n), neighbors(n), code;
    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int v = 0; v < n; ++v) {
        degree[v] = int(g[v].size());
        for (int u : g[v]) {
            neighbors[v] ^= u;
        }
        if (degree[v] == 1) {
            leaves.emplace(v);
        }
    }
    for (int i = 0; i < n - 2; ++i) {
        int v = leaves.top();
        leaves.pop();
        // XOR соседей листа = единственный сосед.
        int u = neighbors[v];
        code.eb(u);
        neighbors[u] ^= v;
        if (--degree[u] == 1) {
            leaves.emplace(u);
        }
    }
    return code;
}

vector<pair<int, int>> prufer_decode(const vector<int> &code) {
    int n = int(code.size()) + 2;
    vector<int> degree(n, 1);
    for (int v : code) {
        assert(0 <= v && v < n);
        ++degree[v];
    }
    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int v = 0; v < n; ++v) {
        if (degree[v] == 1) {
            leaves.emplace(v);
        }
    }
    vector<pair<int, int>> edges;
    for (int u : code) {
        int v = leaves.top();
        leaves.pop();
        edges.eb(v, u);
        if (--degree[u] == 1) {
            leaves.emplace(u);
        }
    }
    int v = leaves.top();
    leaves.pop();
    edges.eb(v, leaves.top()); // Два оставшихся листа.
    return edges;
}
