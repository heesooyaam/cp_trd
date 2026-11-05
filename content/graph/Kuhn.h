/**
 * Author: Andrew-A-13, refactored for cp_trd
 * Source: Templates/Потоки/Kuhn
 * Description: g[v] — правые соседи левой вершины v. Правая доля индексируется 0..m-1 независимо от левой. match[r] — её левая пара либо -1.

 * Time: O(VE)
 * Status: Stress-tested against exhaustive matching.
 */
#pragma once
struct kuhn {
    vector<int> match, used;
    int timer = 0;
    bool dfs(int v, const vector<vector<int>> &g) {
        if (used[v] == timer)
            return false;
        used[v] = timer;
        for (int u : g[v]) {
            if (match[u] == -1 || dfs(match[u], g)) {
                match[u] = v;
                return true;
            }
        }
        return false;
    }
    int solve(const vector<vector<int>> &g, int m) {
        match.assign(m, -1);
        used.assign(g.size(), 0);
        timer = 0;
        int ans = 0;
        for (int v = 0; v < int(g.size()); ++v) {
            ++timer;
            ans += dfs(v, g);
        }
        return ans;
    }
};
