#include "../utilities/template.h"
#include "../utilities/utils.h"

#include "../../content/graph/GlobalMinCut.h"
#include "../../content/graph/GomoryHu.h"
#include "../../content/graph/Dinic.h"


void test(int N, int mxFlow, int iters) {
	for (int it = 0; it < iters; it++) {
		int n = rand()%N+1;
		int m = rand()%(N*N);
		vector<array<ll, 3>> edges;
		vector<vi> mat(n, vi(n));
		for (int it = 0; it < (m); ++it) {
			int i = rand() % n;
			int j = rand() % n;
			if (i == j) continue;
			int w = rand() % mxFlow;
			edges.push_back({i, j, w});
			mat[i][j] += w;
			mat[j][i] += w;
		}
		auto calc = [&](int s, int t) {
			Dinic flow(n);
			for (auto e : edges) {
				flow.addEdge((int)e[0], (int)e[1], e[2], e[2]);
			}
			return flow.calc(s, t);
		};
		vector<flow_edge> gomoryHuTree = gomory_hu(n, edges);
		vector<vector<array<int, 2>>> adj(n);
		for (auto e : gomoryHuTree) {
			adj[e[0]].push_back({(int)e[1], (int)e[2]});
			adj[e[1]].push_back({(int)e[0], (int)e[2]});
		}
		auto dfs = make_y_combinator([&](auto dfs, int start, int cur, int p, int mn) -> void {
			if (start != cur) {
				assert(mn == calc(start, cur));
			}
			for (auto i : adj[cur]) {
				if (i[0] != p)
					dfs(start, i[0], cur, min(mn, i[1]));
			}
		});
		for (int start = 0; start < n; ++start)
            dfs(start, start, -1, INT_MAX);

		// Check that the lightest edge agrees with GlobalMinCut.
		if (n >= 2) {
			ll minCut = LLONG_MAX;
			for (auto e : gomoryHuTree) {
				minCut = min(minCut, e[2]);
			}
			auto mat2 = mat;
			auto pa = globalMinCut(mat2);
			assert(pa.first == minCut);
			vi inCut(n);
			assert(sz(pa.second) != 0);
			assert(sz(pa.second) != n);
			for (int x : pa.second) {
				assert(0 <= x && x < n);
				assert(!inCut[x]);
				inCut[x] = 1;
			}
			int cutw = 0;
			for (int i = 0; i < (n); ++i) for (int j = 0; j < (n); ++j) if (inCut[i] && !inCut[j]) {
				cutw += mat[i][j];
			}
			assert(pa.first == cutw);
		}
	}
}
void large_capacity_test() {
    const ll big = 3000000000000LL;
    vector<flow_edge> edges = {{0, 1, big}, {1, 2, big + 7},
                               {0, 2, 11}, {0, 1, 5}};
    auto tree = gomory_hu(4, edges); // vertex 3 is isolated
    assert(tree.size() == 3);
    vector<vector<pair<int, ll>>> adj(4);
    for (auto [u, v, cap] : tree) {
        adj[u].eb(int(v), cap);
        adj[v].eb(int(u), cap);
    }
    for (int s = 0; s < 4; ++s) {
        vector<ll> answer(4, -1);
        auto visit = [&](auto &&self, int v, int p, ll value) -> void {
            answer[v] = value;
            for (auto [u, cap] : adj[v])
                if (u != p)
                    self(self, u, v, min(value, cap));
        };
        visit(visit, s, -1, LLONG_MAX);
        for (int t = 0; t < 4; ++t) {
            if (s == t)
                continue;
            ll expected = LLONG_MAX;
            for (int mask = 0; mask < 16; ++mask) {
                if (!(mask >> s & 1) || (mask >> t & 1))
                    continue;
                ll cut = 0;
                for (auto [u, v, cap] : edges)
                    if ((mask >> u & 1) != (mask >> v & 1))
                        cut += cap;
                expected = min(expected, cut);
            }
            assert(answer[t] == expected);
        }
    }
    assert(gomory_hu(0, {}).empty());
    assert(gomory_hu(1, {}).empty());
}
signed main() {
    large_capacity_test();
	test(25, 5, 200);
	test(100, 1000, 5);
	test(100, 1, 20);
	test(5, 5, 20000);
	cout<<"Tests passed!"<<endl;
}
