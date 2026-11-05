/**
 * Author: cp_trd, inspired by Andrew-A-13's Better Treap
 * Description: Декартово мультимножество: вставка, удаление одной копии, число ключей строго меньше x, kth с индексацией от 0. Повторы хранятся счётчиком. Поддерживается LLONG\_MAX. Память удалённых узлов не переиспользуется.

 * Time: Ожидаемое O(\log n) на операцию.
 * Status: Random operations checked against std::multiset.
 */
#pragma once
struct treap_set {
    struct node {
        ll key = 0;
        uint32_t priority = 0;
        int l = 0, r = 0, cnt = 0, size = 0;
    };
    vector<node> tree = {node{}};
    mt19937 rng;
    int root = 0;
    treap_set(uint32_t seed = 712367) : rng(seed) {}
    int size(int v) const { return tree[v].size; }
    void update(int v) {
        tree[v].size =
            size(tree[v].l) + size(tree[v].r) + tree[v].cnt;
    }
    int merge(int l, int r) {
        if (!l || !r)
            return l | r;
        if (tree[l].priority > tree[r].priority) {
            tree[l].r = merge(tree[l].r, r);
            update(l);
            return l;
        }
        tree[r].l = merge(l, tree[r].l);
        update(r);
        return r;
    }
    int rotate(int v, bool left) {
        int u = left ? tree[v].l : tree[v].r;
        if (left) {
            tree[v].l = tree[u].r;
            tree[u].r = v;
        } else {
            tree[v].r = tree[u].l;
            tree[u].l = v;
        }
        update(v);
        update(u);
        return u;
    }
    int insert(int v, ll x) {
        if (!v) {
            tree.eb(x, uint32_t(rng()), 0, 0, 1, 1);
            return int(tree.size()) - 1;
        }
        if (x == tree[v].key)
            ++tree[v].cnt;
        else {
            bool left = x < tree[v].key;
            int child = insert(left ? tree[v].l : tree[v].r, x);
            if (left)
                tree[v].l = child;
            else
                tree[v].r = child;
            if (tree[child].priority > tree[v].priority)
                v = rotate(v, left);
        }
        update(v);
        return v;
    }
    int erase(int v, ll x) {
        if (!v)
            return 0;
        if (tree[v].key == x) {
            if (--tree[v].cnt == 0)
                return merge(tree[v].l, tree[v].r);
        } else if (x < tree[v].key) {
            tree[v].l = erase(tree[v].l, x);
        } else
            tree[v].r = erase(tree[v].r, x);
        update(v);
        return v;
    }
    void insert(ll x) { root = insert(root, x); }
    void erase(ll x) { root = erase(root, x); }
    int order_of_key(ll x) const {
        int ans = 0, v = root;
        while (v) {
            if (x <= tree[v].key)
                v = tree[v].l;
            else {
                ans += size(tree[v].l) + tree[v].cnt;
                v = tree[v].r;
            }
        }
        return ans;
    }
    ll kth(int k) const {
        assert(0 <= k && k < size(root));
        int v = root;
        while (true) {
            int left = size(tree[v].l);
            if (k < left)
                v = tree[v].l;
            else if (k < left + tree[v].cnt)
                return tree[v].key;
            else
                k -= left + tree[v].cnt, v = tree[v].r;
        }
    }
};
