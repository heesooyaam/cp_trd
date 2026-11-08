#define main reference_template_main
#include "../../content/contest/template.cpp"
#undef main
#include "../../content/data-structures/UnionFind.h"
#include "../../content/data-structures/PotentialDSU.h"
#include "../../content/data-structures/XorBasis.h"

mt19937_64 gen(847273);

template <bool use_xor> void test_potentials() {
    for (int it = 0; it < 150; ++it) {
        int n = gen() % 15 + 1;
        PotentialDSU<use_xor> d(n);
        vector<vector<pair<int, ll>>> graph(n);
        auto combine = [](ll a, ll b) {
            return use_xor ? a ^ b : a + b;
        };
        auto inverse = [](ll a) { return use_xor ? a : -a; };
        auto brute = [&](int start) {
            vector<optional<ll>> dist(n);
            vector<int> queue{start};
            dist[start] = 0;
            for (int i = 0; i < int(queue.size()); ++i) {
                int v = queue[i];
                for (auto [u, w] : graph[v]) {
                    if (!dist[u]) {
                        dist[u] = combine(*dist[v], w);
                        queue.eb(u);
                    }
                }
            }
            return dist;
        };
        for (int step = 0; step < 120; ++step) {
            int a = gen() % n, b = gen() % n;
            ll w =
                use_xor ? ll(gen() % 64) : ll(gen() % 101) - 50;
            auto known = brute(a)[b];
            if (known && gen() % 2) {
                w = *known;
            }
            bool expected = !known || *known == w;
            assert(d.join(a, b, w) == expected);
            if (expected) {
                graph[a].eb(b, w);
                graph[b].eb(a, inverse(w));
            }
            for (int v = 0; v < n; ++v) {
                auto dist = brute(v);
                for (int u = 0; u < n; ++u) {
                    assert(d.diff(v, u) == dist[u]);
                }
            }
        }
    }
}

int32_t main() {
    for (int it = 0; it < 150; ++it) {
        int n = gen() % 40 + 1;
        UF d(n);
        vector<int> label(n);
        iota(all(label), 0);
        for (int step = 0; step < 200; ++step) {
            int a = gen() % n, b = gen() % n;
            bool merged = label[a] != label[b];
            assert(d.join(a, b) == merged);
            int from = label[b], to = label[a];
            for (int &x : label) {
                if (x == from) {
                    x = to;
                }
            }
            for (int v = 0; v < n; ++v) {
                assert(d.size(v) ==
                       count(all(label), label[v]));
                assert(d.sameSet(a, v) ==
                       (label[a] == label[v]));
            }
        }
    }
    test_potentials<false>();
    test_potentials<true>();
    PotentialDSU<> big(3);
    assert(big.join(0, 1, ll(1) << 40));
    assert(big.join(1, 2, -(ll(1) << 41)));
    assert(big.diff(0, 2) == -(ll(1) << 40));
    XorBasis full;
    for (int i = 0; i < 64; ++i) {
        assert(full.add(uint64_t(1) << i));
    }
    assert(full.rank == 64 && full.max_xor() == UINT64_MAX);
    assert(!full.add(0) && !full.add(UINT64_MAX));
    full.merge(full);
    assert(full.rank == 64);
    for (int it = 0; it < 1000; ++it) {
        XorBasis basis, left, right;
        vector<uint64_t> values{0};
        int n = gen() % 11;
        for (int i = 0; i < n; ++i) {
            uint64_t x = it % 2 ? gen() : gen() % 256;
            bool independent =
                find(all(values), x) == values.end();
            assert(basis.add(x) == independent);
            (i % 2 ? left : right).add(x);
            int old_size = values.size();
            for (int j = 0; j < old_size; ++j) {
                values.eb(values[j] ^ x);
            }
        }
        sort(all(values));
        values.erase(unique(all(values)), values.end());
        assert(values.size() == (uint64_t(1) << basis.rank));
        left.merge(right);
        assert(left.rank == basis.rank);
        for (uint64_t x : values) {
            assert(basis.contains(x) && left.contains(x));
        }
        for (int q = 0; q < 30; ++q) {
            uint64_t x = it % 2 ? gen() : gen() % 512;
            assert(basis.contains(x) ==
                   binary_search(all(values), x));
            uint64_t best = 0;
            for (uint64_t v : values) {
                best = max(best, v ^ x);
            }
            assert(basis.max_xor(x) == best &&
                   left.max_xor(x) == best);
        }
    }
    cout << "DSU, potentials and XOR basis passed\n";
}
