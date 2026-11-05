/**
 * Author: Andrew-A-13, refactored for cp_trd
 * Source: Templates/Потоки/MinCostMaxFlow
 * Description: Successive shortest paths with Johnson potentials.
 *  Negative costs allowed, but no negative-cost residual cycles.
 *  Returns additional (flow,cost), up to limit; s != t.
 *  Parallel edges allowed. All distances, potentials and total
 *  cost must fit ll (distances strictly below inf).
 * Time: O(VE + A E \log V), A augmentations.
 * Status: Small graphs checked by enumerating feasible flows.
 */
#pragma once
struct min_cost_flow {
    struct edge {
        int from, to;
        ll cap, cost;
    };
    static constexpr ll inf = LLONG_MAX / 4;
    vector<edge> edges;
    vector<vector<int>> graph;
    min_cost_flow(int n) : graph(n) {}
    void add_edge(int u, int v, ll cap, ll cost) {
        assert(cap >= 0);
        graph[u].push_back(int(edges.size()));
        edges.push_back({u, v, cap, cost});
        graph[v].push_back(int(edges.size()));
        edges.push_back({v, u, 0, -cost});
    }
    pair<ll, ll> solve(int s, int t, ll limit = inf) {
        assert(s != t && limit >= 0);
        int n = int(graph.size());
        vector<ll> potential(n, inf), dist(n);
        vector<int> prev(n);
        potential[s] = 0;
        for (int it = 0; it < n; ++it) {
            bool changed = false;
            for (auto e : edges) {
                if (e.cap && potential[e.from] != inf &&
                    potential[e.to] >
                        potential[e.from] + e.cost) {
                    potential[e.to] =
                        potential[e.from] + e.cost;
                    changed = true;
                }
            }
            if (!changed) break;
            assert(it != n - 1); // reachable negative cycle
        }
        for (ll &x : potential)
            if (x == inf) x = 0;
        ll flow = 0, cost = 0;
        while (flow < limit) {
            fill(dist.begin(), dist.end(), inf);
            dist[s] = 0;
            using item = pair<ll, int>;
            priority_queue<item, vector<item>, greater<item>>
                q;
            q.emplace(0, s);
            while (!q.empty()) {
                auto [d, v] = q.top();
                q.pop();
                if (d != dist[v]) continue;
                for (int id : graph[v]) {
                    auto e = edges[id];
                    ll nd = d + e.cost + potential[v] -
                            potential[e.to];
                    if (e.cap && nd < dist[e.to]) {
                        dist[e.to] = nd;
                        prev[e.to] = id;
                        q.emplace(nd, e.to);
                    }
                }
            }
            if (dist[t] == inf) break;
            for (int v = 0; v < n; ++v)
                if (dist[v] < inf) potential[v] += dist[v];
            ll pushed = limit - flow;
            for (int v = t; v != s; v = edges[prev[v]].from)
                pushed = min(pushed, edges[prev[v]].cap);
            for (int v = t; v != s; v = edges[prev[v]].from) {
                int id = prev[v];
                edges[id].cap -= pushed;
                edges[id ^ 1].cap += pushed;
                cost += pushed * edges[id].cost;
            }
            flow += pushed;
        }
        return {flow, cost};
    }
};
