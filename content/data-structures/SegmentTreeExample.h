/**
 * Author: heesooyaam
 * Description: Настройка GenericSegmentTree: прибавление на отрезке, запрос суммы. len — число элементов, у пустого нейтрального узла len=0, у листа len=1. Для присваивания вместо прибавления см. пример в doc/segment-trees.md; порядок composition важен для несовместимых обновлений.
 * Status: Random tests against arrays.
 */
#pragma once
#include "GenericSegmentTree.h"

namespace range_sum {
struct node_t {
    ll sum = 0;
    int len = 1;
};
using push_t = ll;
node_t combine(node_t a, node_t b) {
    return {a.sum + b.sum, a.len + b.len};
}
node_t neutral_node() {
    return {0, 0};
}
push_t composition(push_t old_p, push_t new_p) {
    return old_p + new_p;
}
node_t sync(node_t x, push_t f) {
    return {x.sum + f * x.len, x.len};
}
push_t neutral_push() {
    return 0;
}
using tree_t = seg_tree_t<node_t, combine, neutral_node, push_t,
                          composition, sync, neutral_push>;
} // namespace range_sum

void segment_tree_example() {
    vector<ll> a = {2, 4, 6};
    vector<range_sum::node_t> data;
    for (ll x : a) {
        data.eb(x, 1);
    }
    range_sum::tree_t st(data); // либо st(n): n нулей
    st.update(0, 2, 3); // {5, 7, 6}: прибавить 3 на [0,2)
    st.update(1, -2);   // {5, 5, 6}: прибавить -2 в точке 1
    ll sum = st.get(0, 3).sum; // 16
    ll value = st.get(1).sum;  // 5
    // Присвоить 10 в точке при такой настройке:
    st.update(1, 10 - value);
    (void)sum;
}
