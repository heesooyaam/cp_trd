/**
 * Author: cp_trd
 * Description: Персистентное ДО: прибавление в точке и сумма на [l,r) внутри [0,n). Корень 0 — нулевая версия. add(root,pos,delta) возвращает новый корень, старый остаётся доступен. Разность запросов к префиксным частотным версиям даёт частоту на подотрезке. Узлы хранятся по индексам.

 * Time: O(\log n) на операцию и новых узлов на обновление.
 * Status: Random branching versions checked against arrays.
 */
#pragma once
struct persistent_segment_tree {
    struct Node {
        int l = 0, r = 0;
        ll sum = 0;
    };
    vector<Node> t = {Node{}};
    int n;
    persistent_segment_tree(int n) : n(n) { assert(n > 0); }
    int add(int root, int pos, ll delta) {
        assert(0 <= pos && pos < n);
        return add(root, pos, delta, 0, n);
    }
    int add(int v, int p, ll d, int l, int r) {
        int u = int(t.size());
        t.eb(t[v]);
        t[u].sum += d;
        if (r - l > 1) {
            int m = (l + r) / 2;
            if (p < m)
                t[u].l = add(t[u].l, p, d, l, m);
            else
                t[u].r = add(t[u].r, p, d, m, r);
        }
        return u;
    }
    ll query(int root, int l, int r) const {
        return query(root, l, r, 0, n);
    }
    ll query(int v, int a, int b, int l, int r) const {
        if (!v || b <= l || r <= a)
            return 0;
        if (a <= l && r <= b)
            return t[v].sum;
        int m = (l + r) / 2;
        return query(t[v].l, a, b, l, m) +
               query(t[v].r, a, b, m, r);
    }
};
