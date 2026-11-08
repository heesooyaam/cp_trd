#define main reference_template_main
#include "../../content/contest/template.cpp"
#undef main
#include "../../content/strings/MinRotation.h"
#include "../../content/strings/TeamSuffixArray.h"
#include "../../content/strings/SuffixArray.h"
#include "../../content/strings/TeamHash.h"
#include "../../content/various/FastKnapsack.h"
#include "../../content/graph/MaximumClique.h"
#include "../../content/graph/FloydWarshall.h"
#include "../../content/graph/TeamDinic.h"
#include "../../content/data-structures/OrderStatisticTree.h"
#include "../../content/data-structures/HashMap.h"
#include "../../content/data-structures/PersistentSegmentTree.h"
#include "../../content/math/RomanNumerals.h"
#include "../../content/graph/Prufer.h"

static_assert(is_same_v<ll, int64_t>);
static_assert(is_same_v<int, int64_t>);
static_assert(sizeof(int) == 8);
static_assert(
    is_same_v<decltype(reference_template_main()), int32_t>);

#if defined(__x86_64__) || defined(__i386__)
#pragma GCC push_options
#include "../../content/various/SIMD.h"
void simd_width_test() {
    mi v = _mm256_setr_epi32(1, 2, 3, 4, 5, 6, 7, 8);
    assert(sumi32(v) == 36);
    assert(all_zero(zero()) && all_one(one()));
}
#pragma GCC pop_options
// Включение immintrin не должно выключать пользовательский define int.
static_assert(sizeof(int) == 8);
#endif

int32_t main() {
    ordered_examples();
    int large = int(1) << 40;
    ordered_set<int> s;
    s.insert(large);
    s.insert(large + 1);
    assert(s.order_of_key(large + 1) == 1);
    assert(*s.find_by_order(0) == large);
    h[large] = large + 2;
    assert(h[large] == large + 2);
    SumTree<> tree(3);
    int root = tree.update(1, large, 0);
    root = tree.update(2, large + 1, root);
    assert(tree.get_sum(0, 3, root) == 2 * large + 1);
    assert(tree.get_sum(0, 3, 0) == 0);
    dinic flow(2);
    flow.add_edge(0, 1, large);
    assert(flow.max_flow(0, 1) == large);
    vector<vector<ll>> dist{{5, large}, {inf, 7}};
    floydWarshall(dist);
    assert(dist[0][0] == 0 && dist[1][1] == 0);
    assert(dist[0][1] == large && dist[1][0] == inf);
    mt19937 gen(93475);
    for (int it = 0; it < 500; ++it) {
        string text(gen() % 35, 'a');
        for (char &c : text) {
            c += gen() % 3;
        }
        vector<int> expected(text.size());
        iota(all(expected), 0);
        sort(all(expected), [&](int a, int b) {
            return text.substr(a) < text.substr(b);
        });
        auto sa = suffix_array(text);
        assert(sa == expected);
        auto lcp = suffix_lcp(text, sa);
        for (int i = 0; i + 1 < int(sa.size()); ++i) {
            int same = 0;
            while (sa[i] + same < int(text.size()) &&
                   sa[i + 1] + same < int(text.size()) &&
                   text[sa[i] + same] ==
                       text[sa[i + 1] + same]) {
                ++same;
            }
            assert(lcp[i] == same);
        }
        SuffixArray legacy(text);
        expected.insert(expected.begin(), int(text.size()));
        assert(legacy.sa == expected);
        string_hasher hash(text, true, false);
        for (int l = 0; l < int(text.size()); ++l) {
            for (int r = l + 1; r <= int(text.size()); ++r) {
                string part = text.substr(l, r - l),
                       back = part;
                reverse(all(back));
                assert(hash.is_palindrome(l + 1, r) ==
                       (part == back));
            }
        }
        if (!text.empty()) {
            string best = text;
            for (int i = 1; i < int(text.size()); ++i) {
                best = min(best,
                           text.substr(i) + text.substr(0, i));
            }
            int k = minRotation(text);
            assert(text.substr(k) + text.substr(0, k) == best);
        }
        vector<int> weights(gen() % 12);
        for (int &w : weights) {
            w = gen() % 20 + 1;
        }
        int target = gen() % 80, best = 0;
        for (int mask = 0; mask < (int(1) << weights.size());
             ++mask) {
            int sum = 0;
            for (int i = 0; i < int(weights.size()); ++i) {
                if (mask & (int(1) << i)) {
                    sum += weights[i];
                }
            }
            if (sum <= target) {
                best = max(best, sum);
            }
        }
        assert(knapsack(weights, target) == best);
    }
    vector<bitset<200>> graph(3);
    for (int u = 0; u < 3; ++u) {
        for (int v = 0; v < 3; ++v) {
            graph[u][v] = u != v;
        }
    }
    assert(Maxclique(graph).maxClique().size() == 3);
    assert(from_roman(to_roman(1994)) == 1994);
    vector<vector<int>> star{{3}, {3}, {3}, {0, 1, 2, 4}, {3}};
    assert(prufer_encode(star) == vector<int>({3, 3, 3}));
#if defined(__x86_64__) || defined(__i386__)
    if (__builtin_cpu_supports("avx2")) {
        simd_width_test();
    }
#endif
    cout << "int64 template integration passed\n";
}
