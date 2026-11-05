/**
 * Author: heesooyaam
 * Description: Персистентное ДО: присваивание a[pos]=val и сумма на [l,r) внутри [0,n), n>0. Версия — индекс корня, а не номер операции; корень 0 задаёт нулевой массив. update(pos,val,version) возвращает корень новой версии, старая не меняется. Обновлять можно любую сохранённую версию. T должен вмещать сумму. Узлы хранятся по индексам, ссылки на элементы nodes через рекурсию не сохранять: vector может перевыделить память.
 * Usage: SumTree<ll> st(n); int v1 = st.update(2, 7, 0);
 *  int v2 = st.update(2, 9, v1); // v1 всё ещё содержит 7
 *  ll sum = st.get_sum(0, n, v2);
 * Time: O(\log n) запрос и новых узлов на обновление.
 * Status: Random branching versions, 64-bit sums and capped-frequency example checked against arrays.
 */
#pragma once

template <typename T = int> class SumTree {
  public:
    struct Node {
        T sum = 0;
        int l = 0, r = 0;
    };
    explicit SumTree(int sz) : n(sz) {
        assert(n > 0);
        nodes.eb();
    }
    int update(int pos, T val, int version) {
        assert(0 <= pos && pos < n);
        return update(version, pos, val, 0, n);
    }
    T get_sum(int l, int r, int version) const {
        assert(0 <= l && l <= r && r <= n);
        return get_sum(version, l, r, 0, n);
    }

  protected:
    int n;
    vector<Node> nodes;

  private:
    int update(int v, int pos, T val, int cur_l, int cur_r) {
        if (cur_l + 1 == cur_r) {
            nodes.eb(val);
            return int(nodes.size()) - 1;
        }
        int mid = cur_l + (cur_r - cur_l) / 2;
        nodes.eb(nodes[v]);
        int new_v = int(nodes.size()) - 1;
        int l_child = nodes[v].l, r_child = nodes[v].r;
        if (pos < mid) {
            l_child = update(l_child, pos, val, cur_l, mid);
            nodes[new_v].l = l_child;
        } else {
            r_child = update(r_child, pos, val, mid, cur_r);
            nodes[new_v].r = r_child;
        }
        nodes[new_v].sum =
            nodes[l_child].sum + nodes[r_child].sum;
        return new_v;
    }
    T get_sum(int v, int l, int r, int cur_l, int cur_r) const {
        if (l >= r || v == 0) {
            return 0;
        }
        if (l == cur_l && r == cur_r) {
            return nodes[v].sum;
        }
        int mid = cur_l + (cur_r - cur_l) / 2;
        return get_sum(nodes[v].l, l, min(r, mid), cur_l, mid) +
               get_sum(nodes[v].r, max(l, mid), r, mid, cur_r);
    }
};
