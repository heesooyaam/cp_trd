/**
 * Author: heesooyaam
 * Description: Пример версий: для каждого префикса оставляем единицы только на последних k вхождениях каждого значения. roots[i] — корень после a[0..i]. Сумма на [l,r) в roots[r-1] равна сумме min(k,частота x на [l,r)) по различным x. k>=0, значения a в [0,max\_a]. Версии сохраняются после всех обновлений очередного префикса.
 * Time: O(n\log n) время и узлы, дополнительно O(max\_a+n) память.
 * Status: Compared with frequency counting on all subranges.
 */
#pragma once
#include "PersistentSegmentTree.h"

vector<int> capped_versions(const vector<int> &a, int k,
                            int max_a, SumTree<int> &st) {
    vector<queue<int>> positions(max_a + 1);
    vector<int> roots;
    roots.reserve(a.size());
    int last_version = 0;
    for (int i = 0; i < int(a.size()); ++i) {
        last_version = st.update(i, 1, last_version);
        auto &q = positions[a[i]];
        q.push(i);
        if (int(q.size()) > k) {
            last_version =
                st.update(q.front(), 0, last_version);
            q.pop();
        }
        roots.eb(last_version);
    }
    return roots;
}

// Пример онлайн-запросов с декодированием через прошлый ответ.
// n>0; вход: n k, массив, m, затем m пар l r.
void persistent_example() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) {
        cin >> x;
    }
    SumTree<int> st(n);
    auto roots =
        capped_versions(a, k, *max_element(all(a)), st);
    int m, last = 0;
    cin >> m;
    while (m--) {
        ll l, r;
        cin >> l >> r;
        l = (l + last) % n;
        r = (r + last) % n;
        if (l > r) {
            swap(l, r);
        }
        ++r; // теперь [l,r), версия префикса длины r
        last = st.get_sum(int(l), int(r), roots[r - 1]);
        cout << last << ' ';
    }
}
