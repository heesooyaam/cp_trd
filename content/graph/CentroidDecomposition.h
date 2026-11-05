/**
 * Author: cp_trd, inspired by Andrew-A-13's Centroid1
 * Description: Родители в центроидном дереве; у корня -1. Удаление центроида разделяет компоненты. В отмеченном месте build добавлять обработку путей через c. Обход компоненты итеративный, без рекурсии глубины n.

 * Time: O(n \log n), память O(n).
 * Status: Balance and centroid-parent tree checked on random trees.
 */
#pragma once
struct centroid_decomposition {
    vector<vector<int>> graph;
    vector<int> parent, size, prev;
    vector<bool> removed;
    centroid_decomposition(vector<vector<int>> g)
        : graph(std::move(g)), parent(graph.size(), -1),
          size(graph.size()), prev(graph.size()),
          removed(graph.size()) {
        if (!graph.empty())
            build(0, -1);
    }
    void build(int start, int par) {
        vector<int> order{start};
        prev[start] = -1;
        for (int i = 0; i < int(order.size()); ++i) {
            int v = order[i];
            for (int u : graph[v]) {
                if (!removed[u] && u != prev[v])
                    prev[u] = v, order.eb(u);
            }
        }
        int total = int(order.size()), c = -1;
        for (int i = total - 1; i >= 0; --i) {
            int v = order[i], largest = 0;
            size[v] = 1;
            for (int u : graph[v]) {
                if (!removed[u] && prev[u] == v) {
                    size[v] += size[u];
                    largest = max(largest, size[u]);
                }
            }
            largest = max(largest, total - size[v]);
            if (largest <= total / 2)
                c = v;
        }
        parent[c] = par;
        // Обработать пути через c, пропуская удалённые вершины.
        removed[c] = true;
        for (int u : graph[c])
            if (!removed[u])
                build(u, c);
    }
};
