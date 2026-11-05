/**
 * Author: cp_trd
 * Description: Persistent point-add / range-sum tree on [0,n).
 *  Root 0 is the all-zero version. add(root,pos,delta) returns
 *  a new root; old roots remain usable. query uses [l,r).
 *  For prefix frequency roots, subtract two queries to get a
 *  subarray frequency. Indices survive vector reallocations.
 * Time: O(\log n) per operation and new nodes per update.
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
        t.push_back(t[v]);
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
        if (!v || b <= l || r <= a) return 0;
        if (a <= l && r <= b) return t[v].sum;
        int m = (l + r) / 2;
        return query(t[v].l, a, b, l, m) +
               query(t[v].r, a, b, m, r);
    }
};
