/**
 * Author: cp\_trd
 * Description: Мост — ребро, удаление которого увеличивает число компонент связности; точка сочленения — такая вершина (удаляется со всеми рёбрами). Неориентированный граф, допускаются кратные рёбра, петли и несвязность. Номера рёбер совпадают с индексами во входном edges. Для глубокого DFS нужен достаточный стек. tin — время входа, low — минимальный tin, достижимый из поддерева по дереву DFS и одному обратному ребру.
 * Usage: bridges_and_cuts bc(n, edges);
 *  // bc.bridges — номера мостов, bc.is_cut[v] — точка сочленения
 * Time: O(n+m) время и память.
 * Status: Exhaustive simple graphs and random multigraphs checked by vertex/edge deletion.
 */
#pragma once
struct bridges_and_cuts {
    vector<vector<pair<int, int>>> adj;
    vector<int> tin, low, bridges;
    vector<bool> is_cut;
    int timer = 0;
    bridges_and_cuts(int n, const vector<pair<int, int>> &edges)
        : adj(n), tin(n, -1), low(n), is_cut(n) {
        for (int id = 0; id < int(edges.size()); ++id) {
            auto [u, v] = edges[id];
            adj[u].eb(v, id);
            adj[v].eb(u, id);
        }
        for (int v = 0; v < n; ++v) {
            if (tin[v] == -1) {
                dfs(v, -1);
            }
        }
    }
    void dfs(int v, int parent_edge) {
        tin[v] = low[v] = timer++;
        int children = 0;
        for (auto [u, id] : adj[v]) {
            if (id == parent_edge) {
                continue; // пропускаем ребро, а не вершину-родителя
            }
            if (tin[u] != -1) {
                low[v] = min(low[v], tin[u]);
            } else {
                dfs(u, id);
                ++children;
                low[v] = min(low[v], low[u]);
                if (low[u] > tin[v]) {
                    bridges.eb(id);
                }
                if (parent_edge != -1 && low[u] >= tin[v]) {
                    is_cut[v] = true;
                }
            }
        }
        if (parent_edge == -1) {
            is_cut[v] = children > 1;
        }
    }
};
