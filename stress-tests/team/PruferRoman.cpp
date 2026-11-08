#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define all(x) std::begin(x), std::end(x)
#define eb(...) emplace_back(__VA_ARGS__)
#include "../../content/graph/Prufer.h"
#include "../../content/math/RomanNumerals.h"

vector<int> slow_encode(const vector<vector<int>> &g) {
    vector<set<int>> adj(g.size());
    for (int v = 0; v < int(g.size()); ++v) {
        adj[v] = set<int>(all(g[v]));
    }
    vector<int> code;
    for (int i = 0; i < int(g.size()) - 2; ++i) {
        int leaf = 0;
        while (adj[leaf].size() != 1) {
            ++leaf;
        }
        int next = *adj[leaf].begin();
        code.eb(next);
        adj[next].erase(leaf);
        adj[leaf].clear();
    }
    return code;
}

vector<pair<int, int>> normalize(vector<pair<int, int>> edges) {
    for (auto &[u, v] : edges) {
        if (u > v) {
            swap(u, v);
        }
    }
    sort(all(edges));
    return edges;
}

vector<vector<int>>
adjacency(int n, const vector<pair<int, int>> &edges) {
    assert(int(edges.size()) == n - 1);
    vector<vector<int>> g(n);
    for (auto [u, v] : edges) {
        assert(0 <= u && u < n && 0 <= v && v < n && u != v);
        g[u].eb(v);
        g[v].eb(u);
    }
    vector<int> seen(n), order{0};
    seen[0] = 1;
    for (int i = 0; i < int(order.size()); ++i) {
        for (int u : g[order[i]]) {
            if (!seen[u]) {
                seen[u] = 1;
                order.eb(u);
            }
        }
    }
    assert(int(order.size()) == n);
    return g;
}

void prufer_tests() {
    assert(normalize(prufer_decode({})) ==
           (vector<pair<int, int>>{{0, 1}}));
    assert(normalize(prufer_decode({3, 3, 3})) ==
           (vector<pair<int, int>>{
               {0, 3}, {1, 3}, {2, 3}, {3, 4}}));
    for (int n = 2; n <= 7; ++n) {
        int count = 1;
        for (int i = 0; i < n - 2; ++i) {
            count *= n;
        }
        set<vector<pair<int, int>>> trees;
        for (int mask = 0; mask < count; ++mask) {
            vector<int> code(n - 2), degree(n, 1);
            int cur = mask;
            for (int &v : code) {
                v = cur % n;
                cur /= n;
                ++degree[v];
            }
            auto edges = prufer_decode(code);
            auto g = adjacency(n, edges);
            assert(slow_encode(g) == code);
            assert(prufer_encode(g) == code);
            for (int v = 0; v < n; ++v) {
                assert(int(g[v].size()) == degree[v]);
            }
            assert(trees.emplace(normalize(edges)).second);
        }
        assert(int(trees.size()) == count);
    }
    mt19937 gen(821937);
    for (int it = 0; it < 1000; ++it) {
        int n = 2 + gen() % 300;
        vector<int> labels(n);
        iota(all(labels), 0);
        shuffle(all(labels), gen);
        vector<pair<int, int>> edges;
        for (int v = 1; v < n; ++v) {
            edges.eb(labels[v], labels[gen() % v]);
        }
        auto g = adjacency(n, edges);
        for (auto &adj : g) {
            shuffle(all(adj), gen);
        }
        auto code = prufer_encode(g);
        assert(code == slow_encode(g));
        assert(normalize(prufer_decode(code)) ==
               normalize(edges));
    }
    for (bool star : {false, true}) {
        int n = 200000;
        vector<pair<int, int>> edges;
        for (int v = 1; v < n; ++v) {
            edges.eb(v, star ? 0 : v - 1);
        }
        auto code = prufer_encode(adjacency(n, edges));
        assert(normalize(prufer_decode(code)) ==
               normalize(edges));
    }
}

// Независимый эталон по десятичным разрядам вместо жадного вычитания.
string decimal_roman(int n) {
    const string ones[] = {"",  "I",  "II",  "III",  "IV",
                           "V", "VI", "VII", "VIII", "IX"};
    const string tens[] = {"",  "X",  "XX",  "XXX",  "XL",
                           "L", "LX", "LXX", "LXXX", "XC"};
    const string hundreds[] = {"",  "C",  "CC",  "CCC",  "CD",
                               "D", "DC", "DCC", "DCCC", "CM"};
    return string(n / 1000, 'M') + hundreds[n / 100 % 10] +
           tens[n / 10 % 10] + ones[n % 10];
}

void roman_tests() {
    map<string, int> canonical;
    for (int n = 1; n <= 3999; ++n) {
        string expected = decimal_roman(n);
        assert(to_roman(n) == expected);
        assert(from_roman(expected) == n);
        assert(canonical.emplace(expected, n).second);
    }
    assert(to_roman(1994) == "MCMXCIV");
    assert(to_roman(3999) == "MMMCMXCIX");
    assert(from_roman("XLIX") == 49);
    assert(to_roman(3888).size() == 15);
    for (int x : {INT_MIN, -1, 0, 4000, INT_MAX}) {
        assert(to_roman(x).empty());
    }
    for (string s : {"", "IIII", "IC", "IL", "VX", "IIV",
                     "IXIX", "VV", "MMMM", "MCMC", "IXX", "xiv",
                     " XIV", "X IV", "XIV ", "ABC", "N"}) {
        assert(from_roman(s) == -1);
    }
    assert(from_roman(string(1000000, 'M')) == -1);
    assert(from_roman(string("I\0V", 3)) == -1);
    assert(from_roman(string(1, char(255))) == -1);
    mt19937 gen(10925);
    string symbols = "IVXLCDMivx ?";
    for (int it = 0; it < 100000; ++it) {
        string s(gen() % 18, ' ');
        for (char &c : s) {
            c = symbols[gen() % symbols.size()];
        }
        auto found = canonical.find(s);
        int expected =
            found == canonical.end() ? -1 : found->second;
        assert(from_roman(s) == expected);
    }
}

int main() {
    prufer_tests();
    roman_tests();
    cout << "Prufer and Roman numeral tests passed\n";
}
