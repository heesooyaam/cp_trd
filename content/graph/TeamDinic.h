/**
 * Author: Andrew-A-13, refactored for cp_trd
 * Source: Templates/Потоки/dinic
 * Description: Диниц с явными обратными рёбрами, ёмкости ll. Допустимы петли и кратные рёбра; s!=t. max\_flow возвращает дополнительный поток в остаточной сети. Поток исходного ребра id равен \texttt{edges[id \^{} 1].cap}. После завершения level[v]!=-1 отмечает сторону истока минимального разреза.

 * Time: O(V^2 E)
 * Status: Stress-tested against exhaustive min cuts.
 */
#pragma once
struct dinic {
    struct edge {
        int to;
        ll cap;
    };
    vector<edge> edges;
    vector<vector<int>> graph;
    vector<int> level, ptr;
    dinic(int n) : graph(n), level(n), ptr(n) {}
    void add_edge(int u, int v, ll cap) {
        assert(cap >= 0);
        graph[u].eb(int(edges.size()));
        edges.eb(v, cap);
        graph[v].eb(int(edges.size()));
        edges.eb(u, 0);
    }
    bool bfs(int s, int t) {
        fill(all(level), -1);
        queue<int> q;
        q.emplace(s);
        level[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : graph[v]) {
                auto [u, cap] = edges[id];
                if (cap && level[u] == -1)
                    level[u] = level[v] + 1, q.emplace(u);
            }
        }
        return level[t] != -1;
    }
    ll dfs(int v, int t, ll flow) {
        if (v == t)
            return flow;
        for (int &i = ptr[v]; i < int(graph[v].size()); ++i) {
            int id = graph[v][i], u = edges[id].to;
            if (edges[id].cap && level[u] == level[v] + 1) {
                ll pushed = dfs(u, t, min(flow, edges[id].cap));
                if (pushed) {
                    edges[id].cap -= pushed;
                    edges[id ^ 1].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    ll max_flow(int s, int t) {
        assert(s != t);
        ll result = 0;
        while (bfs(s, t)) {
            fill(all(ptr), 0);
            while (ll f = dfs(s, t, LLONG_MAX))
                result += f;
        }
        return result;
    }
};
