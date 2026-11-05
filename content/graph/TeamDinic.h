/**
 * Author: Andrew-A-13, refactored for cp_trd
 * Source: Templates/Потоки/dinic
 * Description: Dinic with explicit reverse edges, ll capacities.
 *  Parallel edges and self loops are allowed. s must differ
 *  from t. max\_flow returns additional flow in the residual graph.
 *  Flow on original edge id is \texttt{edges[id \^{} 1].cap}.
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
        graph[u].push_back(int(edges.size()));
        edges.push_back({v, cap});
        graph[v].push_back(int(edges.size()));
        edges.push_back({u, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : graph[v]) {
                auto [u, cap] = edges[id];
                if (cap && level[u] == -1)
                    level[u] = level[v] + 1, q.push(u);
            }
        }
        return level[t] != -1;
    }
    ll dfs(int v, int t, ll flow) {
        if (v == t) return flow;
        for (int &i = ptr[v]; i < int(graph[v].size()); ++i) {
            int id = graph[v][i], u = edges[id].to;
            if (edges[id].cap && level[u] == level[v] + 1) {
                ll pushed =
                    dfs(u, t, min(flow, edges[id].cap));
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
            fill(ptr.begin(), ptr.end(), 0);
            while (ll f = dfs(s, t, LLONG_MAX)) result += f;
        }
        return result;
    }
};
