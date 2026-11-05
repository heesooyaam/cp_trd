/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Поиск множества образцов. AhoCorasick ac(patterns), корень 0. find(word) для каждой позиции возвращает индекс самого длинного заканчивающегося здесь образца либо -1. findAll возвращает индексы всех начинающихся здесь образцов, от коротких к длинным; без дубликатов всего O(N\sqrt N) вхождений. Дубликаты допустимы, пустые образцы — нет. Для самых длинных начинающихся образцов развернуть все строки.

 * Time: построение $O(26N)$, где N — суммарная длина образцов.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: stress-tested
 */
#pragma once

struct AhoCorasick {
    enum { alpha = 26, first = 'A' }; // задать свой алфавит!
    struct Node {
        // (nmatches можно убрать)
        int back, next[alpha], start = -1, end = -1,
                               nmatches = 0;
        Node(int v) { memset(next, v, sizeof(next)); }
    };
    vector<Node> N;
    vi backp;
    void insert(string &s, int j) {
        assert(!s.empty());
        int n = 0;
        for (char c : s) {
            int &m = N[n].next[c - first];
            if (m == -1) {
                n = m = sz(N);
                N.eb(-1);
            } else
                n = m;
        }
        if (N[n].end == -1)
            N[n].start = j;
        backp.eb(N[n].end);
        N[n].end = j;
        N[n].nmatches++;
    }
    AhoCorasick(vector<string> &pat) : N(1, -1) {
        for (int i = 0; i < (sz(pat)); ++i)
            insert(pat[i], i);
        N[0].back = sz(N);
        N.eb(0);

        queue<int> q;
        for (q.emplace(0); !q.empty(); q.pop()) {
            int n = q.front(), prev = N[n].back;
            for (int i = 0; i < (alpha); ++i) {
                int &ed = N[n].next[i], y = N[prev].next[i];
                if (ed == -1)
                    ed = y;
                else {
                    N[ed].back = y;
                    (N[ed].end == -1 ? N[ed].end
                                     : backp[N[ed].start]) =
                        N[y].end;
                    N[ed].nmatches += N[y].nmatches;
                    q.emplace(ed);
                }
            }
        }
    }
    vi find(string word) {
        int n = 0;
        vi res; // ll count = 0;
        for (char c : word) {
            n = N[n].next[c - first];
            res.eb(N[n].end);
            // count += N[n].nmatches;
        }
        return res;
    }
    vector<vi> findAll(vector<string> &pat, string word) {
        vi r = find(word);
        vector<vi> res(sz(word));
        for (int i = 0; i < (sz(word)); ++i) {
            int ind = r[i];
            while (ind != -1) {
                res[i - sz(pat[ind]) + 1].eb(ind);
                ind = backp[ind];
            }
        }
        return res;
    }
};
