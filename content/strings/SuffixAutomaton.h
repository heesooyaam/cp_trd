/**
 * Author: heesooyaam, adapted for cp_trd
 * Source: AlgoTemplates/Strings/suffix_structures/suffix_automaton.cpp
 * Description: SAM over a..z. State 0 is missing, root is 1.
 *  add appends to the same string. After adding, call
 *  count\_occurrences before reading occ (safe to repeat).
 *  get\_state\_size(v) gives the inclusive length interval.
 * Time: Build O(n), count\_occurrences O(n \log n).
 * Memory: O(26n)
 * Status: Exhaustive small strings, occurrences and traverser tests.
 */
#pragma once
struct suffix_automaton {
    struct node {
        int sufflink = 0, len = 0, occ = 0, seed = 0;
        array<int, 26> go{};
        int get_next(char c) const { return go[c - 'a']; }
    };
    static constexpr int root = 1;
    int last = root;
    vector<node> st = vector<node>(2);
    suffix_automaton(string_view s = {}) {
        st.reserve(2 * s.size() + 2);
        add(s);
        count_occurrences();
    }
    node &get(int v) { return st[v]; }
    node &sufflink(int v) { return st[st[v].sufflink]; }
    pair<int, int> get_state_size(int v) {
        return v == root ? pair<int, int>{0, 0}
                         : pair<int, int>{sufflink(v).len + 1,
                                          st[v].len};
    }
    void push_back(char ch) {
        assert('a' <= ch && ch <= 'z');
        int c = ch - 'a', v = last, cur = int(st.size());
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].seed = 1;
        while (v && !st[v].go[c]) {
            st[v].go[c] = cur;
            v = st[v].sufflink;
        }
        if (!v)
            st[cur].sufflink = root;
        else {
            int q = st[v].go[c];
            if (st[q].len == st[v].len + 1) {
                st[cur].sufflink = q;
            } else {
                int clone = int(st.size());
                st.push_back(st[q]);
                st[clone].len = st[v].len + 1;
                st[clone].seed = st[clone].occ = 0;
                st[q].sufflink = st[cur].sufflink = clone;
                while (v && st[v].go[c] == q) {
                    st[v].go[c] = clone;
                    v = st[v].sufflink;
                }
            }
        }
        last = cur;
    }
    void add(string_view s) {
        for (char c : s) push_back(c);
    }
    void count_occurrences() {
        vector<int> order(st.size() - 2);
        iota(order.begin(), order.end(), 2);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });
        for (auto &v : st) v.occ = v.seed;
        for (int v : order) sufflink(v).occ += st[v].occ;
        st[root].occ = 0;
    }
};
struct traverser {
    suffix_automaton &sa;
    int cur = sa.root, len = 0;
    traverser(suffix_automaton &sa) : sa(sa) {}
    bool can_move_by_char(char c) {
        return sa.get(cur).get_next(c) != 0;
    }
    bool can_move_by_sufflink() {
        return sa.get(cur).sufflink != 0;
    }
    void move_by_char(char c) {
        assert(can_move_by_char(c));
        cur = sa.get(cur).get_next(c);
        ++len;
    }
    void move_by_sufflink() {
        cur = sa.get(cur).sufflink;
        len = sa.get(cur).len;
    }
    void move_to_root() {
        cur = sa.root;
        len = 0;
    }
    void move_to_suffix(int length) {
        assert(0 <= length && length <= len);
        while (can_move_by_sufflink() &&
               sa.sufflink(cur).len >= length) {
            move_by_sufflink();
        }
        len = length;
    }
    void pop_front() { move_to_suffix(len - 1); }
    const auto &get_current_state() { return sa.get(cur); }
    int get_current_state_id() const { return cur; }
    int get_length() const { return len; }
};
int longest_common_substring(suffix_automaton &sa,
                             string_view t) {
    traverser tr(sa);
    int ans = 0;
    for (char c : t) {
        while (!tr.can_move_by_char(c) &&
               tr.can_move_by_sufflink()) {
            tr.move_by_sufflink();
        }
        if (tr.can_move_by_char(c)) tr.move_by_char(c);
        ans = max(ans, tr.len);
    }
    return ans;
}
