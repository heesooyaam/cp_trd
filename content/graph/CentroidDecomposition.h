/**
 * Author: cp_trd, inspired by Andrew-A-13's Centroid1
 * Description: Centroid parent for every vertex of a tree;
 *  root has parent=-1. Removed vertices split components.
 *  Extend build at the marked line to process paths through c.
 *  Iterative component traversal avoids a depth-n size DFS.
 * Time: O(n \log n), memory O(n).
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
        if (!graph.empty()) build(0, -1);
    }
    void build(int start, int par) {
        vector<int> order{start};
        prev[start] = -1;
        for (int i = 0; i < int(order.size()); ++i) {
            int v = order[i];
            for (int u : graph[v]) {
                if (!removed[u] && u != prev[v])
                    prev[u] = v, order.push_back(u);
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
            if (largest <= total / 2) c = v;
        }
        parent[c] = par;
        // Process paths through c here (skip removed vertices).
        removed[c] = true;
        for (int u : graph[c])
            if (!removed[u]) build(u, c);
    }
};
